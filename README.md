# `import.std` with MSVC and GitHub Actions

The following has been tested with Visual Studio 2022 17.8.

This repo demonstrates two methods to enable support for `import.std;` with MSVC in a GitHub workflow:
1. Run `msbuild` for a Visual Studio solution (easier)
2. Run `cl.exe` on the command line

## msbuild for a Visual Studio solution

In the vcxproj, set:
- `Build ISO C++23 Standard Library Modules` to `Yes`
- `C++ Language Standard` to `Preview - Features from the Latest C++ Working Draft (/std:c++latest)`

You do not need to set `Enable Experimental C++ Standard Library Modules (/experimental:module)`.

Use these steps in the workflow:

```
- uses: actions/checkout@v3
- name: Add msbuild to PATH
  uses: microsoft/setup-msbuild@v1.1
- name: Build for release
  run: msbuild test\test.sln -t:rebuild -p:Configuration=Release -p:Platform=x64
```

See the "build-vs-solution" job in [build.yml](https://github.com/bluetarpmedia/cppmodulestest/blob/main/.github/workflows/build.yml)

## cl.exe on the command line

Based on [these instructions](https://learn.microsoft.com/en-us/cpp/cpp/tutorial-import-stl-named-module?view=msvc-170):

Use these steps in the workflow:

```
- uses: actions/checkout@v3
- name: Build command line
  shell: cmd
  run: build.bat
```

Create a `build.bat` file.

Note that you **do not** need to specify `/experimental:module`.

```
@echo off

call "C:\Program Files\Microsoft Visual Studio\2022\Enterprise\VC\Auxiliary\Build\vcvars64.bat"

REM Compile `std` module for our compiler flags
cl.exe /std:c++latest /MD /EHsc /nologo /W4 /c "%VCToolsInstallDir%\modules\std.ixx"

REM Build and link with `std.obj`
cl.exe test\test.cpp std.obj /std:c++latest /MD /EHsc /nologo /W4 /Fe"test.exe"
```

See the "build-command-line" job in [build.yml](https://github.com/bluetarpmedia/cppmodulestest/blob/main/.github/workflows/build.yml) and the [build.bat](https://github.com/bluetarpmedia/cppmodulestest/blob/main/build.bat) file.

## Modules feature test macros

There are two relevant feature test macros related to C++ modules:
- `__cpp_modules`: indicates whether the compiler supports C++ modules
- `__cpp_lib_modules`: indicates whether `import std;` and `import std.compat;` are available

C++ Language feature test macros (like `__cpp_modules`) are predefined in each translation unit by the compiler. You can use `__cpp_modules` without needing to `#include` or `import` anything.

However, C++ Library feature test macros (like `__cpp_lib_modules`) are defined in header files and C++ modules **do not** import macros from header files.

This behaviour may be surprising:
```
import std;

int main()
{
#ifdef __cpp_modules
    // Yes!
#endif

#ifdef __cpp_lib_modules
    // No!
#endif
}
```

The solution is to `#include <version>` first:
```
#include <version>
import std;

int main()
{
#ifdef __cpp_modules
    // Yes!
#endif

#ifdef __cpp_lib_modules
    // Yes!
#endif
}
```
