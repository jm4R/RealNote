#ifndef MAINVIEW_H
#define MAINVIEW_H

#include <QWidget>

class QAction;

class QAbstractButton;
class QTreeView;
class QPlainTextEdit;
class QPoint;
class QPushButton;
class TextEditor;
class TextFinder;
class QMenu;
class QModelIndex;

class MainView : public QWidget
{
    Q_OBJECT
public:
    MainView(QWidget* parent);

private:
    void buildWidgets();
    void buildActions();
    void buildMenus();
    void connectSignals();

signals:
    void addNote(const QModelIndex& position, const QString& name);
    void removeNote(const QModelIndex& index);
    void addCategory(const QModelIndex& position, const QString& name);
    void removeCategory(const QModelIndex& index);

public slots:
    void toggleTextFinder();

private slots:
    void showContextMenu(const QPoint& point);
    void addNoteRequested();
    void removeNoteRequested();
    void addCategoryRequested();
    void removeCategoryRequested();
    void renameRequested();

protected:
    QSize sizeHint() const override;

public:
    using QButton = QPushButton;

    QTreeView* treeView;
    TextEditor* textEdit;
    TextFinder* textFinder;

    QMenu* categoryContextMenu;
    QMenu* noteContextMenu;

private:
    QAction* addNoteAction;
    QAction* removeNoteAction;
    QAction* addCategoryAction;
    QAction* removeCategoryAction;
    QAction* editAction;
};

#endif // MAINVIEW_H
