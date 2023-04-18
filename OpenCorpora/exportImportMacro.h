#pragma once

#ifndef S_EXPORT
    #ifdef _MSC_VER
        #define S_EXPORT __declspec(dllexport)
    #else
        #define S_EXPORT
    #endif
#endif

#ifndef S_IMPORT
    #ifdef _MSC_VER
        #define S_IMPORT __declspec(dllimport)
    #else
        #define S_IMPORT
    #endif
#endif
