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
    void addNote(const QModelIndex& category, const QString& name);
    void removeNote(const QModelIndex& index);

public slots:
    void toggleTextFinder();

private slots:
    void showContextMenu(const QPoint& point);
    void addNoteRequested();
    void removeNoteRequested();

protected:
    QSize sizeHint() const override;

public:
    using QButton = QPushButton;

    QTreeView* treeView;
    TextEditor* textEdit;
    TextFinder* textFinder;
    QButton* addButton;
    QButton* removeButton;

    QAction* addNoteAction;
    QAction* removeNoteAction;

    QMenu* categoryContextMenu;
    QMenu* noteContextMenu;
};

#endif // MAINVIEW_H
