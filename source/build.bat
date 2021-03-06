@echo off

IF NOT DEFINED clset (call "C:\Program Files (x86)\Microsoft Visual Studio\2017\Community\VC\Auxiliary\build\vcvarsall.bat" x64)

:: docs.microsoft.com/en-us/cpp/build/reference/compiler-options-listed-by-category?view=vs-2019

set MultithreadCompile=-MT
set NoLogo=-nologo
set RuntimeInformation=-GR-
set ModernCatchExceptions=-EHa-
set NoExternCExceptions=-EHsc
set DisableOptimization=-Od
set GenerateIntrinsics=-Oi
set WarningLevel=-W2
set WarningAsErrors=-WX
set DisplayFullSourcePath=-FC
set GenerateVersion7Debugging=-Z7

set IgnoreConversionOfGreaterSize=-wd4312
set IgnoreTrunctionOfPointerType=-wd4311 -wd4302

set IncludeRegistryLib=Advapi32.lib

set CommonCompilerFlags=%MultithreadCompile% %NoLogo% %RuntimeInformation% %ModernCatchExceptions% %NoExternCExceptions% %DisableOptimization% %GenerateIntrinsics% %WarningLevel% %WarningsAsErrors% %DisplayFullSourcePaths% %GenerateVersion7Debugging% %IgnoreConversionOfGreaterSize% %IgnoreTrunctionOfPointerType%

set CommonLinkerFlags=-opt:ref User32.lib gdi32.lib winmm.lib opengl32.lib %IncludeRegistryLib%
set ProjectLinkerFlags=glew32.lib glew32s.lib
set ImguiProjectFiles=..\include\imgui\examples\imgui_impl_win32.cpp ..\include\imgui\examples\imgui_impl_opengl3.cpp ..\include\imgui\imgui*.cpp

IF NOT EXIST ..\build  mkdir ..\build
pushd ..\build

del *.obj /Q

REM 64 bit build
cl %CommonCompilerFlags% /I ..\include ..\source\senser_entry.cpp %ImguiProjectFiles% /link %ProjectLinkerFlags% %CommonLinkerFlags% /libpath:..\lib 

popd