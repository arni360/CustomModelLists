#pragma once
#include <QSortFilterProxyModel>
#include <QAbstractProxyModel>
class BaseListModel :
    public QAbstractProxyModel
{
public:
    enum ROLES {
        IsFilterNameRole = Qt::UserRole + 1
    };
    BaseListModel(QObject* i_parent);
    void set_source_model(QSortFilterProxyModel* i_source);
    virtual int	columnCount(const QModelIndex& parent = QModelIndex()) const override;
    virtual int	rowCount(const QModelIndex& parent = QModelIndex()) const override;
    virtual QModelIndex	mapFromSource(const QModelIndex& sourceIndex) const override;
    virtual QModelIndex	mapToSource(const QModelIndex& proxyIndex) const override;
    virtual QVariant	data(const QModelIndex & index, int role = Qt::DisplayRole) const override;
    virtual QModelIndex	parent(const QModelIndex& index) const override;
    virtual QModelIndex	index(int row, int column, const QModelIndex& parent = QModelIndex()) const override;
    virtual Qt::ItemFlags	flags(const QModelIndex& index) const override;
protected:
    void clean_data();
    void remap_data();

protected:
    QSortFilterProxyModel* m_source;
    QVector<QPair<QVariant,int>> m_sort_values;
};

