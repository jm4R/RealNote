#ifndef NOTESCONTAINER_H
#define NOTESCONTAINER_H

#include "CategorizedListModel.h"

#include <vector>
#include <memory>

class NoteModel;

struct Category
{
    QString _name;
    std::vector<std::unique_ptr<NoteModel>> _notes;
};

class NotesContainer : public CategorizedListModel
{
public:
    NotesContainer(QObject* parent = nullptr);

protected:
    int categoriesCount() const override;
    int categoryItems(int category) const override;
    QVariant categoryData(int category, Qt::ItemDataRole role = Qt::DisplayRole) const override;
    QVariant itemData(int category, int item,
                      Qt::ItemDataRole role = Qt::DisplayRole) const override;

private:
    void loadFromDisc();

private:
    static const QString DATA_LOCATION;

private:
    std::vector<std::unique_ptr<Category>> _categories;
};

#endif // NOTESCONTAINER_H
