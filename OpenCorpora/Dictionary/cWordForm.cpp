#include "cWordForm.h"

namespace OpenCorpora {

cWordForm::cWordForm(const QString &word, const QVector<cGrammeme *> &grammemes, cParadigm* paradigm)
    : text_(word),
      grammemes_(grammemes),
      paradigm_(paradigm)
{
}

const QVector<cGrammeme*> & cWordForm::grammemes() const
{
    return grammemes_;
}

const cParadigm *cWordForm::paradigm() const
{
    return paradigm_;
}

cParadigm *cWordForm::paradigm()
{
    return paradigm_;
}

const QString &cWordForm::text() const
{
    return text_;
}

void cWordForm::setGrammemes(const QVector<cGrammeme *> &grammemes)
{
    grammemes_ = grammemes;
}

void cWordForm::setParadigm(cParadigm *paradigm)
{
    paradigm_ = paradigm;
}

void cWordForm::setText(const QString &text)
{
    text_ = text;
}

} // namespace MorphologicalAnalysis
