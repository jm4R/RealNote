#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

class MainMenu;
class MainView;
class QAbstractItemModel;
class NoteModel;

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget* parent = nullptr);
    ~MainWindow();

    void setNotesTreeModel(QAbstractItemModel& model);

signals:
    void saveInvoked();
    void noteChoosed(const QModelIndex& index);
    void addNote(const QModelIndex& index, const QString& name);

private slots:
    void reloadNote();

private:
    MainView* mainView_;
    MainMenu* mainMenu_;
};

#endif // MAINWINDOW_H
