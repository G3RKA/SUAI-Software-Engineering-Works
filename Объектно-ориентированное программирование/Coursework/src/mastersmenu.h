#ifndef MASTERSMENU_H
#define MASTERSMENU_H

#include "qstandarditemmodel.h"
#include "master.h"
#include <QWidget>

namespace Ui {
class MastersMenu;
}

class MastersMenu : public QWidget
{
    Q_OBJECT

public:
    explicit MastersMenu(QWidget *parent = nullptr);
    ~MastersMenu();
    bool IsMasterInList(QString);
    void SetMasterBusyStatusByRegCode(QString, int);
    Master* GetMasterByRegCode(QString);
    void ClearInputs();
    void FireMaster(QString);


signals:
    void RequestToRemoveMaster(QString);

private:
    Ui::MastersMenu* ui;
    int NumOfMasters;
    QList<Master*> MasterList;
    QStandardItemModel* model;

    void SetModelHeader();
    void AddNewMasterToModel(Master*);

public slots:
    void UpdatePlaceList(QString);

private slots:
    void InfoChanged();
    void RegNumberChanged();
    void RequestToAddMaster();
};

#endif // MASTERSMENU_H
