#pragma once
#include <QStyledItemDelegate>
class CustomDelegate : public QStyledItemDelegate
{
public: 
	CustomDelegate(QObject* parent = nullptr);
	virtual QSize	sizeHint(const QStyleOptionViewItem& option, const QModelIndex& index) const override;
	int maxWidth = 100;
};

