import std;

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
