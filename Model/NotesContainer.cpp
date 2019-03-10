#include "NotesContainer.hpp"

#include "FilesUtils.hpp"
#include "Model/ApplicationContext.hpp"
#include "Model/NoteModel.hpp"

#include <QDebug>
#include <QStandardPaths>
#include <QStringList>

NotesContainer::NotesContainer(QObject* parent) : CategorizedListModel{parent}
{
    // TODO move from constructor;
    loadFromDisc();
}

NotesContainer::~NotesContainer()
{
}

void NotesContainer::add(int categoryNumber, int beforeNote, const QString& name)
{
    insertItem(categoryNumber, beforeNote, name);
}

void NotesContainer::addCategory(int beforeCategory, const QString &name)
{
    insertCategory(beforeCategory, name);
}

NoteModel* NotesContainer::noteAt(const QModelIndex& index)
{
    auto idx = translateIndex(index);
    if (idx.category == -1 || idx.item == -1)
        return nullptr;
    else
        return _categories[static_cast<std::size_t>(idx.category)]->_notes[static_cast<std::size_t>(idx.item)].get();
}

void NotesContainer::setLoadedNote(NoteModel& note)
{
    context->note = &note;
    emit loadedChanged();
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
        return QColor{0xff161718};
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
        return QColor{0xff22242f};
    default:
        return {};
    }
}

bool NotesContainer::handleInsertCategory(int beforeCategory, QVariant data)
{
    if (beforeCategory < 0 || beforeCategory > int(_categories.size()))
        return false;
    bool ok = Dir::dataDir().mkdir(data.toString());
    if (!ok)
        return false; // TODO: error handling
    auto& newCategory = *_categories.insert(_categories.begin() + beforeCategory,
                                            std::make_unique<Category>());
    newCategory->_name = std::move(data).toString();
    return true;
}

bool NotesContainer::handleInsertItem(int category, int beforeItem, QVariant data)
{
    if (category < 0 || category >= int(_categories.size()))
        return false;

    auto& theCategory = *_categories[std::size_t(category)];

    if (beforeItem < 0 || beforeItem > int(theCategory._notes.size()))
        return false;

    auto& inserted = *theCategory._notes.insert(theCategory._notes.begin() + beforeItem,
                                                std::make_unique<NoteModel>(
                                                        theCategory._name,
                                                        std::move(data).toString()));
    inserted->save();
    return true;
}

bool NotesContainer::handleRemoveCategory(int category)
{
    if (category < 0 || category >= int(_categories.size()))
        return false;
    auto toRemove = _categories.begin() + category;
    auto dir = Dir::dataDir();
    bool ok = dir.cd(toRemove->get()->_name);
    ok = ok && dir.removeRecursively();
    if (!ok)
        return false; // TODO: error handling
    _categories.erase(toRemove);
    return true;
}

bool NotesContainer::handleRemoveItem(int category, int item)
{
    if (category < 0 || category >= int(_categories.size()))
        return false;

    auto& theCategory = *_categories[std::size_t(category)];

    if (item < 0 || item >= int(theCategory._notes.size()))
        return false;

    auto removedIterator = theCategory._notes.begin() + item;
    bool ok = removedIterator->get()->archive();
    ok = ok && *theCategory._notes.erase(removedIterator);
    return ok;
}

void NotesContainer::loadFromDisc()
{
    QDir dataDir = Dir::dataDir();
    qDebug() << "Loading notes structure from: " << dataDir.path();
    for (const auto& categoryDir : Dir::listDirs(dataDir))
    {
        _categories.push_back(std::make_unique<Category>());
        _categories.back()->_name = categoryDir;
        dataDir.cd(categoryDir);
        for (const auto& noteFile : Dir::listFiles(dataDir))
            _categories.back()->_notes.push_back(std::make_unique<NoteModel>(categoryDir, noteFile));
        dataDir.cdUp();
    }
}
