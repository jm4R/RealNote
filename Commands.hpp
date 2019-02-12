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
            context->note = note;
        }
        return note != nullptr;
    }
};

} // namespace cmd

#endif // COMMANDS_HPP
