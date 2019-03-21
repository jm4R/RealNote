#ifndef COMMANDS_HPP
#define COMMANDS_HPP

class NoteModel;
class QModelIndex;
class QString;

namespace cmd
{

bool reloadFromSettings();
bool saveCurrentNote();
bool setNote(const QModelIndex& index);
bool setNote(NoteModel* note);
bool addNote(const QModelIndex& position, const QString& name);
bool removeNote(const QModelIndex& index);
bool addCategory(const QModelIndex& position, const QString& name);
bool removeCategory(const QModelIndex& index);

} // namespace cmd

#endif // COMMANDS_HPP
