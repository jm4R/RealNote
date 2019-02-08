#ifndef MAINCONTROLLER_H
#define MAINCONTROLLER_H

#include "MainWindow.hpp"
#include "NoteModel.hpp"
#include "NotesContainer.hpp"

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
    NotesContainer notes_;
    NoteModel* note_; // FIXME: use tree structure here
};

#endif // MAINCONTROLLER_H
