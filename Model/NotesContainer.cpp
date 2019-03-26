#include "NotesContainer.hpp"

#include "FilesUtils.hpp"
#include "Model/ApplicationContext.hpp"
#include "Model/NoteModel.hpp"
#include "Themes.hpp"

#include <QDebug>
#include <QStandardPaths>
#include <QStringList>
#include <QPixmap>

namespace
{

template<typename T>
T unexpected(T val)
{
    assert(false);
    return std::forward<T>(val);
}

} // namespace

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
    return noteAt(idx);
}

NoteModel* NotesContainer::noteAt(const CategorizedListModel::Index& idx)
{
    return noteAt(idx.category, idx.item);
}

NoteModel *NotesContainer::noteAt(int category, int note)
{
    if (!noteExists(category, note))
        return unexpected(nullptr);
    else
        return categoryAt(category)->_notes[static_cast<std::size_t>(note)].get();
}

const NoteModel *NotesContainer::noteAt(int category, int note) const
{
    if (!noteExists(category, note))
        return unexpected(nullptr);
    else
        return categoryAt(category)->_notes[static_cast<std::size_t>(note)].get();
}

NoteModel* NotesContainer::findNote(const QString& category, const QString& name) const
{
    auto c = std::find_if(_categories.begin(), _categories.end(), [&](auto& c) { return c->_name == category; });
    if (c == _categories.end())
        return nullptr;
    auto n = std::find_if(c->get()->_notes.begin(), c->get()->_notes.end(), [&](auto& n) { return n->name() == name; });
    if (n == c->get()->_notes.end())
        return nullptr;
    return n->get();
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
    assert(categoryExists(category));
    return static_cast<int>(categoryAt(category)->_notes.size());
}

QVariant NotesContainer::categoryData(int category, Qt::ItemDataRole role) const
{
    assert(categoryExists(category));
    switch (role)
    {
    case Qt::DisplayRole:
    case Qt::EditRole:
        return categoryAt(category)->_name;
    case Qt::DecorationRole:
        return Themes::categoryIcon();
    default:
        return {};
    }
}

QVariant NotesContainer::itemData(int category, int item, Qt::ItemDataRole role) const
{
    assert(noteExists(category, item));
    switch (role)
    {
    case Qt::DisplayRole:
    case Qt::EditRole:
        return noteAt(category, item)->name();
    case Qt::DecorationRole:
        return Themes::noteIcon();
    default:
        return {};
    }
}

bool NotesContainer::handleInsertCategory(int beforeCategory, QVariant data)
{
    if (beforeCategory < 0 || beforeCategory > categoriesCount())
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
    if (!categoryExists(category))
        return false;

    auto theCategory = categoryAt(category);

    if (!theCategory)
        return unexpected(false);

    auto& theNotes = theCategory->_notes;

    if (beforeItem < 0 || beforeItem > int(theNotes.size()))
        return unexpected(false);

    auto& inserted = *theCategory->_notes.insert(
            theNotes.begin() + beforeItem, std::make_unique<NoteModel>(theCategory->_name, std::move(data).toString()));
    inserted->save();
    return true;
}

bool NotesContainer::handleRemoveCategory(int category)
{
    if (!categoryExists(category))
        return unexpected(false);

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
    if (noteExists(category, item))
        return unexpected(false);

    auto& theCategory = *_categories[std::size_t(category)];

    auto removedIterator = theCategory._notes.begin() + item;
    bool ok = removedIterator->get()->archive();
    ok = ok && *theCategory._notes.erase(removedIterator);
    return ok;
}

bool NotesContainer::handleResetCategory(int category, const QVariant &value, int role)
{
    if (role != Qt::EditRole)
        return false;

    auto* toReset = categoryAt(category);
    if (!toReset)
        return unexpected(false);

    auto dir = Dir::dataDir();
    bool ok = dir.rename(toReset->_name, value.toString());
    if (!ok)
        return false; // TODO: error handling
    toReset->_name = value.toString();
    return true;
}

bool NotesContainer::handleResetItem(int category, int item, const QVariant &value, int role)
{
    if (role != Qt::EditRole)
        return false;
    if (!noteExists(category, item))
        return unexpected(false);

    bool ok = noteAt(category, item)->rename(value.toString());
    return ok; //TODO: error handling
}

Qt::ItemFlags NotesContainer::flags(const QModelIndex &index) const
{
    return CategorizedListModel::flags(index) | Qt::ItemIsEditable;
}

Category *NotesContainer::categoryAt(int category)
{
    if (!categoryExists(category))
    {
        return nullptr;
    }
    else
        return _categories[static_cast<std::size_t>(category)].get();
}

const Category *NotesContainer::categoryAt(int category) const
{
    if (!categoryExists(category))
    {
        return nullptr;
    }
    else
        return _categories[static_cast<std::size_t>(category)].get();
}

bool NotesContainer::categoryExists(int category) const
{
    return category >= 0 && category < categoriesCount();
}

bool NotesContainer::noteExists(int category, int note) const
{
    return categoryExists(category) && note >= 0 && note < categoryItems(category);
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
