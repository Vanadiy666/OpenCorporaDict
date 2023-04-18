#pragma once

#include <QString>
#include <QSharedPointer>

#include "../OpenCorporaDefs.h"

namespace OpenCorpora {

class OPENCORPORA_EXPORT cGrammeme
{
public:
    cGrammeme();
    cGrammeme(const QString & innerId, const QString & outterId, const QString & description, cGrammeme* parent = nullptr);

    const QString & description() const;
    const QString & innerId() const;
    const QString & outterId() const;
    const cGrammeme* parent() const;

    void setDescription(const QString & description);
    void setInnerId(const QString & innerId);
    void setOutterId(const QString & outterId);
    void setParent(cGrammeme * parent);
private:
    QString innerId_;
    QString outterId_;
    QString description_;
    cGrammeme* parent_;
};

using CGrammeme = QSharedPointer<cGrammeme>;

} // namespace MorphologicalAnalysis

