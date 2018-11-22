#include "MainWindow.h"
#include "ui_MainWindow.h"

#include <QShortcut>
#include <QActionGroup>
#include <KGL/Design/QCodeEditorDesign.hpp>

namespace {

enum class Node
{
    Folder,
    Document
};

QTreeWidgetItem* makeItem(QString text, Node node = Node::Document)
{
    static const auto documentIcon = QIcon::fromTheme("document");
    static const auto folderIcon = QIcon::fromTheme("folder");
    auto result = new QTreeWidgetItem{QStringList{} << text};
    result->setIcon(0, node == Node::Document ? documentIcon : folderIcon);
    return result;
}
} // namespace

MainWindow::MainWindow(QWidget* parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    auto p = makeItem("parent", Node::Folder);
    p->addChild(makeItem("c1"));
    p->addChild(makeItem("c2"));
    ui->treeWidget->addTopLevelItem(p);
    kgl::QCodeEditorDesign design;
    design.setLineColumnBackColor(0xff232323);
    design.setLineColumnSeparatorColor(0xff000000);
    ui->plainTextEdit->setDesign(design);;
    //ui->treeWidget->hide();

    QShortcut* saveShortcut = new QShortcut{QKeySequence{QKeySequence::Save}, this};
    connect(saveShortcut, &QShortcut::activated, this, &MainWindow::saveInvoked);
    QShortcut* findShortcut = new QShortcut{QKeySequence{QKeySequence::Find}, this};
    connect(findShortcut, &QShortcut::activated, [this]{ui->plainTextEdit->showTextFinder();});
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
