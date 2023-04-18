import qbs
import qbs.FileInfo

QtGuiApplication {
    destinationDirectory:  "bin"
    consoleApplication: false
    files: [
        "**/*.cpp",
        "**/*.h",
        "**/*.hpp",
        "**/*.xml",
        "*.build",
        "**/*.json",
        "**/*.ui",
        "*.ignore"
    ]
    cpp.includePaths: [
        ".",
        FileInfo.path( product.sourceDirectory )
    ]

    Depends { name: "cpp" }
    cpp.cxxLanguageVersion: {"c++17"}

    Depends { name: "OpenCorpora" }

    Depends { name: "Qt.network" }
    Depends { name: "Qt.core" }
    Depends { name: "Qt.gui" }
    Depends { name: "Qt.widgets" }
    Depends { name: "Qt.xml" }

    Export {
        Depends { name: "cpp" }
        cpp.includePaths: [
                    FileInfo.path( product.sourceDirectory )
                ]
    }
}
