#include "View/MainWindow.hpp"

#include "Model/ApplicationContext.hpp"
#include "Model/NoteModel.hpp"
#include "Themes.hpp"
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

    setWindowIcon(QIcon(":/res/icons/icon.png"));
    mainView_->textEdit->setDesign(Themes::textEditTheme());

    // generate signals:
    QShortcut* saveShortcut = new QShortcut{QKeySequence{QKeySequence::Save}, this}; // TODO: QAction
    connect(saveShortcut, &QShortcut::activated, this, &MainWindow::saveInvoked);
    QShortcut* findShortcut = new QShortcut{QKeySequence{QKeySequence::Find}, this};
    connect(findShortcut, &QShortcut::activated, [this] { mainView_->toggleTextFinder(); });
    connect(mainView_->treeView, &QTreeView::activated, this, &MainWindow::noteChoosed);
    connect(mainView_, &MainView::addNote, this, &MainWindow::addNote);
    connect(mainView_, &MainView::removeNote, this, &MainWindow::removeNote);
    connect(mainView_, &MainView::addCategory, this, &MainWindow::addCategory);
    connect(mainView_, &MainView::removeCategory, this, &MainWindow::removeCategory);

    // connect slots:
    connect(&context->notes, &NotesContainer::loadedChanged, this, &MainWindow::reloadNote);

    context->window = this;
}

MainWindow::~MainWindow()
{
}

void MainWindow::setNotesTreeModel(QAbstractItemModel& model)
{
    mainView_->treeView->setModel(&model);
}

void MainWindow::reloadNote()
{
    if (!context->note)
        return;
    static auto ag = new QActionGroup(this);
    mainView_->textEdit->setDocument(&context->note->document());
    mainMenu_->history->clear();
    QAction* action = mainMenu_->history->addAction(tr("Current"));
    ag->addAction(action);
    action->setCheckable(true);
    action->setChecked(true);
    mainMenu_->history->addSeparator();
    int i = 0;
    for (const auto& version : context->note->versions())
    {
        QAction* action =
                mainMenu_->history->addAction(QString::number(++i) + ".  " + NoteModel::humanReadableVersion(version));
        ag->addAction(action);
        action->setCheckable(true);
        action->setEnabled(false); // TODO: temp
    }
}
