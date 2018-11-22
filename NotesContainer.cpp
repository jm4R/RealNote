#include "NotesContainer.h"

#include "NoteModel.h"

#include <QStandardPaths>

const QString NotesContainer::DATA_LOCATION =
    QStandardPaths::writableLocation(QStandardPaths::AppDataLocation);

NotesContainer::NotesContainer()
{
    loadFromDisc();
}

void NotesContainer::loadFromDisc()
{

}
