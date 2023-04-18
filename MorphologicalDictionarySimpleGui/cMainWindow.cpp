#include "cMainWindow.h"
#include "./ui_cMainWindow.h"

#include <QMessageBox>

#include <cassert>

#include <OpenCorpora/Dictionary/cMorphologicalDictionary.h>

namespace MorphologicalDictionarySimpleGui {

cMainWindow::cMainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::cMainWindow),
      analyzer_(nullptr)
{
    ui->setupUi(this);

    ui->analysisResult_->setPlainText("Dictionary loading...");
}

cMainWindow::~cMainWindow()
{
    delete ui;
}

void cMainWindow::setData(OpenCorpora::cMorphologicalDictionary *analyzer)
{
    assert(analyzer);

    analyzer_ = analyzer;
    ui->analysisResult_->clear();
    setEnabled(true);
}


void cMainWindow::on_searchButton__clicked()
{
    if(ui->wordForAnalysis_->text().isEmpty())
    {
        QMessageBox::warning(this, "Warning","Enter a word to search.");
        return;
    }

    auto wordForms = analyzer_->findWordFormByText(ui->wordForAnalysis_->text());
    if(wordForms.isEmpty())
    {
        const QString noResultsText = QString("No results found for the word \"%1\".").arg(ui->wordForAnalysis_->text());
        ui->analysisResult_->setPlainText(noResultsText);
    }
    else
        ui->analysisResult_->setPlainText(getAllWordFormsText(wordForms));
}

QString cMainWindow::getAllWordFormsText(const QList<const OpenCorpora::cWordForm *> &wordForms) const
{
    QStringList wordFormsTextParts;

    for(const auto wordForm : wordForms)
    {
        wordFormsTextParts << QString("\"%1\" от \"%2\", %3").arg( wordForm->text() )
                              .arg( wordForm->paradigm()->baseForm()->text())
                              .arg(getAllGrammemesText(wordForm));
    }

    return wordFormsTextParts.join("\n");
}

QString cMainWindow::getAllGrammemesText(const OpenCorpora::cWordForm *wordForm) const
{
    assert(wordForm);

    QStringList grammemesTextParts;

    for( const auto grammeme : wordForm->paradigm()->baseForm()->grammemes())
        grammemesTextParts << grammeme->outterId().toLower();
    for( const auto grammeme : wordForm->grammemes())
        grammemesTextParts << grammeme->outterId().toLower();

    return grammemesTextParts.join(", ");
}


} // namespace MorphAnalyzerGui
