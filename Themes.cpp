#include "Themes.hpp"

#include "View/TextEditor.hpp"

const char* Themes::style()
{
    return R"AA(
* {
    background-color: #404244;
    color: #BBBBBB;
    border-color: #333436;
    }
QPlainTextEdit, QTreeView {
    background-color: #2E2F30;
    color: #EEEEEE;
}

)AA";
}

TextEditorTheme Themes::textEditTheme()
{
    TextEditorTheme theme;
    theme.setLineColumnBackColor(0xff232323);
    theme.setLineColumnSeparatorColor(0xff000000);
    theme.setEditorBackColor(0xff000000);
    theme.setEditorTextColor(0xffeeeeee);
    theme.setEditorBorder({1,1,1,1});
    theme.setEditorBorderColor(0xff232425);
    return theme;
}
