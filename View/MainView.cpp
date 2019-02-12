#include "MainView.hpp"

#include "QtUtils.hpp"

MainView::MainView(QWidget* parent) : QWidget{parent}
{
    textEdit = new TextEditor{this};
    textFinder = new TextFinder{this, textEdit};
    treeView = new QTreeView{this};
    treeView->setHeaderHidden(true);
    addButton = new QPushButton{tr("Add"), this};

    textFinder->layout()->setMargin(0);
    textFinder->layout()->setSpacing(2);
    textFinder->hide();

    auto* editorWidget = new QFrame{this};
    QtUtils::vLayout(editorWidget, textEdit, textFinder)->setMargin(0);

    auto* treeWidget = new QFrame{this};
    //auto* buttonsLayout = QtUtils::hLayout(treeWidget, addButton);
    //buttonsLayout->setMargin(0);
    QtUtils::vLayout(treeWidget, treeView, addButton)->setMargin(0);

    auto* splitter = QtUtils::splitter(this, treeWidget, editorWidget);
    splitter->setStretchFactor(0, 0);
    splitter->setStretchFactor(1, 1);
    auto* mainLayout = QtUtils::hLayout(this, splitter);
    setLayout(mainLayout);
}

void MainView::toggleTextFinder()
{
    textFinder->setVisible(textFinder->isHidden());
    if (textFinder->isVisible())
        textFinder->setFocus();
}

QSize MainView::sizeHint() const
{
    return {800, 480};
}
