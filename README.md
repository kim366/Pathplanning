[![Build Status](https://travis-ci.org/kim366/Pathplanning.svg?branch=master)](https://travis-ci.org/kim366/Pathplanning)

# Pathplanning
Various Pathplanning Algorithms Derived off Dijkstra's in multiple situations visualized by SFML

## Dependencies
[SFML Graphics Library](https://github.com/SFML/SFML)

[Catch Unit Testing Library](https://github.com/philsquared/Catch)

## Build Instructions
For Building cmake and a C++17 compiler is necessary (for example g++ 7.1 or Clang 4). The [MinGW-w64 fork](https://sourceforge.net/projects/mingw-w64) comes with g++ 7.1 and works for building this project.

[Download SFML ](https://www.sfml-dev.org/download/sfml/2.4.2/) for your compiler and place it within the project's root directory.

```
md build
cd build
cmake ..
```

And then invoke the appropriate command for your build system. Which may be `make`, `ninja` or opening the generated Visual Studio project file. A binary named "gui" will be generated.

Full example using MinGW:

```
md build
cd build
cmake -G "MinGW Makefiles" ..
mingw32-make
```

### Build Tests
To build tests first download the (Catch single include)[https://github.com/philsquared/Catch/blob/master/single_include] and place it as "catch.hpp" into the include folder. Then add `-DBUILD_TESTS=ON` when invoking cmake. The additional "tests" binary will be generated.
