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

    addButton = new QButton{tr("Add"), this};
    removeButton = new QButton{tr("Remove"), this};

    textFinder->layout()->setMargin(0);
    textFinder->layout()->setSpacing(2);
    textFinder->hide();

    auto* editorWidget = new QFrame{this};
    QtUtils::vLayout(editorWidget, textEdit, textFinder)->setMargin(0);

    auto* treeWidget = new QFrame{this};
    auto* buttonsLayout = QtUtils::hLayout(nullptr, addButton, removeButton); //TODO: memory leak?
    buttonsLayout->setMargin(0);
    auto* treeLayout = QtUtils::vLayout(treeWidget, treeView, buttonsLayout);
    treeLayout->setMargin(0);


    auto* splitter = QtUtils::splitter(this, treeWidget, editorWidget);
    splitter->setStretchFactor(0, 0);
    splitter->setStretchFactor(1, 1);
    auto* mainLayout = QtUtils::hLayout(this, splitter);
    setLayout(mainLayout);
}

void MainView::buildActions()
{
    addNoteAction = QtUtils::action(this, tr("Add note here"), [&] { addNoteRequested(); });
    removeNoteAction = QtUtils::action(this, tr("Remove this note"), [&] { removeNoteRequested(); });
}

void MainView::buildMenus()
{

    categoryContextMenu = new QMenu{this};
    {
        auto* menu = categoryContextMenu;
        menu->addAction(addNoteAction);
        menu->addAction(removeNoteAction);
        menu->addAction(QtUtils::action(this, tr("Rename (TODO)"), [] {}));
        menu->addAction(QtUtils::action(this, tr("Merge with... (TODO)"), [] {}));
    }

    noteContextMenu = new QMenu{this};
    {
        auto* menu = noteContextMenu;
        menu->addAction(removeNoteAction);
        menu->addAction(QtUtils::action(this, tr("Rename (TODO)"), [] {}));
        menu->addAction(QtUtils::action(this, tr("Move to... (TODO)"), [] {}));
    }
}

void MainView::connectSignals()
{
    connect(treeView, &QTreeView::customContextMenuRequested, this, &MainView::showContextMenu);
    connect(addButton, &QButton::clicked, this, &MainView::addNoteRequested);
    connect(removeButton, &QButton::clicked, this, &MainView::removeNoteRequested);
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

void MainView::removeNoteRequested()
{
    auto index = treeView->currentIndex();
    if (!index.isValid())
        return;
    bool confirm = QtUtils::confirmDialog(this, tr("Remove permanently?"));
    if (confirm)
        emit removeNote(index);
}
