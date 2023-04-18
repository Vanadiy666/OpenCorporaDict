import qbs.TextFile
import qbs.File
import qbs.FileInfo

Project {
    qbsSearchPaths: [
        sourceDirectory
    ]
    references: [
        "OpenCorpora/OpenCorpora.qbs",
        "MorphologicalDictionarySimpleGui/MorphologicalDictionarySimpleGui.qbs"
    ]
}
