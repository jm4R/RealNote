#ifndef COMMANDS_HPP
#define COMMANDS_HPP

#include "Model/ApplicationContext.hpp"

class NoteModel;

namespace cmd
{

struct SetNote
{
    const QModelIndex& index;
    SetNote(const QModelIndex& index) : index{index}
    {
    }

    bool operator()()
    {
        auto note = context->notes.noteAt(index);
        if (note)
        {
            context->notes.setLoadedNote(*note);
        }
        return note != nullptr;
    }
};

bool addNote()
{

    return true;
}

} // namespace cmd

#endif // COMMANDS_HPP
