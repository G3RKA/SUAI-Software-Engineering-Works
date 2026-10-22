#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QWidget>

class QTableWidget;
class QLineEdit;
class QDateEdit;

class MainWindow : public QWidget
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);

private slots:
    void addTask();

private:
    QTableWidget *table;
    QLineEdit *editName;
    QDateEdit *editDate;
};

#endif // MAINWINDOW_H
