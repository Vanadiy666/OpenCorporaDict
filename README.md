# OpenCorporaDict
## Introduction
It's a Morphological analyze library based on the OpenCorpora dictionary.
Project contains:
- library that implements morphological parsing based on the OpenCorpora dictionary.
The library is simple, it loads all the necessary dictionary data into RAM (about 1.5 gigabytes) and it takes about a minute for the initial download;
- test application that demonstrates the functionality of the library.
## Project build
The Qbs build system was used with the help of QtCreator IDE.
Project build tested under msvc 16.11 and mingv 11.2.0 compilers using qt 6.2.4.
And i think, it can be build under gcc and clang compilers too.
