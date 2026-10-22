#include "historymenu.h"
#include "ui_historymenu.h"

#include <QDate>
#include <QTime>

HistoryMenu::HistoryMenu(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::HistoryMenu)
{
    ui->setupUi(this);
    this->setWindowFlag(Qt::Window);

    auto HistoryTable = ui->HistoryTable;
    HistoryTable->setEditTriggers(QAbstractItemView::NoEditTriggers);
    HistoryTable->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);

    model = new QStandardItemModel(0, 3, this);

    model->setHeaderData(0, Qt::Horizontal, "Дата");
    model->setHeaderData(1, Qt::Horizontal, "Время");
    model->setHeaderData(2, Qt::Horizontal, "Действие");

    HistoryTable->setModel(model);
    HistoryTable->setWordWrap(true);
}

HistoryMenu::~HistoryMenu()
{
    delete ui;
}

void HistoryMenu::NewAction(QString InText)
{
    model->appendRow({new QStandardItem(QDate::currentDate().toString("dd.MM.yyyy")),
                    new QStandardItem(QTime::currentTime().toString("hh:mm:ss")),
                    new QStandardItem(InText)
                    });

    ui->HistoryTable->resizeRowToContents(model->rowCount() - 1);
}
