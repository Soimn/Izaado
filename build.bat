@echo off

if "%Platform%" neq "x64" (
    echo ERROR: Platform is not "x64" - please run this from the MSVC x64 native tools command prompt.
    exit /b 1
)

set "diag_options= /nologo /FC /diagnostics:column /W4 /wd4996 /wd4116 /wd4100 /wd4201 /wd4101 /wd4204 /wd4200"
set "nocrt_options= /Zl /GR- /GS- /Gs9999999"
set "noctr_link= /STACK:0x100000,0x100000 /NODEFAULTLIB /SUBSYSTEM:windows"
set "fast_fp= /fp:fast /fp:except-"

IF NOT EXIST .\build mkdir build
pushd .\build

IF "%1"=="all" (
set /A game=1
set /A engine=1
) ELSE IF "%1"=="engine" (
set /A game=0
set /A engine=1
) ELSE IF "%1"=="game" (
set /A game=1
set /A engine=0
) ELSE (
echo Invalid arguments. Usage: build.bat [all/engine/game] [debug/internal/release]
GOTO :DONE
)

IF "%2"=="debug" (
set "compile_options= /DIZ_DEBUG %nocrt_options% %diag_options% /Od /Zo /Zf /Z7"
) ELSE IF "%1"=="internal" (
set "compile_options= /DIZ_INTERNAL %nocrt_options% %diag_options% /O2 /Zo /Zf /Z7"
) ELSE (
set "compile_options= %nocrt_options% %diag_options% /O2 /Zo /Zf /Z7"
)

set "link_options= /INCREMENTAL:NO /opt:ref /STACK:0x100000,0x100000 /NODEFAULTLIB /SUBSYSTEM:windows"

IF /I "%engine%" EQU "1" cl %compile_options% ..\src\iz_win32.c /link %link_options% /PDB:izaado.pdb /ENTRY:WinMainCRTStartup Kernel32.lib Winmm.lib User32.lib Gdi32.lib OpenGL32.lib /out:izaado.exe
IF /I "%game%" EQU "1" cl %compile_options% ..\src\izaado.c /LD /link %link_options% Kernel32.lib /EXPORT:GameTick /out:game.dll

del izaado.obj
del iz_win32.obj
del izaado.lib
del izaado.exp

:DONE

popd
