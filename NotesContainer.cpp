#include "NotesContainer.hpp"

#include "FilesUtils.hpp"
#include "NoteModel.hpp"

#include <QStandardPaths>
#include <QStringList>

NotesContainer::NotesContainer(QObject* parent) : CategorizedListModel{parent}
{
    loadFromDisc();
}

NotesContainer::~NotesContainer()
{

}

NoteModel* NotesContainer::noteAt(const QModelIndex& index)
{
    auto idx = translateIndex(index);
    if (idx.category == -1 || idx.item == -1)
        return nullptr;
    else
        return _categories[static_cast<std::size_t>(idx.category)]->_notes[static_cast<std::size_t>(idx.item)].get();
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
        return _categories[static_cast<std::size_t>(category)]->_notes[static_cast<std::size_t>(item)]->name();
    case Qt::DecorationRole:
        return QColor{Qt::blue};
    default:
        return {};
    }
}

void NotesContainer::loadFromDisc()
{
    QDir dataDir = Dir::dataDir();
    for (const auto& categoryDir : Dir::listDirs(dataDir))
    {
        _categories.push_back(std::make_unique<Category>());
        _categories.back()->_name = categoryDir;
        dataDir.cd(categoryDir);
        for (const auto& noteFile : Dir::listFiles(dataDir))
            _categories.back()->_notes.push_back(std::make_unique<NoteModel>(categoryDir, noteFile));
    }
}
