#ifndef COMMANDS_HPP
#define COMMANDS_HPP

#include "Model/ApplicationContext.hpp"

class NoteModel;

namespace cmd
{

bool setNote(const QModelIndex& index)
{
    auto note = context->notes.noteAt(index);
    if (note)
    {
        context->notes.setLoadedNote(*note);
    }
    return note != nullptr;
}

bool addNote(const QModelIndex& index, const QString& name)
{
    auto ciIndex = context->notes.translateIndex(index);
    context->notes.add(ciIndex.category, ciIndex.item + 1, name);
    return true;
}

bool removeNote(const QModelIndex& index)
{
    auto ciIndex = context->notes.translateIndex(index);
    context->notes.remove(ciIndex.category, ciIndex.item);
    return true;
}

} // namespace cmd

#endif // COMMANDS_HPP
