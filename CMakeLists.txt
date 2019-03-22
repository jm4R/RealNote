cmake_minimum_required(VERSION 3.13)
project(RealNote LANGUAGES CXX VERSION 1.0)

set(CMAKE_CXX_STANDARD 17)

#find_package(Boost 1.69.0 REQUIRED)
find_package(Qt5 REQUIRED COMPONENTS Core Gui Widgets Network Svg)

set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

include_directories(
    ${PROJECT_SOURCE_DIR}
    ${PROJECT_SOURCE_DIR}/ThirdParty/QCodeEditor/include
)

add_executable(${PROJECT_NAME}
    ${MOC_SOURCES}
    Commands.cpp
    FilesUtils.cpp
    MainController.cpp
    main.cpp
    Model/ApplicationContext.cpp
    Model/CategorizedListModel.cpp
    Model/NoteModel.cpp
    Model/NotesContainer.cpp
    Themes.cpp
    ThirdParty/QCodeEditor/src/Design/QCodeEditorDesign.cpp
    ThirdParty/QCodeEditor/src/Design/QCodeEditorSheets.cpp
    ThirdParty/QCodeEditor/src/Design/QLineColumnPadding.cpp
    ThirdParty/QCodeEditor/src/Design/QSyntaxRule.cpp
    ThirdParty/QCodeEditor/src/Design/XmlHelper.cpp
    ThirdParty/QCodeEditor/src/Widgets/QCodeEditor.cpp
    ThirdParty/QCodeEditor/src/Widgets/QCodeEditorEvents.cpp
    ThirdParty/QCodeEditor/src/Widgets/QCodeEditorHighlighter.cpp
    ThirdParty/QCodeEditor/src/Widgets/QCodeEditorLineWidget.cpp
    ThirdParty/QCodeEditor/src/Widgets/QCodeEditorPopup.cpp
    ThirdParty/QCodeEditor/src/Widgets/QCodeEditorSlots.cpp
    ThirdParty/QCodeEditor/src/Widgets/QCodeEditorTextFinder.cpp
    View/MainMenu.cpp
    View/MainView.cpp
    View/MainWindow.cpp

    Commands.hpp
    FilesUtils.hpp
    MainController.hpp
    Model/ApplicationContext.hpp
    Model/CategorizedListModel.hpp
    Model/Global.hpp
    Model/NoteModel.hpp
    Model/NotesContainer.hpp
    Themes.hpp
    ThirdParty/QCodeEditor/include/KGL/Design/QCodeEditorDesign.hpp
    ThirdParty/QCodeEditor/include/KGL/Design/QCodeEditorSheets.hpp
    ThirdParty/QCodeEditor/include/KGL/Design/QLineColumnPadding.hpp
    ThirdParty/QCodeEditor/include/KGL/Design/QSyntaxRule.hpp
    ThirdParty/QCodeEditor/include/KGL/Design/XmlHelper.hpp
    ThirdParty/QCodeEditor/include/KGL/KGLConfig.hpp
    ThirdParty/QCodeEditor/include/KGL/Widgets/QCodeEditorHighlighter.hpp
    ThirdParty/QCodeEditor/include/KGL/Widgets/QCodeEditor.hpp
    ThirdParty/QCodeEditor/include/KGL/Widgets/QCodeEditorLineWidget.hpp
    ThirdParty/QCodeEditor/include/KGL/Widgets/QCodeEditorPopup.hpp
    ThirdParty/QCodeEditor/include/KGL/Widgets/QCodeEditorTextFinder.hpp
    View/MainMenu.hpp
    View/MainView.hpp
    View/MainWindow.hpp
    View/QtUtils.hpp
    View/TextEditor.hpp

    Res/Resources.qrc
)

target_link_librarieS(${PROJECT_NAME} Qt5::Widgets Qt5::Network Qt5::Svg)
