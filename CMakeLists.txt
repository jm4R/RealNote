cmake_minimum_required(VERSION 3.13)
project(RealNote LANGUAGES CXX VERSION 1.0)

#Qt
find_package(Qt5 REQUIRED COMPONENTS Core Gui Widgets Network Svg)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

#QCodeEditor
add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/ThirdParty/QCodeEditor)

include_directories(
    ${PROJECT_SOURCE_DIR}
    ${QCODEEDITOR_INCLUDE_ROOT}
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
    View/MainMenu.hpp
    View/MainView.hpp
    View/MainWindow.hpp
    View/QtUtils.hpp
    View/TextEditor.hpp

    Res/Resources.qrc
)

target_compile_features(${PROJECT_NAME} PRIVATE cxx_std_17)

target_link_libraries(${PROJECT_NAME}
    Qt5::Widgets
    Qt5::Network
    Qt5::Svg
    qcodeeditor
    )
