#include "MainView.hpp"

#include "QtUtils.hpp"

MainView::MainView(QWidget* parent) : QWidget{parent}
{
    textEdit = new TextEditor{this};
    textFinder = new TextFinder{this, textEdit};
    treeView = new QTreeView{this};
    treeView->setHeaderHidden(true);

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
