#ifndef MAINCONTROLLER_H
#define MAINCONTROLLER_H

#include "MainWindow.h"
#include "NoteModel.h"

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
    NoteModel note_; // FIXME: use tree structure here
};

#endif // MAINCONTROLLER_H
