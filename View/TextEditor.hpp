#ifndef TEXTEDITOR_H
#define TEXTEDITOR_H

#include <QCodeEditor/QCodeEditor.hpp>
#include <QCodeEditor/QCodeEditorTextFinder.hpp>
#include <QWidget>

class TextEditor : public QCodeEditor
{
    using QCodeEditor::QCodeEditor;
};

class TextFinder : public QCodeEditorTextFinder
{
    using QCodeEditorTextFinder::QCodeEditorTextFinder;
};

class TextEditorTheme : public QCodeEditorDesign
{
    using QCodeEditorDesign::QCodeEditorDesign;
};

#endif // TEXTEDITOR_H
