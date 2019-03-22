#ifndef NOTESCONTAINER_H
#define NOTESCONTAINER_H

#include "CategorizedListModel.hpp"

#include <memory>
#include <vector>

class NoteModel;

struct Category
{
    QString _name;
    std::vector<std::unique_ptr<NoteModel>> _notes;
};

class NotesContainer : public CategorizedListModel
{
    Q_OBJECT
public:
    NotesContainer(QObject* parent = nullptr);
    ~NotesContainer() override;

    void add(int category, int beforeNote, const QString& name);
    void addCategory(int beforeCategory, const QString& name);

    NoteModel* noteAt(const QModelIndex &index);
    NoteModel* noteAt(const Index& index);
    NoteModel* findNote(const QString& category, const QString& name) const;
    void setLoadedNote(NoteModel &note);

protected:
    int categoriesCount() const override;
    int categoryItems(int category) const override;
    QVariant categoryData(int category, Qt::ItemDataRole role = Qt::DisplayRole) const override;
    QVariant itemData(int category, int item, Qt::ItemDataRole role = Qt::DisplayRole) const override;

    bool handleInsertCategory(int beforeCategory, QVariant data) override;
    bool handleInsertItem(int category, int beforeItem, QVariant data) override;
    bool handleRemoveCategory(int category) override;
    bool handleRemoveItem(int category, int item) override;

signals:
    void loadedChanged();

private:
    void loadFromDisc();

private:
    std::vector<std::unique_ptr<Category>> _categories;
};

#endif // NOTESCONTAINER_H
