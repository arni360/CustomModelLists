#pragma once

#include <QtWidgets/QMainWindow>
#include "ui_CustomModelLists.h"
class CustomDelegate;
class CustomModelLists : public QMainWindow
{
    Q_OBJECT

public:
    CustomModelLists(QWidget *parent = nullptr);
    ~CustomModelLists();
    virtual bool eventFilter(QObject* watched, QEvent* event) override;
private:
    Ui::CustomModelListsClass ui;
    CustomDelegate* m_delegate;
    QListView* m_list_view;
};
