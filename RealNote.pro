#-------------------------------------------------
#
# Project created by QtCreator 2018-10-11T17:49:25
#
#-------------------------------------------------

QT       += core gui network widgets

CONFIG += c++17

TARGET = RealNote
TEMPLATE = app

# The following define makes your compiler emit warnings if you use
# any feature of Qt which has been marked as deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0


SOURCES += \
        main.cpp \
        MainWindow.cpp \
    MainController.cpp \
    ThirdParty/QCodeEditor/src/Design/QCodeEditorDesign.cpp \
    ThirdParty/QCodeEditor/src/Design/QCodeEditorSheets.cpp \
    ThirdParty/QCodeEditor/src/Design/QLineColumnPadding.cpp \
    ThirdParty/QCodeEditor/src/Design/QSyntaxRule.cpp \
    ThirdParty/QCodeEditor/src/Design/XmlHelper.cpp \
    ThirdParty/QCodeEditor/src/Widgets/QCodeEditor.cpp \
    ThirdParty/QCodeEditor/src/Widgets/QCodeEditorEvents.cpp \
    ThirdParty/QCodeEditor/src/Widgets/QCodeEditorHighlighter.cpp \
    ThirdParty/QCodeEditor/src/Widgets/QCodeEditorLineWidget.cpp \
    ThirdParty/QCodeEditor/src/Widgets/QCodeEditorPopup.cpp \
    ThirdParty/QCodeEditor/src/Widgets/QCodeEditorSlots.cpp \
    ThirdParty/QCodeEditor/src/Widgets/QCodeEditorTextFinder.cpp \
    View/MainView.cpp \
    View/MainMenu.cpp \
    FilesUtils.cpp \
    Model/NoteModel.cpp \
    Model/NotesContainer.cpp \
    Model/ApplicationContext.cpp \
    Model/CategorizedListModel.cpp

HEADERS += \
    ThirdParty/QCodeEditor/include/KGL/Design/QCodeEditorDesign.hpp \
    ThirdParty/QCodeEditor/include/KGL/Design/QCodeEditorSheets.hpp \
    ThirdParty/QCodeEditor/include/KGL/Design/QLineColumnPadding.hpp \
    ThirdParty/QCodeEditor/include/KGL/Design/QSyntaxRule.hpp \
    ThirdParty/QCodeEditor/include/KGL/Design/XmlHelper.hpp \
    ThirdParty/QCodeEditor/include/KGL/Widgets/QCodeEditor.hpp \
    ThirdParty/QCodeEditor/include/KGL/Widgets/QCodeEditorHighlighter.hpp \
    ThirdParty/QCodeEditor/include/KGL/Widgets/QCodeEditorLineWidget.hpp \
    ThirdParty/QCodeEditor/include/KGL/Widgets/QCodeEditorPopup.hpp \
    ThirdParty/QCodeEditor/include/KGL/Widgets/QCodeEditorTextFinder.hpp \
    ThirdParty/QCodeEditor/include/KGL/KGLConfig.hpp \
    View/QtUtils.hpp \
    View/MainView.hpp \
    View/TextEditor.hpp \
    View/MainMenu.hpp \
    FilesUtils.hpp \
    MainController.hpp \
    MainWindow.hpp \
    Model/Global.hpp \
    Commands.hpp \
    Model/ApplicationContext.hpp \
    Model/NoteModel.hpp \
    Model/NotesContainer.hpp \
    Model/CategorizedListModel.hpp

INCLUDEPATH += \
    ThirdParty/QCodeEditor/include

RESOURCES += \
    Style.qrc
