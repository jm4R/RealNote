#include "Commands.hpp"

#include "Model/ApplicationContext.hpp"
#include "Model/NoteModel.hpp"

bool cmd::reloadFromSettings()
{
    QVariant c = context->settings.value("current_category");
    QVariant n = context->settings.value("current_note");
    if (c.isValid() && n.isValid())
    {
        auto note = context->notes.findNote(c.toString(), n.toString());
        if (note)
        {
            context->notes.setLoadedNote(*note);
            context->settings.setValue("current_category", note->category());
            context->settings.setValue("current_note", note->name());
        }
        return note != nullptr;
    }
    return false;
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
    if (note)
    {
        context->notes.setLoadedNote(*note);
        context->settings.setValue("current_category", note->category());
        context->settings.setValue("current_note", note->name());
    }
    return note != nullptr;
}

bool cmd::setNote(NoteModel *note)
{
    if (note)
    {
        context->notes.setLoadedNote(*note);
        context->settings.setValue("current_category", note->category());
        context->settings.setValue("current_note", note->name());
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
