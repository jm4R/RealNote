#include "MainWindow.hpp"

#include "View/MainMenu.hpp"
#include "View/MainView.hpp"
#include "View/TextEditor.hpp"

#include <QShortcut>
#include <QTreeView>
#include <QWidget>

MainWindow::MainWindow(QWidget* parent) : QMainWindow{parent}
{
    mainView_ = new MainView{this};
    setCentralWidget(mainView_);
    mainMenu_ = new MainMenu{this};
    setMenuBar(mainMenu_);

    /*kgl::QCodeEditorDesign design;
    design.setLineColumnBackColor(0xff232323);
    design.setLineColumnSeparatorColor(0xff000000);
    design.setEditorBackColor(0xff000000);
    design.setEditorTextColor(0xffeeeeee);*/

    QShortcut* saveShortcut = new QShortcut{QKeySequence{QKeySequence::Save}, this};
    connect(saveShortcut, &QShortcut::activated, this, &MainWindow::saveInvoked);
    QShortcut* findShortcut = new QShortcut{QKeySequence{QKeySequence::Find}, this};
    connect(findShortcut, &QShortcut::activated, [this] { mainView_->toggleTextFinder(); });
    connect(mainView_->treeView, &QTreeView::activated, this, &MainWindow::noteChoosed);
}

MainWindow::~MainWindow()
{
}

void MainWindow::setNote(NoteModel& note)
{
    note_ = &note;
    updateNote();
}

void MainWindow::setNotesTreeModel(QAbstractItemModel& model)
{
    mainView_->treeView->setModel(&model);
}

void MainWindow::updateNote()
{
    static auto ag = new QActionGroup(this);
    mainView_->textEdit->setDocument(&note_->document());
    mainMenu_->history->clear();
    QAction* action = mainMenu_->history->addAction(tr("Current"));
    ag->addAction(action);
    action->setCheckable(true);
    action->setChecked(true);
    mainMenu_->history->addSeparator();
    int i = 0;
    for (const auto& version : note_->versions())
    {
        QAction* action =
                mainMenu_->history->addAction(QString::number(++i) + ".  " + NoteModel::humanReadableVersion(version));
        ag->addAction(action);
        action->setCheckable(true);
        action->setEnabled(false); // TODO: temp
    }
}
