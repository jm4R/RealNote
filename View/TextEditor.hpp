#ifndef TEXTEDITOR_H
#define TEXTEDITOR_H

#include <KGL/Widgets/QCodeEditor.hpp>
#include <KGL/Widgets/QCodeEditorTextFinder.hpp>
#include <QWidget>

class TextEditor : public kgl::QCodeEditor
{
    using QCodeEditor::QCodeEditor;
};

class TextFinder : public kgl::QCodeEditorTextFinder
{
    using QCodeEditorTextFinder::QCodeEditorTextFinder;
};

class TextEditorTheme : public kgl::QCodeEditorDesign
{
    using QCodeEditorDesign::QCodeEditorDesign;
};

#endif // TEXTEDITOR_H
