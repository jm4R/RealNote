#ifndef THEMES_HPP
#define THEMES_HPP

class TextEditorTheme;
class QPixmap;

class Themes
{
public:
    static const char* style();
    static TextEditorTheme textEditTheme();
    static QPixmap& noteIcon();
    static QPixmap& categoryIcon();
    static QPixmap loadIcon(const char* resourceName, int size);
};

#endif // THEMES_HPP
