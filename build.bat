@echo off

call "C:\Program Files\Microsoft Visual Studio\2022\Enterprise\VC\Auxiliary\Build\vcvars64.bat"

REM Compile `std` module for our compiler flags
cl.exe /std:c++latest /MD /EHsc /nologo /W4 /c "%VCToolsInstallDir%\modules\std.ixx"

REM Build and link with `std.obj`; make sure to use the same compiler flags as above
cl.exe test\test.cpp std.obj /std:c++latest /MD /EHsc /nologo /W4 /Fe"test.exe"

REM Run
test.exe
