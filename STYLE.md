### General Coding Standards 

Avoid `using` statements at all costs, preface all C++ standard libraries with the `std::` qualifier.

Make liberal use of the `const` keyword whenever possible–this will help avoid bugs later.

### File and Directory Conventions 

File names should be in written in snake case, such as `multi_cpu_driver.cpp`.

File names should reflect the class inside.

Header (.h) files are placed in include/.

Original source files (.cpp) should be placed in src/.

External dependency source should be placed in external/ and output libraries should be placed in lib/. Only check in Win64 & Mac OS X static libraries (.lib and .so respectively). 

Test cases should go in test/.

### Naming Conventions 

Preprocessor defintions should be in all-caps snake case: `A_PREPROCESSOR_DEFINITION`

Compile-time options should be denoted by placing two underscores before the phrase, such as: `__WITH_SUCH_FEATURE`.

Class, struct, and namespace declarations should be in `CamelCase`.

Variables within a class or struct declaration should be in `mixedCase`.

Denote internal members with m_, such as `m_genericPointer`.

Place a space after the opening parenthesis, before the closing parenthesis, and after the keyword. Additionally, braces should be placed on the following line. 

Example: 
```c++
if ( foo != std::nullptr )
{

}
```
