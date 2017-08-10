[![Build Status](https://travis-ci.org/kim366/Pathplanning.svg?branch=master)](https://travis-ci.org/kim366/Pathplanning)

# Pathplanning
Various Pathplanning Algorithms Derived off Dijkstra's in mulitple situations visualized by SFML

## Dependencies
[SFML Graphics Library](https://github.com/SFML/SFML)

[Catch Unit Testing Library](https://github.com/philsquared/Catch)

## Build Instructions

For Building a C++17 compiler is necessary (for example g++ 7.1 or Clang 4). The [MinGW-w64 fork](https://sourceforge.net/projects/mingw-w64) comes with g++ 7.1 and works for building this project.

Install SFML as shown in the [Getting Started section](https://www.sfml-dev.org/tutorials/2.1/#getting-started) of the SFML tutorial page.

On Windows also add the path of the `include` folder into the `CPLUS_INCLUDE_PATH` environment variable and the path to the `lib` folder into the `LIBRARY_PATH` environment variable if using Clang or gcc with MinGW.

Download the [Catch Single Include File](https://github.com/philsquared/Catch/blob/master/single_include/catch.hpp) and put the path to the contatining folder into the `CPLUS_INCLUDE_PATH` environment variable (separated by a semicolon). If using Visual Studio, add the file into the project properties.

In order to compile the repository simply type `make bld/gui` to build the gui application and `make bld/test` to build the unit tests. If using MinGW, do `mingw32-make` instead of `make`.
