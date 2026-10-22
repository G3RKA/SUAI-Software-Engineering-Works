#include "mainwindow.h"

#include <QComboBox>
#include <QDoubleValidator>
#include <QFormLayout>
#include <QHBoxLayout>
#include <QLabel>
#include <QLineEdit>
#include <QMessageBox>
#include <QPushButton>
#include <QVBoxLayout>

MainWindow::MainWindow(QWidget *parent)
    : QWidget(parent)
{
    setWindowTitle("Калькулятор");

    editA = new QLineEdit("12");
    editB = new QLineEdit("5");
    editA->setValidator(new QDoubleValidator(this));
    editB->setValidator(new QDoubleValidator(this));

    comboOp = new QComboBox;
    comboOp->addItems({"+", "-", "*", "/"});

    labelResult = new QLabel("Результат: ");
    QFont font = labelResult->font();
    font.setPointSize(12);
    font.setBold(true);
    labelResult->setFont(font);

    QPushButton *buttonCalc = new QPushButton("Вычислить");
    QPushButton *buttonClear = new QPushButton("Очистить");

    QFormLayout *form = new QFormLayout;
    form->addRow("Число A:", editA);
    form->addRow("Операция:", comboOp);
    form->addRow("Число B:", editB);

    QHBoxLayout *buttons = new QHBoxLayout;
    buttons->addWidget(buttonCalc);
    buttons->addWidget(buttonClear);

    QVBoxLayout *layout = new QVBoxLayout(this);
    layout->addLayout(form);
    layout->addLayout(buttons);
    layout->addWidget(labelResult);

    connect(buttonCalc, &QPushButton::clicked, this, &MainWindow::calculate);
    connect(buttonClear, &QPushButton::clicked, this, &MainWindow::clear);

    resize(300, 170);
}

void MainWindow::calculate()
{
    double a = editA->text().toDouble();
    double b = editB->text().toDouble();
    QString op = comboOp->currentText();
    double result = 0;

    if (op == "+")
        result = a + b;
    else if (op == "-")
        result = a - b;
    else if (op == "*")
        result = a * b;
    else {
        if (b == 0) {
            QMessageBox::warning(this, "Ошибка", "Деление на ноль невозможно");
            return;
        }
        result = a / b;
    }

    labelResult->setText("Результат: " + QString::number(result));
}

void MainWindow::clear()
{
    editA->clear();
    editB->clear();
    labelResult->setText("Результат: ");
}
