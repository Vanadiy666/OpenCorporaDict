#pragma once

#include <utility>
#include <vector>
#include <algorithm>
#include <iterator>

#include <QString>
#include <QtXml>

#include "cParadigm.h"
#include "cMorphologicalDictionaryFileFormatException.h"

namespace OpenCorpora
{
class OPENCORPORA_EXPORT cMorphologicalDictionary
{
public:
    cMorphologicalDictionary() = default;
    ~cMorphologicalDictionary();

    QList<const cWordForm *> findWordFormByText(const QString & text);
    void loadVocabulary(const QString & vocabularyFilePath);
    void loadVocabulary(QXmlStreamReader &xml);
private:
    QVector<cParadigm*> paradigms_;
    QVector<cGrammeme*> grammemes_;
    QMultiMap<QString, const cWordForm*> wordFormByTextSearchMap_;

    static QPair<QString, cGrammeme* > parseGrammeme(QXmlStreamReader &xml);
    static QString parseGrammemeParent(QXmlStreamReader &xml);
    static QMultiMap<QString, const cWordForm*> createWordFormByTextSearchMap(const QVector<cParadigm*> & paradigms);
    static QString parseWordFormText(QXmlStreamReader &xml);

    cGrammeme* findGrammemeByInnerId(const QString & innerId);
    void parseGrammemes(QXmlStreamReader &xml);
    void parseParadigms(QXmlStreamReader &xml);
    std::unique_ptr<cParadigm> parseParadigm(QXmlStreamReader &xml);
    std::unique_ptr<cWordForm> parseWordForm(QXmlStreamReader &xml, const QString & wordFormType);
    QVector<cGrammeme*> parseWordFormGrammemes(QXmlStreamReader &xml, const QString &wordFormType);

    void clear();
};
}
