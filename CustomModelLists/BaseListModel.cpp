#include "BaseListModel.h"

BaseListModel::BaseListModel(QObject* i_parent)
	: QAbstractProxyModel(i_parent)
	, m_source(new QSortFilterProxyModel(this))
{
	setSourceModel(m_source);
}

void BaseListModel::set_source_model(QAbstractItemModel* i_source)
{
	m_source->setSourceModel(i_source);
	remap_data();
	connect(m_source, &QAbstractItemModel::layoutAboutToBeChanged, this, &BaseListModel::clean_data);
	connect(m_source, &QAbstractItemModel::layoutChanged, this, &BaseListModel::remap_data);
}

int BaseListModel::columnCount(const QModelIndex& parent) const
{
	return 1;
}

int BaseListModel::rowCount(const QModelIndex& parent) const
{
	return sourceModel()->rowCount() + m_sort_values.size();
}

QModelIndex BaseListModel::mapFromSource(const QModelIndex& sourceIndex) const
{
	if (!sourceIndex.isValid())
	{
		return QModelIndex();
	}

	const QVariant& val = sourceIndex.data(m_source->sortRole());
	int row = sourceIndex.row();
	for (const auto& value: m_sort_values)
	{
		row++;
		if (value.first == val)
		{
			break;
		}
	}
	return index(row ,0);
}

QModelIndex BaseListModel::mapToSource(const QModelIndex& proxyIndex) const
{
	if (!proxyIndex.isValid())
	{
		return QModelIndex();
	}

	int row = proxyIndex.row();
	int shift = 0;
	int total = 0;
	for (const auto& value : m_sort_values)
	{
		if (row - total == 0)
		{
			return QModelIndex();
		}

		total += value.second + 1;
		shift++;
		if (total > row)
		{
			break;
		}
	}
	return sourceModel()->index(row - shift,0);
}

QVariant BaseListModel::data(const QModelIndex& index, int role) const
{
	if (!index.isValid())
	{
		return QVariant();
	}

	int row = index.row();
	int shift = 0;
	int total = 0;
	for (const auto& value : m_sort_values)
	{
		if (row - total == 0)
		{
			switch (role)
			{
			case Qt::DisplayRole:
				return "Title : " + value.first.toString();
			case IsFilterNameRole:
				return QVariant(true);
			default:
				return QAbstractProxyModel::data(index, role);
			}
		}

		total += value.second + 1;
		shift++;
		if (total > row)
		{
			if (role == IsFilterNameRole)
			{
				return false;
			}
			break;
		}
	}

	return sourceModel()->data(mapToSource(index),role);
}

QModelIndex BaseListModel::parent(const QModelIndex& index) const
{
	return QModelIndex();
}

QModelIndex BaseListModel::index(int row, int column, const QModelIndex& parent) const
{
	return createIndex(row,column,nullptr);
}

void BaseListModel::clean_data()
{
	m_sort_values.clear();
}

void BaseListModel::remap_data()
{
	for (int i = 0; i < m_source->rowCount(); ++i)
	{
		auto cur_value = m_source->data(m_source->index(i, 0), m_source->sortRole());
		if (m_sort_values.isEmpty() || m_sort_values.last().first != cur_value)
		{
			m_sort_values.push_back({ cur_value,1 });
		}
		else {
			m_sort_values.last().second++;
		}
	}
}
