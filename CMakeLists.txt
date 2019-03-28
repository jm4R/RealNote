cmake_minimum_required(VERSION 3.13)
project(RealNote LANGUAGES CXX VERSION 1.0)

#Qt
find_package(Qt5 REQUIRED COMPONENTS Core Gui Widgets Network Svg)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

#QCodeEditor
add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/third_party/QCodeEditor)

include_directories(
    ${PROJECT_SOURCE_DIR}/src
    ${QCODEEDITOR_INCLUDE_ROOT}
)

add_executable(${PROJECT_NAME}
    ${MOC_SOURCES}
    src/Commands.cpp
    src/FilesUtils.cpp
    src/MainController.cpp
    src/main.cpp
    src/Model/ApplicationContext.cpp
    src/Model/CategorizedListModel.cpp
    src/Model/NoteModel.cpp
    src/Model/NotesContainer.cpp
    src/Themes.cpp
    src/View/MainMenu.cpp
    src/View/MainView.cpp
    src/View/MainWindow.cpp

    src/Commands.hpp
    src/FilesUtils.hpp
    src/MainController.hpp
    src/Model/ApplicationContext.hpp
    src/Model/CategorizedListModel.hpp
    src/Model/Global.hpp
    src/Model/NoteModel.hpp
    src/Model/NotesContainer.hpp
    src/Themes.hpp
    src/View/MainMenu.hpp
    src/View/MainView.hpp
    src/View/MainWindow.hpp
    src/View/QtUtils.hpp
    src/View/TextEditor.hpp

    res/Resources.qrc
)

target_compile_features(${PROJECT_NAME} PRIVATE cxx_std_17)

target_link_libraries(${PROJECT_NAME}
    Qt5::Widgets
    Qt5::Network
    Qt5::Svg
    qcodeeditor
    )
