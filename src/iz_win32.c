#define UNICODE
#define NOMINMAX            1
#define WIN32_LEAN_AND_MEAN 1
#define WIN32_MEAN_AND_LEAN 1
#define VC_EXTRALEAN        1
#include <windows.h>
#include <Timeapi.h>
#undef NOMINMAX
#undef WIN32_LEAN_AND_MEAN
#undef WIN32_MEAN_AND_LEAN
#undef VC_EXTRALEAN
#undef far
#undef near

#include "iz_platform.h"
#include "iz_renderer_opengl.h"
#include "iz_win32_renderer.h"

typedef struct Win32_File_Timestamp
{
    u64 creation;
    u64 last_write;
    u64 last_access;
} Win32_File_Timestamp;

typedef struct Win32_Game_Code
{
    Win32_File_Timestamp timestamp;
    HMODULE handle;
    platform_game_tick_func* game_tick;
} Win32_Game_Code;

internal void
Win32_Log(const char* message, ...)
{
    Memory_Arena_Marker mem_marker = Arena_BeginTempMemory(Platform->transient_memory);
    
    va_list arg_list;
    va_start(arg_list, message);
    umm required_size = FormatStringArgList((Buffer){0}, message, arg_list);
    va_end(arg_list);
    
    Buffer buffer;
    buffer.size = required_size + 1;
    buffer.data = Arena_PushSize(Platform->transient_memory, buffer.size, 1);
    
    va_start(arg_list, message);
    FormatStringArgList(buffer, message, arg_list);
    buffer.data[buffer.size - 1] = 0;
    va_end(arg_list);
    
    OutputDebugStringA("[Win32] ");
    OutputDebugStringA((LPCSTR)buffer.data);
    OutputDebugStringA("\n");
    
    Arena_EndTempMemory(Platform->transient_memory, mem_marker);
}

internal void
Win32_ErrorPrompt(const char* message, ...)
{
    Memory_Arena_Marker mem_marker = Arena_BeginTempMemory(Platform->transient_memory);
    
    va_list arg_list;
    va_start(arg_list, message);
    umm required_size = FormatStringArgList((Buffer){0}, message, arg_list);
    va_end(arg_list);
    
    Buffer buffer;
    buffer.size = required_size + 1;
    buffer.data = Arena_PushSize(Platform->transient_memory, buffer.size, 1);
    
    va_start(arg_list, message);
    FormatStringArgList(buffer, message, arg_list);
    buffer.data[buffer.size - 1] = 0;
    va_end(arg_list);
    
    MessageBoxA(GetActiveWindow(), (LPCSTR)buffer.data, "Izaado", MB_ICONERROR | MB_OK);
    
    Arena_EndTempMemory(Platform->transient_memory, mem_marker);
}

LRESULT CALLBACK
WindowProc(HWND window_handle, UINT message, WPARAM wparam, LPARAM lparam)
{
    LRESULT result = 0;
    
    if (message == WM_QUIT || message == WM_CLOSE) PostQuitMessage(0);
    else result = DefWindowProc(window_handle, message, wparam, lparam);
    
    return result;
}

bool
Win32_GetFileTimestamp(LPWSTR path, Win32_File_Timestamp* timestamp)
{
    bool succeeded = false;
    
    WIN32_FILE_ATTRIBUTE_DATA attributes;
    if (GetFileAttributesExW(path, GetFileExInfoStandard, &attributes))
    {
        timestamp->creation    = (u64)attributes.ftCreationTime.dwHighDateTime   << 32 | attributes.ftCreationTime.dwLowDateTime;
        timestamp->last_write  = (u64)attributes.ftLastWriteTime.dwHighDateTime  << 32 | attributes.ftLastWriteTime.dwLowDateTime;
        timestamp->last_access = (u64)attributes.ftLastAccessTime.dwHighDateTime << 32 | attributes.ftLastAccessTime.dwLowDateTime;
        
        succeeded = true;
    }
    
    return succeeded;
}

bool
Win32_LoadGameCode(Win32_Game_Code* game_code, LPWSTR game_code_path, LPWSTR temp_game_code_path, LPWSTR loaded_game_code_path)
{
    bool succeeded = false;
    
    if (CopyFileW(game_code_path, temp_game_code_path, 0))
    {
        HMODULE handle = LoadLibraryW(temp_game_code_path);
        
        if (handle == 0) Win32_Log("Failed to load game code dll");
        else
        {
            platform_game_tick_func* tick = (platform_game_tick_func*)GetProcAddress(handle, "GameTick");
            
            if (tick == 0) Win32_Log("Failed to load game tick function");
            else
            {
                FreeLibrary(handle);
                FreeLibrary(game_code->handle);
                
                DeleteFile(loaded_game_code_path);
                if (MoveFile(temp_game_code_path, loaded_game_code_path))
                {
                    handle = LoadLibraryW(loaded_game_code_path);
                    tick = (platform_game_tick_func*)GetProcAddress(handle, "GameTick");
                    
                    if (handle != 0 && tick != 0)
                    {
                        game_code->handle    = handle;
                        game_code->game_tick = tick;
                        
                        succeeded = true;
                    }
                }
            }
        }
    }
    
    return succeeded;
}

void __stdcall
WinMainCRTStartup()
{
    HINSTANCE instance        = GetModuleHandle(0);
    Win32_Game_Code game_code = {0};
    HWND window_handle        = 0;
    
    WNDCLASSW window_class = {
        .lpfnWndProc   = &WindowProc,
        .hInstance     = instance,
        .lpszClassName = L"Izaado",
    };
    
    if (!RegisterClassW(&window_class)) Win32_ErrorPrompt("Failed to register window class");
    else
    {
        window_handle = CreateWindowExW(0, L"Izaado", L"Izaado", WS_OVERLAPPEDWINDOW,
                                        CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT,
                                        0, 0, instance, 0);
        
        if (window_handle == INVALID_HANDLE_VALUE) Win32_ErrorPrompt("Failed to create window");
        else
        {
            bool setup_failed = false;
            
            Platform_Data platform = {0};
            Platform = &platform;
            
            /// Setup memory arenas
            Memory_Arena memory_bank[2] = {0};
            {
                bool succeeded_in_allocating_memory = false;
                
                do {
                    SYSTEM_INFO system_info;
                    GetSystemInfo(&system_info);
                    
                    umm page_size = system_info.dwPageSize;
                    
                    umm persistent_memory_size = RoundUpToAlignment(PLATFORM_PERSISTENT_MEMORY_SIZE, page_size);
                    umm transient_memory_size  = RoundUpToAlignment(PLATFORM_TRANSIENT_MEMORY_SIZE, page_size);
                    
                    DWORD garbage;
                    u8* base = VirtualAlloc((void*)0, persistent_memory_size + page_size, MEM_RESERVE | MEM_COMMIT, PAGE_READWRITE);
                    if (base == 0) break;
                    if (!VirtualProtect(base + persistent_memory_size, page_size, PAGE_NOACCESS, &garbage)) break;
                    
                    platform.persistent_memory = &memory_bank[0];
                    platform.persistent_memory->base_address = (u64)base;
                    platform.persistent_memory->size         = persistent_memory_size;
                    
                    base = VirtualAlloc(0, transient_memory_size + page_size, MEM_RESERVE | MEM_COMMIT, PAGE_READWRITE);
                    if (base == 0) break;
                    if (!VirtualProtect(base + transient_memory_size, page_size, PAGE_NOACCESS, &garbage)) break;
                    
                    platform.transient_memory = &memory_bank[1];
                    platform.transient_memory->base_address = (u64)base;
                    platform.transient_memory->size         = transient_memory_size;
                    
                    succeeded_in_allocating_memory = true;
                } while (0);
                
                if (!succeeded_in_allocating_memory)
                {
                    MessageBoxA(window_handle, "Failed to allocate memory for the game.", "Izaado", MB_ICONERROR | MB_OK);
                    setup_failed = true;
                }
            }
            
            /// Setup paths
            LPWSTR game_code_path        = L"game.dll";
            LPWSTR temp_game_code_path   = L"game_loaded.dll";
            LPWSTR loaded_game_code_path = L"game_temp.dll";
            
            if (!setup_failed)
            {
                u32 size = MAX_PATH;
                
                void* buffer = Arena_PushSize(Platform->transient_memory, size, ALIGNOF(WCHAR));
                
                Win32_Log("%u", *((u8*)buffer + 4));
                
                PWSTR file_path = 0;
                umm length      = 0;
                
                while (file_path == 0)
                {
                    u32 max_length = size / sizeof(WCHAR);
                    length         = GetModuleFileNameW(instance, buffer, max_length);
                    
                    if      (length == 0) break;
                    else if (length == max_length)
                    {
                        // NOTE: This will probably never happen, but failing to launch a game because the
                        //       file path to the game engine it too long is exceptionally stupid
                        size += MAX_PATH;
                    }
                    
                    else file_path = buffer;
                }
                
                umm last_backslash = 0;
                for (umm i = 0; file_path[i] != 0; ++i)
                {
                    if (file_path[i] == L'\\') last_backslash = i;
                }
                
                file_path[last_backslash + 1] = 0;
                
                bool successfully_set_cwd = (bool)SetCurrentDirectoryW(file_path);
                
                if (!successfully_set_cwd)
                {
                    LPWSTR paths[] = {game_code_path, temp_game_code_path, loaded_game_code_path};
                    
                    umm file_path_length = last_backslash + 1;
                    
                    for (umm i = 0; i < ARRAY_SIZE(paths); ++i)
                    {
                        umm path_length = 0;
                        for (WCHAR* scan = paths[i]; *scan != 0; ++scan) ++path_length;
                        
                        void* new_path = Arena_PushSize(Platform->persistent_memory, (file_path_length + path_length + 1) * sizeof(WCHAR), 1);
                        
                        Copy(file_path, new_path, file_path_length * sizeof(WCHAR));
                        Copy(paths[i], (u8*)new_path + file_path_length * sizeof(WCHAR), path_length * sizeof(WCHAR));
                        ((WCHAR*)new_path)[file_path_length + path_length] = 0;
                        
                        paths[i] = new_path;
                    }
                    
                    game_code_path        = paths[0];
                    temp_game_code_path   = paths[1];
                    loaded_game_code_path = paths[2];
                }
            }
            
            /// Setup renderer
            if (!setup_failed)
            {
                setup_failed = !Win32_RendererSetup(instance, window_handle);
            }
            
            /// Load game code
            if (!setup_failed)
            {
                for (umm tries = 0;; ++tries)
                {
                    if (Win32_LoadGameCode(&game_code, game_code_path, temp_game_code_path, loaded_game_code_path))
                    {
                        Win32_File_Timestamp timestamp;
                        if (Win32_GetFileTimestamp(game_code_path, &timestamp))
                        {
                            game_code.timestamp = timestamp;
                        }
                        
                        Win32_Log("Successfully loaded game code");
                        break;
                    }
                    
                    else if (tries == 10)
                    {
                        Win32_ErrorPrompt("Failed to load game code");
                        setup_failed = true;
                        break;
                    }
                    
                    else continue;
                }
            }
            
            /// Run game
            if (!setup_failed)
            {
                ShowWindow(window_handle, SW_SHOW);
                
                // NOTE: request minimum resolution of 1 ms for timers, affects Sleep
                timeBeginPeriod(1);
                
                LARGE_INTEGER perf_freq;
                QueryPerformanceFrequency(&perf_freq);
                
                LARGE_INTEGER flip_time;
                QueryPerformanceCounter(&flip_time);
                
                bool running = true;
                while (running)
                {
                    Arena_Clear(Platform->transient_memory);
                    
                    /// Reload game code if necessary
                    if (IZ_INTERNAL)
                    {
                        Win32_File_Timestamp game_code_timestamp;
                        if (Win32_GetFileTimestamp(game_code_path, &game_code_timestamp) && !StructCompare(&game_code_timestamp, &game_code.timestamp))
                        {
                            if (Win32_LoadGameCode(&game_code, game_code_path, temp_game_code_path, loaded_game_code_path))
                            {
                                if (Win32_GetFileTimestamp(game_code_path, &game_code_timestamp))
                                {
                                    game_code.timestamp = game_code_timestamp;
                                }
                                
                                Win32_Log("Successfully reloaded game code");
                            }
                        }
                    }
                    
                    MSG msg;
                    while (PeekMessageW(&msg, 0, 0, 0, PM_REMOVE))
                    {
                        if (msg.message == WM_QUIT)
                        {
                            running = false;
                            break;
                        }
                        
                        else DispatchMessage(&msg);
                    }
                    
                    RECT window_rect;
                    GetWindowRect(window_handle, &window_rect); // TODO: Should the return value for this be checked?
                    imm width  = window_rect.right - window_rect.left;
                    imm height = window_rect.bottom - window_rect.top;
                    
                    Renderer_BeginFrame(width, height);
                    
                    game_code.game_tick(Platform);
                    
                    Renderer_EndFrame();
                    
                    /// End of frame cleanup
                    LARGE_INTEGER end_time;
                    QueryPerformanceCounter(&end_time);
                    
                    Win32_Log("frame time: %ums", (u32)(1000 * (f32)(end_time.QuadPart - flip_time.QuadPart) / perf_freq.QuadPart));
                    
                    flip_time = end_time;
                }
                
                timeEndPeriod(1);
                DeleteFile(loaded_game_code_path);
            }
        }
    }
    
    ExitProcess(0);
}