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

    textFinder->layout()->setMargin(0);
    textFinder->layout()->setSpacing(2);
    textFinder->hide();

    auto* editorWidget = new QFrame{this};
    QtUtils::vLayout(editorWidget, textEdit, textFinder)->setMargin(0);

    auto* splitter = QtUtils::splitter(this, treeView, editorWidget);
    splitter->setStretchFactor(0, 0);
    splitter->setStretchFactor(1, 1);
    auto* mainLayout = QtUtils::hLayout(this, splitter);
    setLayout(mainLayout);
}

void MainView::buildActions()
{
    addNoteAction = QtUtils::action(this, tr("Add note here"), [&] { addNoteRequested(); });
    removeNoteAction = QtUtils::action(this, tr("Remove this note"), [&] { removeNoteRequested(); });
    addCategoryAction = QtUtils::action(this, tr("Add category here"), [&] { addCategoryRequested(); });
    removeCategoryAction = QtUtils::action(this, tr("Remove this category"), [&] { removeCategoryRequested(); });
    editAction = QtUtils::action(this, tr("Rename"), [&]{ renameRequested(); });
}

void MainView::buildMenus()
{

    categoryContextMenu = new QMenu{this};
    {
        auto* menu = categoryContextMenu;
        menu->addAction(addNoteAction);
        menu->addAction(addCategoryAction);
        menu->addAction(removeCategoryAction);
        menu->addAction(editAction);
        //menu->addAction(QtUtils::action(this, tr("Move to... (TODO)"), [] {}));
    }

    noteContextMenu = new QMenu{this};
    {
        auto* menu = noteContextMenu;
        menu->addAction(removeNoteAction);
        menu->addAction(editAction);
        //menu->addAction(QtUtils::action(this, tr("Merge with... (TODO)"), [] {}));
    }
}

void MainView::connectSignals()
{
    connect(treeView, &QTreeView::customContextMenuRequested, this, &MainView::showContextMenu);
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
        menu = categoryContextMenu;
        break;
    case CategorizedListModel::itItem:
        menu = noteContextMenu;
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
    bool confirm = QtUtils::confirmDialog(this, tr("Move note to archive?"));
    if (confirm)
        emit removeNote(index);
}

void MainView::addCategoryRequested()
{
    bool ok;
    QString name = QInputDialog::getText(this, tr("New category name..."), tr("Category name:"),
                                         QLineEdit::Normal, tr("New category"), &ok);
    if (ok && !name.isEmpty())
        emit addCategory(treeView->currentIndex(), name);
}

void MainView::removeCategoryRequested()
{
    auto index = treeView->currentIndex();
    if (!index.isValid())
        return;
    bool confirm = QtUtils::confirmDialog(this, tr("Move category to archive?"));
    if (confirm)
        emit removeCategory(index);
}

void MainView::renameRequested()
{
    auto index = treeView->currentIndex();
    treeView->edit(index);
}
