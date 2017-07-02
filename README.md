[![Build Status](https://travis-ci.org/kim366/Pathplanning.svg?branch=master)](https://travis-ci.org/kim366/Pathplanning)

# Pathplanning
Various Pathplanning Algorithms Derived off Dijkstra's in mulitple situations visualized by SFML

## Dependencies
[SFML Graphics Library](https://github.com/SFML/SFML)

[Catch Unit Testing Library](https://github.com/philsquared/Catch)

## Build Instructions

Install SFML as shown in the [Getting Started section](https://www.sfml-dev.org/tutorials/2.1/#getting-started) of the SFML tutorial page.

On Windows also add the path of the `include` folder into the `CPLUS_INCLUDE_PATH` environment variable and the path to the `lib` folder into the `LIBRARY_PATH` environment variable if using Clang or gcc with MinGW.

Download the [Catch Single Include File](https://github.com/philsquared/Catch/blob/master/single_include/catch.hpp) and put the path to the contatining folder into the `CPLUS_INCLUDE_PATH` environment variable (separated by a semicolon). If using Visual Studio, add the file into the project properties.

In order to compile the repository simply type `make gui` to build the gui application and `make tst` to build the unit tests. If using MinGW, use `mingw32-make` instead of `make`.
