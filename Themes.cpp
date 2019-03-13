#include "Themes.hpp"

#include "View/TextEditor.hpp"

#include <QPainter>
#include <QPixmap>
#include <QSvgRenderer>

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
    theme.setEditorBorder({1, 1, 1, 1});
    theme.setEditorBorderColor(0xff232425);
    return theme;
}

QPixmap& Themes::noteIcon()
{
    static auto icon = loadIcon(":/res/icons/note.svg", 16);
    return icon;
}

QPixmap& Themes::categoryIcon()
{
    static auto icon = loadIcon(":/res/icons/category.svg", 24);
    return icon;
}

QPixmap Themes::loadIcon(const char* resourceName, int size)
{
    QSvgRenderer renderer{QString{resourceName}};
    QPixmap result{size, size};
    result.fill(QColor(0, 0, 0, 0));
    QPainter painter{&result};
    renderer.render(&painter, result.rect());
    return result;
}
