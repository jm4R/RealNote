#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "NoteModel.h"

#include <QMainWindow>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget* parent = nullptr);
    ~MainWindow();

    void setNote(NoteModel& note);
    void updateNote();

signals:
    void saveInvoked();

private:
    Ui::MainWindow* ui;
    NoteModel* note_;
};

#endif // MAINWINDOW_H
