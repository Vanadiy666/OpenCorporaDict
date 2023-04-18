#pragma once

#include "cWordForm.h"

namespace OpenCorpora {

class OPENCORPORA_EXPORT cParadigm
{
public:
    cParadigm();
    ~cParadigm();

    const cWordForm* baseForm() const;
    cWordForm* baseForm();
    const QVector<cWordForm*> & wordForms() const;
    void setBaseForm(cWordForm* baseForm);
    void setWordForms(const QVector<cWordForm*> & wordForms);
private:
    cWordForm* baseForm_;
    QVector<cWordForm*> wordForms_;
};

using CParadigm = QSharedPointer<cParadigm>;

} // namespace MorphologicalAnalysis

