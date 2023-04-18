#include "cGrammeme.h"

namespace OpenCorpora {

cGrammeme::cGrammeme()
    :parent_(nullptr)
{

}

cGrammeme::cGrammeme(const QString &innerId, const QString &outterId, const QString &description, cGrammeme* parent)
    :innerId_(innerId),
     outterId_(outterId),
     description_(description),
     parent_(parent)
{
}
const QString &  cGrammeme::description() const
{
    return description_;
}
const QString &cGrammeme::innerId() const
{
    return innerId_;
}

const QString &  cGrammeme::outterId() const
{
    return outterId_;
}
const cGrammeme *cGrammeme::parent() const
{
    return parent_;
}

void cGrammeme::setDescription(const QString &description)
{
    description_ = description;
}

void cGrammeme::setInnerId(const QString &innerId)
{
    innerId_ = innerId;
}

void cGrammeme::setOutterId(const QString &outterId)
{
    outterId_ = outterId;
}

void cGrammeme::setParent(cGrammeme *parent)
{
    parent_ = parent;
}

} // namespace MorphologicalAnalysis
