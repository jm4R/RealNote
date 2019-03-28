#ifndef MAINMENU_HPP
#define MAINMENU_HPP

#include <QMenuBar>

class QMenu;

class MainMenu : public QMenuBar
{
    Q_OBJECT
public:
    MainMenu(QWidget* parent = nullptr);

public:
    QMenu* history;
};

#endif // MAINMENU_HPP
