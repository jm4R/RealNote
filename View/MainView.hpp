#ifndef MAINVIEW_H
#define MAINVIEW_H

#include <QWidget>

class QTreeView;
class QPlainTextEdit;
class TextEditor;
class TextFinder;

class MainView : public QWidget
{
    Q_OBJECT
public:
    MainView(QWidget* parent);

public slots:
    void toggleTextFinder();

protected:
    QSize sizeHint() const override;

public:
    QTreeView* treeView;
    TextEditor* textEdit;
    TextFinder* textFinder;
};

#endif // MAINVIEW_H
