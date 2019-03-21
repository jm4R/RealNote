#ifndef COMMANDS_HPP
#define COMMANDS_HPP

#include "Model/ApplicationContext.hpp"
#include "Model/NoteModel.hpp"

namespace cmd
{

bool reloadFromSettings()
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

bool saveCurrentNote()
{
    if (!context->note)
        return false;
    context->note->save();
    return true;
}

bool setNote(const QModelIndex& index)
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

bool addNote(const QModelIndex& position, const QString& name)
{
    auto ciIndex = context->notes.translateIndex(position);
    context->notes.add(ciIndex.category, ciIndex.item + 1, name);
    return true;
}

bool removeNote(const QModelIndex& index)
{
    auto ciIndex = context->notes.translateIndex(index);
    context->notes.removeItem(ciIndex.category, ciIndex.item);
    return true;
}

bool addCategory(const QModelIndex& position, const QString& name)
{
    auto ciIndex = context->notes.translateIndex(position);
    context->notes.addCategory(ciIndex.category + 1, name);
    return true;
}

bool removeCategory(const QModelIndex& index)
{
    auto ciIndex = context->notes.translateIndex(index);
    context->notes.removeCategory(ciIndex.category);
    return true;
}

} // namespace cmd

#endif // COMMANDS_HPP
