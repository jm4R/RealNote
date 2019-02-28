#include "CategorizedListModel.hpp"

namespace
{
constexpr auto HAVE_NO_PARENT = static_cast<quintptr>(-1);
} // namespace

CategorizedListModel::CategorizedListModel(QObject* parent) : QAbstractItemModel{parent}
{
}

CategorizedListModel::~CategorizedListModel()
{
}

CategorizedListModel::IndexType CategorizedListModel::indexType(const QModelIndex& index)
{
    if (!index.isValid())
        return itInvalid;
    return index.internalId() == HAVE_NO_PARENT ? itCategory : itItem;
}

QVariant CategorizedListModel::data(const QModelIndex& index, int role) const
{
    switch (indexType(index))
    {
    case itInvalid:
        return {};
    case itCategory:
        return categoryData(index.row(), Qt::ItemDataRole(role));
    case itItem:
        return itemData(static_cast<int>(index.internalId()), index.row(), Qt::ItemDataRole(role));
    }
    return {};
}

QModelIndex CategorizedListModel::index(int row, int column, const QModelIndex& parent) const
{
    if (!hasIndex(row, column, parent))
        return QModelIndex();

    auto category = parent.isValid() ? static_cast<quintptr>(parent.row()) : HAVE_NO_PARENT;
    return createIndex(row, 0, category);
}

QModelIndex CategorizedListModel::parent(const QModelIndex& index) const
{
    if (indexType(index) == itItem)
        return createIndex(static_cast<int>(index.internalId()), 0, HAVE_NO_PARENT);
    return {};
}

int CategorizedListModel::rowCount(const QModelIndex& parent) const
{
    switch (indexType(parent))
    {
    case itInvalid:
        return categoriesCount();
    case itCategory:
        return categoryItems(parent.row());
    case itItem:
        return 0;
    }
    return 0;
}

int CategorizedListModel::columnCount(const QModelIndex& /*parent*/) const
{
    return 1;
}

bool CategorizedListModel::insertCategory(int beforeCategory, QVariant data)
{
    beginInsertRows({}, beforeCategory, beforeCategory + 1);
    bool res = handleInsertCategory(beforeCategory, std::move(data));
    endInsertRows();
    return res;
}

bool CategorizedListModel::insertItem(int category, int beforeItem, QVariant data)
{
    beginInsertRows(categoryToIndex(category), beforeItem, beforeItem + 1);
    bool res = handleInsertItem(category, beforeItem, std::move(data));
    endInsertRows();
    return res;
}

CategorizedListModel::Index CategorizedListModel::translateIndex(const QModelIndex& index) const
{
    switch (indexType(index))
    {
    case itInvalid:
        return {-1, -1};
    case itCategory:
        return {index.row(), -1};
    case itItem:
        return {static_cast<int>(index.internalId()), index.row()};
    }
    return {-1, -1};
}

QModelIndex CategorizedListModel::translateIndex(const Index& index) const
{
    if (index.category == -1 && index.item == -1)
        return {};
    if (index.item == -1 /*&& index.category != -1*/)
        return createIndex(index.category, 0, HAVE_NO_PARENT);
    return createIndex(index.item, 0, static_cast<quintptr>(index.category));
}

QModelIndex CategorizedListModel::categoryToIndex(int category) const
{
    return translateIndex({category, -1});
}

QModelIndex CategorizedListModel::itemToIndex(int category, int item) const
{
    return translateIndex({category, item});
}

bool CategorizedListModel::handleInsertCategory(int, QVariant)
{
    return false;
}

bool CategorizedListModel::handleInsertItem(int, int, QVariant)
{
    return false;
}
