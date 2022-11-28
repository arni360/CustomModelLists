#include "CustomDelegate.h"
#include "BaseListModel.h"

CustomDelegate::CustomDelegate(QObject* parent)
    : QStyledItemDelegate(parent)
{
}

QSize CustomDelegate::sizeHint(const QStyleOptionViewItem& option, const QModelIndex& index) const
{
    const auto res = QStyledItemDelegate::sizeHint(option, index);

    if (index.data(BaseListModel::IsFilterNameRole).toBool())
    {
        return QSize(maxWidth, res.height());
    }
    return res;
}
