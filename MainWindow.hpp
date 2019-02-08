#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "NoteModel.hpp"

#include <QMainWindow>

class MainMenu;
class MainView;
class QAbstractItemModel;

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget* parent = nullptr);
    ~MainWindow();

    void setNote(NoteModel& note);
    void setNotesTreeModel(QAbstractItemModel& model);
    void updateNote();

signals:
    void saveInvoked();
    void noteChoosed(const QModelIndex& index);

private:
    MainView* mainView_;
    MainMenu* mainMenu_;
    NoteModel* note_;
};

#endif // MAINWINDOW_H
