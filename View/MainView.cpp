#include "MainView.hpp"

#include "QtUtils.hpp"
#include "Model/ApplicationContext.hpp"

MainView::MainView(QWidget* parent) : QWidget{parent}
{
    buildWidgets();
    buildActions();
    buildMenus();
    connectSignals();
}

void MainView::buildWidgets()
{
    textEdit = new TextEditor{this};
    textFinder = new TextFinder{this, textEdit};

    treeView = new QTreeView{this};
    treeView->setHeaderHidden(true);
    treeView->setContextMenuPolicy(Qt::CustomContextMenu);

    addButton = new QPushButton{tr("Add"), this};

    textFinder->layout()->setMargin(0);
    textFinder->layout()->setSpacing(2);
    textFinder->hide();

    auto* editorWidget = new QFrame{this};
    QtUtils::vLayout(editorWidget, textEdit, textFinder)->setMargin(0);

    auto* treeWidget = new QFrame{this};
    // auto* buttonsLayout = QtUtils::hLayout(treeWidget, addButton);
    // buttonsLayout->setMargin(0);
    QtUtils::vLayout(treeWidget, treeView, addButton)->setMargin(0);

    auto* splitter = QtUtils::splitter(this, treeWidget, editorWidget);
    splitter->setStretchFactor(0, 0);
    splitter->setStretchFactor(1, 1);
    auto* mainLayout = QtUtils::hLayout(this, splitter);
    setLayout(mainLayout);
}

void MainView::buildActions()
{
    addNoteAction = QtUtils::action(this, tr("Add note here"), [&] { addNoteRequested(); });
}

void MainView::buildMenus()
{
    categoryContextMenu = new QMenu{this};
    categoryContextMenu->addAction(addNoteAction);
    categoryContextMenu->addAction(QtUtils::action(this, tr("Rename (TODO)"), [] {}));
    categoryContextMenu->addAction(QtUtils::action(this, tr("Delete (TODO)"), [] {}));
    categoryContextMenu->addAction(QtUtils::action(this, tr("Merge with... (TODO)"), [] {}));

    noteContextMenu = new QMenu{this};
    noteContextMenu->addAction(QtUtils::action(this, tr("Rename (TODO)"), [] {}));
    noteContextMenu->addAction(QtUtils::action(this, tr("Delete (TODO)"), [] {}));
    noteContextMenu->addAction(QtUtils::action(this, tr("Move to... (TODO)"), [] {}));
}

void MainView::connectSignals()
{
    connect(treeView, &QTreeView::customContextMenuRequested, this, &MainView::showContextMenu);
    connect(addButton, &QAbstractButton::clicked, this, &MainView::addNoteRequested);
}

QSize MainView::sizeHint() const
{
    return {800, 480};
}

void MainView::toggleTextFinder()
{
    textFinder->setVisible(textFinder->isHidden());
    if (textFinder->isVisible())
        textFinder->setFocus();
}

void MainView::showContextMenu(const QPoint& point)
{
    QMenu* menu;
    auto indexType = context->notes.indexType(treeView->indexAt(point));
    switch (indexType)
    {
    case CategorizedListModel::itInvalid:
        return;
    case CategorizedListModel::itCategory:
        menu = noteContextMenu;
        break;
    case CategorizedListModel::itItem:
        menu = categoryContextMenu;
        break;

    }

    menu->exec(treeView->viewport()->mapToGlobal(point));
}

void MainView::addNoteRequested()
{
    bool ok;
    QString name = QInputDialog::getText(this, tr("New note name..."), tr("Note name:"), QLineEdit::Normal,
                                         tr("Fast note"), &ok);
    if (ok && !name.isEmpty())
        emit addNote(treeView->currentIndex(), name);
}
