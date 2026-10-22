#include "mainwindow.h"

#include <QDateEdit>
#include <QHBoxLayout>
#include <QHeaderView>
#include <QLineEdit>
#include <QPushButton>
#include <QTableWidget>
#include <QVBoxLayout>

MainWindow::MainWindow(QWidget *parent)
    : QWidget(parent)
{
    setWindowTitle("Список задач");

    editName = new QLineEdit;
    editName->setPlaceholderText("Название задачи");
    editDate = new QDateEdit(QDate::currentDate());
    QPushButton *buttonAdd = new QPushButton("Добавить");

    table = new QTableWidget(0, 2);
    table->setHorizontalHeaderLabels({"Задача", "Срок"});
    table->horizontalHeader()->setSectionResizeMode(0, QHeaderView::Stretch);

    QHBoxLayout *input = new QHBoxLayout;
    input->addWidget(editName);
    input->addWidget(editDate);
    input->addWidget(buttonAdd);

    QVBoxLayout *layout = new QVBoxLayout(this);
    layout->addLayout(input);
    layout->addWidget(table);

    connect(buttonAdd, &QPushButton::clicked, this, &MainWindow::addTask);

    resize(480, 320);
}

void MainWindow::addTask()
{
    if (editName->text().isEmpty())
        return;

    QString date = editDate->date().toString("dd.MM.yyyy");
    int row = table->rowCount();
    table->insertRow(row);
    table->setItem(row, 0, new QTableWidgetItem(editName->text()));
    table->setItem(row, 1, new QTableWidgetItem(date));
    editName->clear();
}
