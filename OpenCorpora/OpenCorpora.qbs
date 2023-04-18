import qbs
import qbs.FileInfo

DynamicLibrary { 

    destinationDirectory:  "libs" 
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
    cpp.defines: ["OPENCORPORA_DLL=1"]

    cpp.cxxLanguageVersion: {"c++17"}

    Depends { name: "Qt.core" }
    Depends { name: "Qt.xml" }

    Export {
        Depends { name: "cpp" }
        cpp.includePaths: [
                    FileInfo.path( product.sourceDirectory )
                ]
    }
}
