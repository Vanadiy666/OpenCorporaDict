# OpenCorporaDict
## Introduction
This is the solution to a test task that I once completed. This project is not a finished product or final solution.

It's a Morphological analyze library based on the OpenCorpora dictionary.
Project contains:
- library that implements morphological parsing based on the [OpenCorpora dictionary](http://opencorpora.org).
The library is simple, it loads all the necessary dictionary data (xml format) into RAM (about 1.5 gigabytes) and it takes about a minute for the initial download.
The library does not solve the problem of ambiguity and the presence of the letters "е"/"ё" in words;
- test application that demonstrates the functionality of the library.
## Project build
The Qbs build system was used with the help of QtCreator IDE.
Project build tested under msvc 16.11 and mingv 11.2.0 compilers using qt 6.2.4.
And i think, it can be build under gcc and clang compilers too.
## Launch of MorphologicalDictionarySimpleGui test application


https://user-images.githubusercontent.com/72406877/233347228-ff309193-a630-40b3-a7fa-0bad6cd9222c.mp4


Launch instruction contains of steps:
- pass as a start parameter in the console the absolute path to the xml data of the OpenCorpora dictionary;
- wait for 1-2 minutes of loading;
- use.
