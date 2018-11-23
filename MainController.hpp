#ifndef MAINCONTROLLER_H
#define MAINCONTROLLER_H

#include "MainWindow.hpp"

#include <QList>
#include <QObject>

class MainController : public QObject
{
    Q_OBJECT
public:
    explicit MainController(QObject* parent = nullptr);

private slots:
    void save();

private:
    MainWindow window_;
};

#endif // MAINCONTROLLER_H
