#include "NotesContainer.h"

#include "NoteModel.h"

#include <QStandardPaths>

const QString NotesContainer::DATA_LOCATION =
    QStandardPaths::writableLocation(QStandardPaths::AppDataLocation);

NotesContainer::NotesContainer(QObject* parent)
    : CategorizedListModel{parent}
{
    loadFromDisc();
}

int NotesContainer::categoriesCount() const
{
    return static_cast<int>(_categories.size());
}

int NotesContainer::categoryItems(int category) const
{
    return static_cast<int>(_categories[static_cast<std::size_t>(category)]->_notes.size());
}
#include <QColor>
QVariant NotesContainer::categoryData(int category, Qt::ItemDataRole role) const
{
    switch (role)
    {
    case Qt::DisplayRole:
        return _categories[static_cast<std::size_t>(category)]->_name;
    case Qt::DecorationRole:
        return QColor{Qt::green};
    default:
        return {};
    }
}

QVariant NotesContainer::itemData(int category, int item, Qt::ItemDataRole role) const
{
    switch (role)
    {
    case Qt::DisplayRole:
        return _categories[static_cast<std::size_t>(category)]
            ->_notes[static_cast<std::size_t>(item)]
            ->name();
    case Qt::DecorationRole:
        return QColor{Qt::blue};
    default:
        return {};
    }
}

void NotesContainer::loadFromDisc()
{
    // TODO: stub
    _categories.push_back(std::make_unique<Category>());
    _categories.back()->_name = "Default";
    _categories.back()->_notes.push_back(std::make_unique<NoteModel>("DefaultNote"));
}
