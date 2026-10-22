#ifndef HISTORYMENU_H
#define HISTORYMENU_H

#include "qstandarditemmodel.h"
#include <QWidget>

namespace Ui {
class HistoryMenu;
}

class HistoryMenu : public QWidget
{
    Q_OBJECT

public:
    explicit HistoryMenu(QWidget *parent = nullptr);
    ~HistoryMenu();

    QStandardItemModel* model;

    void NewAction(QString);

private:
    Ui::HistoryMenu *ui;
};

#endif // HISTORYMENU_H
