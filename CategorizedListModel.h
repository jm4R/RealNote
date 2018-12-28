#ifndef CategorizedListModel_H
#define CategorizedListModel_H

#include <QAbstractItemModel>

class CategorizedListModel : public QAbstractItemModel
{
public:
    CategorizedListModel(QObject* parent = nullptr);
    ~CategorizedListModel() override;
    QVariant data(const QModelIndex& index, int role) const override;
    QModelIndex index(int row, int column,
                      const QModelIndex& parent = QModelIndex()) const override;
    QModelIndex parent(const QModelIndex& index) const override;
    int rowCount(const QModelIndex& parent = QModelIndex()) const override;
    int columnCount(const QModelIndex& parent = QModelIndex()) const override;
    using QAbstractItemModel::itemData; // suppress warning

protected:
    virtual int categoriesCount() const = 0;
    virtual int categoryItems(int category) const = 0;
    virtual QVariant categoryData(int category, Qt::ItemDataRole role = Qt::DisplayRole) const = 0;
    virtual QVariant itemData(int category, int item,
                              Qt::ItemDataRole role = Qt::DisplayRole) const = 0;
};

#endif // CategorizedListModel_H
