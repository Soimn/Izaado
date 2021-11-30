
bool
Win32_PlatformGetFileInfo(String path, File_Info* file_info)
{
    bool succeeded = false;
    
    Memory_Arena_Marker marker = Arena_BeginTempMemory(Platform->transient_memory);
    
    int required_chars = MultiByteToWideChar(CP_UTF8, 0, (LPCCH)path.data, (int)path.size, 0, 0);
    
    if (required_chars != 0)
    {
        WCHAR* wide_path = Arena_PushSize(Platform->transient_memory, (required_chars + 1) * sizeof(WCHAR), ALIGNOF(WCHAR));
        
        if (MultiByteToWideChar(CP_UTF8, 0, (LPCCH)path.data, (int)path.size, wide_path, required_chars) == required_chars)
        {
            wide_path[required_chars] = 0;
            
            WIN32_FILE_ATTRIBUTE_DATA attributes;
            if (GetFileAttributesExW(wide_path, GetFileExInfoStandard, &attributes))
            {
                file_info->creation_time.value    = (u64)attributes.ftCreationTime.dwHighDateTime   << 32 | attributes.ftCreationTime.dwLowDateTime;
                file_info->last_write_time.value  = (u64)attributes.ftLastWriteTime.dwHighDateTime  << 32 | attributes.ftLastWriteTime.dwLowDateTime;
                file_info->last_access_time.value = (u64)attributes.ftLastAccessTime.dwHighDateTime << 32 | attributes.ftLastAccessTime.dwLowDateTime;
                file_info->file_size              = attributes.nFileSizeLow;
                
                // NOTE: files larger than 4GB are not supported
                if (attributes.nFileSizeHigh == 0)
                {
                    succeeded = true;
                }
            }
        }
    }
    
    Arena_EndTempMemory(Platform->transient_memory, marker);
    
    return succeeded;
}

bool
Win32_PlatformReadEntireFile(String path, Memory_Arena* arena, File_Info* file_info, String* file_contents)
{
    bool succeeded = false;
    
    Memory_Arena_Marker marker = Arena_BeginTempMemory(Platform->transient_memory);
    
    HANDLE file_handle = INVALID_HANDLE_VALUE;
    u32 file_size      = 0;
    
    int required_chars = MultiByteToWideChar(CP_UTF8, 0, (LPCCH)path.data, (int)path.size, 0, 0);
    
    if (required_chars != 0)
    {
        WCHAR* wide_path = Arena_PushSize(Platform->transient_memory, (required_chars + 1) * sizeof(WCHAR), ALIGNOF(WCHAR));
        
        if (MultiByteToWideChar(CP_UTF8, 0, (LPCCH)path.data, (int)path.size, wide_path, required_chars) == required_chars)
        {
            wide_path[required_chars] = 0;
            
            WIN32_FILE_ATTRIBUTE_DATA attributes;
            if (GetFileAttributesExW(wide_path, GetFileExInfoStandard, &attributes))
            {
                if (file_info != 0)
                {
                    file_info->creation_time.value    = (u64)attributes.ftCreationTime.dwHighDateTime   << 32 | attributes.ftCreationTime.dwLowDateTime;
                    file_info->last_write_time.value  = (u64)attributes.ftLastWriteTime.dwHighDateTime  << 32 | attributes.ftLastWriteTime.dwLowDateTime;
                    file_info->last_access_time.value = (u64)attributes.ftLastAccessTime.dwHighDateTime << 32 | attributes.ftLastAccessTime.dwLowDateTime;
                    file_info->file_size              = attributes.nFileSizeLow;
                }
                
                file_size = attributes.nFileSizeLow;
                
                // NOTE: files larger than 4GB are not supported
                if (attributes.nFileSizeHigh == 0)
                {
                    file_handle = CreateFileW(wide_path, GENERIC_READ, FILE_SHARE_READ, 0, OPEN_EXISTING, attributes.dwFileAttributes, 0);
                }
            }
        }
    }
    
    
    Arena_EndTempMemory(Platform->transient_memory, marker);
    
    if (file_handle != INVALID_HANDLE_VALUE)
    {
        file_contents->size = file_size;
        file_contents->data = Arena_PushSize(arena, file_size + 1, ALIGNOF(WCHAR));
        
        DWORD bytes_read;
        if (ReadFile(file_handle, file_contents->data, (u32)file_size, &bytes_read, 0) && bytes_read == file_size)
        {
            file_contents->data[file_contents->size] = 0;
            
            succeeded = true;
        }
    }
    
    return succeeded;
}

void
Win32_PlatformLog(const char* message, ...)
{
    Memory_Arena_Marker mem_marker = Arena_BeginTempMemory(Platform->transient_memory);
    
    va_list arg_list;
    va_start(arg_list, message);
    umm required_size = String_FormatArgList((Buffer){0}, message, arg_list);
    va_end(arg_list);
    
    Buffer buffer;
    buffer.size = required_size + 1;
    buffer.data = Arena_PushSize(Platform->transient_memory, buffer.size, 1);
    
    va_start(arg_list, message);
    String_FormatArgList(buffer, message, arg_list);
    buffer.data[buffer.size - 1] = 0;
    va_end(arg_list);
    
    OutputDebugStringA((LPCSTR)buffer.data);
    OutputDebugStringA("\n");
    
    Arena_EndTempMemory(Platform->transient_memory, mem_marker);
}
