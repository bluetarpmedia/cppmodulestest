// `import std;` does not import macros.
// C++ Language feature test macros are available with just `import std;` since
// they are predefined in each translation unit, rather than #defined in header files.
// But it's necessary to `#include <version>` to enable C++ Library feature test macros.
#include <version>

#ifdef __cpp_lib_modules
import std;
#else
    #error C++ Standard Library modules not available
#endif

int main()
{
    std::cout << "Hello World!\n";

#ifdef __cpp_modules
    std::cout << "__cpp_modules: " << std::to_string(__cpp_modules) << " \n";
#else
    std::cout << "__cpp_modules: not defined\n";
#endif

#ifdef __cpp_lib_modules
    std::cout << "__cpp_lib_modules: " << std::to_string(__cpp_lib_modules) << " \n";
#else
    std::cout << "__cpp_lib_modules: not defined\n";
#endif
}
