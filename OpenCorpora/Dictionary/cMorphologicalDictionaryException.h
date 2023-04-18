#pragma once

#include <exception>

#include <QString>

#include "../OpenCorporaDefs.h"

namespace OpenCorpora {

class OPENCORPORA_EXPORT cMorphologicalDictionaryException : public std::exception
{
public:
    cMorphologicalDictionaryException(const QString & message);

    // exception interface
    virtual const char *what() const noexcept override;
private:
    QByteArray  message_;
};

} // namespace MorphologicalAnalysis

