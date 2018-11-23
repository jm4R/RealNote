#include "MainMenu.hpp"

MainMenu::MainMenu(QWidget* parent) : QMenuBar{parent}
{
    history = addMenu(tr("History"));
}
