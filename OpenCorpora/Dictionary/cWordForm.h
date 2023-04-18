#pragma once

#include <QVector>

#include "cGrammeme.h"

namespace OpenCorpora {

class cParadigm;

class OPENCORPORA_EXPORT cWordForm
{
public:
    cWordForm(const QString & word, const QVector<cGrammeme *> & grammemes, cParadigm* paradigm = nullptr);

    const QVector<cGrammeme*> & grammemes() const;
    const cParadigm* paradigm() const;
    cParadigm* paradigm();
    const QString & text() const;
    void setGrammemes(const QVector<cGrammeme *> &grammemes);
    void setParadigm(cParadigm* paradigm);
    void setText(const QString & text);
private:
    QString text_;
    QVector<cGrammeme*> grammemes_;
    cParadigm* paradigm_;
};

using CWordForm = QSharedPointer<cWordForm>;

} // namespace MorphologicalAnalysis

