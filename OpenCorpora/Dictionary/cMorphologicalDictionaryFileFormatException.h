#pragma once

#include "cMorphologicalDictionaryException.h"

namespace OpenCorpora {

class OPENCORPORA_EXPORT cMorphologicalDictionaryFileFormatException: public cMorphologicalDictionaryException
{
public:
    cMorphologicalDictionaryFileFormatException(const QString & message);
};

} // namespace MorphologicalAnalysis

