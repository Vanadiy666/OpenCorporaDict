#include "cMorphologicalDictionary.h"

#include <iostream>

namespace OpenCorpora
{
    cMorphologicalDictionary::~cMorphologicalDictionary()
    {
        clear();
    }

    QPair<QString, cGrammeme*> cMorphologicalDictionary::parseGrammeme(QXmlStreamReader &xml)
    {
        QString parentName = parseGrammemeParent(xml);
        std::unique_ptr< cGrammeme > grammeme( new cGrammeme() );
        while (!xml.atEnd() && !xml.hasError())
        {
            QXmlStreamReader::TokenType token = xml.readNext();
            if (token == QXmlStreamReader::StartElement)
            {
                if(xml.name() == QString("name"))
                    grammeme->setInnerId( xml.readElementText() );
                else if(xml.name() == QString("alias"))
                    grammeme->setOutterId( xml.readElementText() );
                else if(xml.name() == QString("description"))
                    grammeme->setDescription( xml.readElementText() );
            }
            if(token == QXmlStreamReader::EndElement && xml.name() == QString("grammeme"))
                break;
        }

        return QPair<QString, cGrammeme*>(parentName, grammeme.release() );
    }

    QString cMorphologicalDictionary::parseGrammemeParent(QXmlStreamReader &xml)
    {
        QXmlStreamAttributes attributes = xml.attributes();
        if(!attributes.hasAttribute("parent"))
            throw cMorphologicalDictionaryFileFormatException(QObject::tr("Tag 'grammeme' have not attribute 'parent'."));
        return attributes.value("parent").toString();
    }

    QMultiMap<QString, const cWordForm *> cMorphologicalDictionary::createWordFormByTextSearchMap(const QVector<cParadigm *> &paradigms)
    {
        QMultiMap<QString, const cWordForm *> result;
        for(const auto & paradigm : paradigms)
            for(const auto & wordForm : paradigm->wordForms())
                result.insert(wordForm->text(), wordForm);
        return result;
    }
    QString cMorphologicalDictionary::parseWordFormText(QXmlStreamReader &xml)
    {
        QXmlStreamAttributes attributes = xml.attributes();
        if(!attributes.hasAttribute("t"))
            throw cMorphologicalDictionaryFileFormatException(QObject::tr("Tag 'f'/'l' have not attribute 't'."));

        return attributes.value("t").toString();
    }

    void cMorphologicalDictionary::loadVocabulary(QXmlStreamReader &xml)
    {

        while (!xml.atEnd() && !xml.hasError())
        {
            QXmlStreamReader::TokenType token = xml.readNext();
            if (token == QXmlStreamReader::StartDocument)
                continue;
            if (token == QXmlStreamReader::StartElement)
            {
                if(xml.name() == QString("grammemes"))
                {
                    parseGrammemes(xml);
                }
                if(xml.name() == QString("lemmata"))
                {
                    parseParadigms(xml);
                }
            }
            if(token == QXmlStreamReader::EndDocument)
                break;
        }
    }

    cGrammeme* cMorphologicalDictionary::findGrammemeByInnerId(const QString &innerId)
    {
        for( auto grammeme : grammemes_)
        {
            if(innerId == grammeme->innerId())
                return grammeme;
        }
        return nullptr;
    }
    void cMorphologicalDictionary::parseGrammemes(QXmlStreamReader &xml)
    {
        QVector<QString> parentsNames;

        while (!xml.atEnd() && !xml.hasError())
        {
            QXmlStreamReader::TokenType token = xml.readNext();
            if (token == QXmlStreamReader::StartElement)
            {
                if(xml.name() == QString("grammeme"))
                {
                    QPair<QString, cGrammeme *> grammemeInfo = parseGrammeme(xml);
                    parentsNames.push_back(grammemeInfo.first);
                    grammemes_.push_back(grammemeInfo.second);
                }
            }
            if(token == QXmlStreamReader::EndElement && xml.name() == QString("grammemes"))
                break;
        }

        for(qsizetype i = 0; i < parentsNames.size(); i++)
        {
            grammemes_[i]->setParent( findGrammemeByInnerId(parentsNames[i]) );
        }
    }
    void cMorphologicalDictionary::parseParadigms(QXmlStreamReader &xml)
    {
        while (!xml.atEnd() && !xml.hasError())
        {
            QXmlStreamReader::TokenType token = xml.readNext();
            if (token == QXmlStreamReader::StartElement)
            {
                if(xml.name() == QString("lemma"))
                {
                    cParadigm * paradigm = parseParadigm(xml).release();
                    paradigms_.push_back(paradigm);
                }
            }
            if(token == QXmlStreamReader::EndElement && xml.name() == QString("lemmata"))
                break;
        }
        wordFormByTextSearchMap_ = createWordFormByTextSearchMap(paradigms_);
    }

    std::unique_ptr<cParadigm> cMorphologicalDictionary::parseParadigm(QXmlStreamReader &xml)
    {
        std::unique_ptr<cParadigm> paradigm( new cParadigm() );
        QVector<cWordForm *> wordForms;

        bool thereIsABaseForm = false;
        while (!xml.atEnd() && !xml.hasError())
        {
            QXmlStreamReader::TokenType token = xml.readNext();
            if (token == QXmlStreamReader::StartElement)
            {
                if(xml.name() == QString("l"))
                {
                    if(thereIsABaseForm)
                        throw cMorphologicalDictionaryFileFormatException(QObject::tr("Tag 'lemma' have more than one tag 'l'."));

                    cWordForm * wordForm = parseWordForm(xml, "l").release();
                    wordForm->setParadigm(paradigm.get());
                    paradigm->setBaseForm( wordForm );

                    thereIsABaseForm = true;
                }
                if(xml.name() == QString("f"))
                {
                    cWordForm * wordForm = parseWordForm(xml, "f").release();
                    wordForm->setParadigm(paradigm.get());
                    wordForms.push_back(wordForm);
                }
            }
            if(token == QXmlStreamReader::EndElement && xml.name() == QString("lemma"))
                break;
        }
        paradigm->setWordForms(std::move( wordForms ));
        return paradigm;
    }
    std::unique_ptr< cWordForm> cMorphologicalDictionary::parseWordForm(QXmlStreamReader &xml, const QString & wordFormType)
    {
        const QString word = parseWordFormText(xml);
        QVector<cGrammeme*> grammemes = parseWordFormGrammemes(xml, wordFormType);

        return std::unique_ptr< cWordForm>(new cWordForm(word, grammemes) );
    }

    QVector<cGrammeme*> cMorphologicalDictionary::parseWordFormGrammemes(QXmlStreamReader &xml, const QString &wordFormType)
    {
        QVector<cGrammeme *> result;
        while (!xml.atEnd() && !xml.hasError())
        {
            QXmlStreamReader::TokenType token = xml.readNext();
            if (token == QXmlStreamReader::StartElement)
            {
                if(xml.name() == QString("g"))
                {
                    QXmlStreamAttributes attributes = xml.attributes();
                    if(!attributes.hasAttribute("v"))
                        throw cMorphologicalDictionaryFileFormatException(QObject::tr("Tag 'g' have not attribute 'v'."));
                    const QString grammemeInnerId = attributes.value("v").toString();
                    cGrammeme * grammeme = findGrammemeByInnerId(grammemeInnerId);
                    result.push_back(grammeme);
                }
            }
            else if(token == QXmlStreamReader::EndElement && xml.name() == wordFormType)
                break;
        }
        return result;
    }

    void cMorphologicalDictionary::clear()
    {
        for( auto grammeme : grammemes_)
        {
            if(grammeme)
                delete grammeme;
        }
        grammemes_.clear();
        for(auto paradigm : paradigms_)
        {
            if(paradigm)
                delete paradigm;
        }
        paradigms_.clear();
        wordFormByTextSearchMap_.clear();
    }
    QList<const cWordForm*> cMorphologicalDictionary::findWordFormByText(const QString & text)
    {
        return wordFormByTextSearchMap_.values(text.toLower());
    }

    void cMorphologicalDictionary::loadVocabulary(const QString &vocabularyFilePath)
    {
        QFile file(vocabularyFilePath);
        if (!file.open(QIODevice::ReadOnly | QIODevice::Text))
        {
            throw cMorphologicalDictionaryException(QObject::tr("Failed to read dictionary file '%1'.").arg(vocabularyFilePath));
        }
        QXmlStreamReader xml(&file);
        loadVocabulary(xml);
    }
}
