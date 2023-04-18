#pragma once

#include "exportImportMacro.h"

#ifndef OPENCORPORA_EXPORT
    #ifdef OPENCORPORA_DLL
        #define OPENCORPORA_EXPORT S_EXPORT
    #else
        #ifdef OPENCORPORA_SLL
            #define OPENCORPORA_EXPORT
        #else
            #define OPENCORPORA_EXPORT S_IMPORT
        #endif
    #endif
#endif
