#ifndef THINGSMENU_H
#define THINGSMENU_H

#include "qstandarditemmodel.h"
#include "thing.h"
#include <QWidget>

namespace Ui {
class ThingsMenu;
}

class ThingsMenu : public QWidget
{
    Q_OBJECT

public:
    explicit ThingsMenu(QWidget *parent = nullptr);
    ~ThingsMenu();

    void ClearInputs();
    void SetOrderStatusByName(QString, int);
    bool IsThingNameInList(QString);
    Thing* GetThingByName(QString);

private:
    Ui::ThingsMenu *ui;
    int NumOfThings;
    QList<Thing*> ThingsList;
    QStandardItemModel* model;

    void AddNewThingToModel(Thing*);
    void SetModelHeader();

public slots:
    void RequestToAddThing();
    void UpdatePlaceList(QString);
    void InfoChanged();
};

#endif // THINGSMENU_H
