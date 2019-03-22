#include "Commands.hpp"

#include "Model/ApplicationContext.hpp"
#include "Model/NoteModel.hpp"
#include "MainWindow.hpp"

bool cmd::reloadFromSettings()
{
    QVariant c = context->settings.value("current_category");
    QVariant n = context->settings.value("current_note");
    bool loaded = false;
    if (c.isValid() && n.isValid())
    {
        auto note = context->notes.findNote(c.toString(), n.toString());
        loaded =  setNote(note);
    }
    if (!loaded)
    {
        auto firstNote = context->notes.noteAt(CategorizedListModel::Index{0, 0});
        loaded =  setNote(firstNote);
    }
    if (!loaded)
    {
        context->notes.addCategory(0, QObject::tr("FAST NOTES"));
        context->notes.add(0, 0, QObject::tr("Default"));
        auto firstNote = context->notes.noteAt(CategorizedListModel::Index{0, 0});
        loaded =  setNote(firstNote);
    }
    return loaded;
}

bool cmd::saveCurrentNote()
{
    if (!context->note)
        return false;
    context->note->save();
    return true;
}

bool cmd::setNote(const QModelIndex &index)
{
    auto note = context->notes.noteAt(index);
    return setNote(note);
}

bool cmd::setNote(NoteModel *note)
{
    if (note)
    {
        context->notes.setLoadedNote(*note);
        context->settings.setValue("current_category", note->category());
        context->settings.setValue("current_note", note->name());
        context->window->setWindowTitle("[" + note->category() + "]  " + note->name());
    }
    return note != nullptr;
}

bool cmd::addNote(const QModelIndex &position, const QString &name)
{
    auto ciIndex = context->notes.translateIndex(position);
    context->notes.add(ciIndex.category, ciIndex.item + 1, name);
    return true;
}

bool cmd::removeNote(const QModelIndex &index)
{
    auto ciIndex = context->notes.translateIndex(index);
    context->notes.removeItem(ciIndex.category, ciIndex.item);
    return true;
}

bool cmd::addCategory(const QModelIndex &position, const QString &name)
{
    auto ciIndex = context->notes.translateIndex(position);
    context->notes.addCategory(ciIndex.category + 1, name);
    return true;
}

bool cmd::removeCategory(const QModelIndex &index)
{
    auto ciIndex = context->notes.translateIndex(index);
    context->notes.removeCategory(ciIndex.category);
    return true;
}
