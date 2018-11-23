#ifndef CategorizedListModel_H
#define CategorizedListModel_H

#include <QAbstractItemModel>

class CategorizedListModel : public QAbstractItemModel
{
    Q_OBJECT
public:
    CategorizedListModel(QObject* parent = nullptr);
    ~CategorizedListModel() override;

public:
    enum IndexType
    {
        itInvalid,
        itCategory,
        itItem
    };

    static IndexType indexType(const QModelIndex& index);

    //read data:
    QVariant data(const QModelIndex& index, int role) const override;
    QModelIndex index(int row, int column, const QModelIndex& parent = QModelIndex()) const override;
    QModelIndex parent(const QModelIndex& index) const override;
    int rowCount(const QModelIndex& parent = QModelIndex()) const override;
    int columnCount(const QModelIndex& parent = QModelIndex()) const override;

    //modify data:
    bool insertCategory(int beforeCategory, QVariant data);
    bool insertItem(int category, int beforeItem, QVariant data);
    bool removeCategory(int category);
    bool removeItem(int category, int item);

    using QAbstractItemModel::itemData; // suppress warning

public: // TODO: are you sure?
    struct Index
    {
        int category, item;
    };
    Index translateIndex(const QModelIndex& index) const;
    QModelIndex translateIndex(const Index& index) const;
    QModelIndex categoryToIndex(int category) const;
    QModelIndex itemToIndex(int category, int item) const;

protected:
    virtual int categoriesCount() const = 0;
    virtual int categoryItems(int category) const = 0;
    virtual QVariant categoryData(int category, Qt::ItemDataRole role = Qt::DisplayRole) const = 0;
    virtual QVariant itemData(int category, int item, Qt::ItemDataRole role = Qt::DisplayRole) const = 0;

    virtual bool handleInsertCategory(int beforeCategory, QVariant data);
    virtual bool handleInsertItem(int category, int beforeItem, QVariant data);
    virtual bool handleRemoveCategory(int category);
    virtual bool handleRemoveItem(int category, int item);
};

#endif // CategorizedListModel_H
