#ifndef NOTESCONTAINER_H
#define NOTESCONTAINER_H

#include <QList>

class NoteModel;

struct Category
{
    QString _name;
    QList<NoteModel> _notes;
};

class NotesContainer //:public QAbstractItemModel
{
public:
    NotesContainer();

private:
    void loadFromDisc();

private:
    static const QString DATA_LOCATION;

private:
    QList<Category> _categories;
};

#endif // NOTESCONTAINER_H
