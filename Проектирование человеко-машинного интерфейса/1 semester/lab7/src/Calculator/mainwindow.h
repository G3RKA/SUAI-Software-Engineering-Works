#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QWidget>

class QLineEdit;
class QComboBox;
class QLabel;

class MainWindow : public QWidget
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);

private slots:
    void calculate();
    void clear();

private:
    QLineEdit *editA;
    QLineEdit *editB;
    QComboBox *comboOp;
    QLabel *labelResult;
};

#endif // MAINWINDOW_H
