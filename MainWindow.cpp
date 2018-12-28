#include "MainWindow.h"
#include "ui_MainWindow.h"

#include "CategorizedListModel.h"

#include <QShortcut>
#include <QActionGroup>
#include <KGL/Design/QCodeEditorDesign.hpp>

namespace {

} // namespace

MainWindow::MainWindow(QWidget* parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    //ui->treeView->setModel(new CategorizedListModel());
    kgl::QCodeEditorDesign design;
    design.setLineColumnBackColor(0xff232323);
    design.setLineColumnSeparatorColor(0xff000000);
    design.setEditorBackColor(0xff000000);
    design.setEditorTextColor(0xffeeeeee);
    design.setTextFinderBackColor(0xff404244);
    ui->plainTextEdit->setDesign(design);;
    //ui->treeWidget->hide();

    QShortcut* saveShortcut = new QShortcut{QKeySequence{QKeySequence::Save}, this};
    connect(saveShortcut, &QShortcut::activated, this, &MainWindow::saveInvoked);
    QShortcut* findShortcut = new QShortcut{QKeySequence{QKeySequence::Find}, this};
    connect(findShortcut, &QShortcut::activated, [this]{ui->plainTextEdit->toggleTextFinder();});
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::setNote(NoteModel& note)
{
    note_ = &note;
    updateNote();
}

void MainWindow::setNotesTreeModel(QAbstractItemModel *model)
{
    ui->treeView->setModel(model);
}

void MainWindow::updateNote()
{
    static auto ag = new QActionGroup(this);
    ui->plainTextEdit->setDocument(&note_->document());
    ui->menuHistory->clear();
    QAction *action = ui->menuHistory->addAction(tr("Current"));
    ag->addAction(action);
    action->setCheckable(true);
    action->setChecked(true);
    ui->menuHistory->addSeparator();
    int i = 0;
    for (const auto& version : note_->versions())
    {
        QAction* action = ui->menuHistory->addAction(QString::number(++i) + ".  " +
                                                     NoteModel::humanReadableVersion(version));
        ag->addAction(action);
        action->setCheckable(true);
    }
}
