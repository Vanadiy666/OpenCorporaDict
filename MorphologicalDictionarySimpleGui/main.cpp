#include "cMainWindow.h"

#include <cassert>

#include <QApplication>

#include <OpenCorpora/Dictionary/cMorphologicalDictionary.h>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    assert(argc > 1 && "The required parameter of the path to the morphological dictionary file is not set.");

    MorphologicalDictionarySimpleGui::cMainWindow w;
    w.show();

    OpenCorpora::cMorphologicalDictionary dictionary;

    QThread * loader = QThread::create([&a, &dictionary, argv](){
        QString openCorporaDictionaryPath = argv[1];
        try
        {
            dictionary.loadVocabulary(openCorporaDictionaryPath);
        }
        catch(const OpenCorpora::cMorphologicalDictionaryException & ex)
        {
            qCritical() << QObject::tr("File parsing error. Details: %1").arg( ex.what() );
            a.exit(-1);
        }
    });
    QObject::connect(loader, &QThread::finished, &w, [&w, &dictionary, loader]{
        w.setData(&dictionary);
        loader->deleteLater();
    });
    loader->start();

    return a.exec();
}
