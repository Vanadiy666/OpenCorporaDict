#pragma once

#include <QMainWindow>

namespace OpenCorpora
{
class cMorphologicalDictionary;
class cWordForm;
}

namespace MorphologicalDictionarySimpleGui {

namespace Ui { class cMainWindow; }

class cMainWindow : public QMainWindow
{
    Q_OBJECT

public:
    cMainWindow(QWidget *parent = nullptr);
    ~cMainWindow() override;

    void setData(OpenCorpora::cMorphologicalDictionary * analyzer);
private slots:
    void on_searchButton__clicked();

private:
    Ui::cMainWindow *ui;
    OpenCorpora::cMorphologicalDictionary * analyzer_;

    QString getAllWordFormsText(const QList<const OpenCorpora::cWordForm *> & wordForms) const;
    QString getAllGrammemesText(const OpenCorpora::cWordForm * wordForm) const;
};

} // namespace MorphAnalyzerGui
