#ifndef ORDERMANIPULATE_H
#define ORDERMANIPULATE_H

#include "mainwindow.h"
#include "order.h"
#include <QWidget>

class OrderManipulate : public QWidget
{
    Q_OBJECT
public:
    explicit OrderManipulate(QWidget *parent = nullptr);
    static void SetRootWidget(MainWindow*);
    static void SendErrorMessage(QString);
    static void AddOrder(Order*);
    static void ExecuteOrder(int);
    static void RemoveOrder(int);
    static void RemoveMaster(QString);
    static void NewAction(QString);

private:
    static MainWindow* RootWidget;
};

#endif // ORDERMANIPULATE_H
