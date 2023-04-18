#include "cMorphologicalDictionaryException.h"

namespace OpenCorpora {

cMorphologicalDictionaryException::cMorphologicalDictionaryException(const QString & message):
    message_(message.toUtf8())
{
}

const char *cMorphologicalDictionaryException::what() const noexcept
{
    return message_.data();
}

} // namespace MorphologicalAnalysis
