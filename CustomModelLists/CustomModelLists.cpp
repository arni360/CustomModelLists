#include "CustomModelLists.h"
#include "BaseListModel.h"
#include "CustomDelegate.h"
#include <QStandardItemModel>
#include <QConcatenateTablesProxyModel>

CustomModelLists::CustomModelLists(QWidget *parent)
    : QMainWindow(parent)
{
    ui.setupUi(this);
    QStandardItemModel* model1 = new QStandardItemModel(this);
    model1->appendRow(new QStandardItem("A-0"));
    model1->appendRow(new QStandardItem("A-0"));
    model1->appendRow(new QStandardItem("A-1"));
    model1->appendRow(new QStandardItem("A-2"));
    model1->appendRow(new QStandardItem("A-3"));

    model1->appendRow(new QStandardItem("B-0"));
    model1->appendRow(new QStandardItem("B-1"));
    model1->appendRow(new QStandardItem("B-2"));
    model1->appendRow(new QStandardItem("B-3"));
    model1->appendRow(new QStandardItem("C-0"));
    model1->appendRow(new QStandardItem("C-1"));
    model1->appendRow(new QStandardItem("C-2"));
    model1->appendRow(new QStandardItem("C-3"));
    BaseListModel* concat = new BaseListModel(this);
    concat->set_source_model(model1);
    m_list_view = ui.listView;
    ui.listView->setViewMode(QListView::IconMode);
    ui.listView->setModel(concat);
    m_delegate = new CustomDelegate(this);
    ui.listView->setItemDelegate(m_delegate);
    ui.listView->installEventFilter(this);
}

CustomModelLists::~CustomModelLists()
{}

bool CustomModelLists::eventFilter(QObject * watched, QEvent * event)
{
    if (watched == m_list_view && event->type() == QEvent::Resize)
    {
        m_delegate->maxWidth = m_list_view->contentsRect().width();
    }
    return QMainWindow::eventFilter(watched, event);
}
