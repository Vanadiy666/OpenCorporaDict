#include "cParadigm.h"

#include <cassert>

namespace OpenCorpora {

cParadigm::cParadigm()
    : baseForm_(nullptr)
{
}

cParadigm::~cParadigm()
{
    for(auto wordForm : wordForms_)
    {
        if(wordForm)
            delete wordForm;
    }
    if(baseForm_)
        delete baseForm_;
}

const cWordForm* cParadigm::baseForm() const
{
    return baseForm_;
}

cWordForm* cParadigm::baseForm()
{
    return baseForm_;
}

const QVector<cWordForm *> &cParadigm::wordForms() const
{
    return wordForms_;
}

void cParadigm::setBaseForm(cWordForm *baseForm)
{
    assert(!baseForm_);

    baseForm_ = baseForm;
}

void cParadigm::setWordForms(const QVector<cWordForm *> &wordForms)
{
    assert(wordForms_.isEmpty());

    wordForms_ = wordForms;
}

} // namespace MorphologicalAnalysis
