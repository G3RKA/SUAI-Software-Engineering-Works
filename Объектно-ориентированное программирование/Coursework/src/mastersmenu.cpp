#include "mastersmenu.h"
#include "ordermanipulate.h"
#include "ui_mastersmenu.h"

MastersMenu::MastersMenu(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::MastersMenu)
{
    ui->setupUi(this);
    this->setWindowFlag(Qt::Window);

    model = new QStandardItemModel(0, 6, this);
    SetModelHeader();

    this->NumOfMasters = 0;
    auto MasterTable = ui->MastersTable;
    MasterTable->setEditTriggers(QAbstractItemView::NoEditTriggers);
    MasterTable->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);

    MasterTable->setModel(model);
    MasterTable->setWordWrap(true);
    ui->RegEdit->setInputMask(">AA-9000;_");

    AddNewMasterToModel(new Master(nullptr, "Тетерин Емельян Васильевич", "Junior", "На ленинском"));
    AddNewMasterToModel(new Master(nullptr, "Носкова Мия Вячеславовна", "Junior", "На московской"));
    AddNewMasterToModel(new Master(nullptr, "Карпов Иван Филатович", "Senior", "На ленинском"));
    AddNewMasterToModel(new Master(nullptr, "Ефимов Людвиг Анатольевич", "Middle", "На московской"));

    connect(ui->AddMaster, &QPushButton::clicked, this, &MastersMenu::RequestToAddMaster);
    connect(ui->RemoveMaster, &QPushButton::clicked, this, [this] {emit RequestToRemoveMaster(ui->RegEdit->text());});
    connect(ui->PositionCombo, &QComboBox::currentTextChanged, this, &MastersMenu::InfoChanged);
    connect(ui->FIOEdit, &QLineEdit::textChanged, this, &MastersMenu::InfoChanged);
    connect(ui->RegEdit, &QLineEdit::textChanged, this, &MastersMenu::RegNumberChanged);
}

MastersMenu::~MastersMenu()
{
    auto ListBegin = MasterList.begin();
    auto ListEnd = MasterList.end();
    for (;ListBegin<ListEnd; ListBegin++)
    {
        delete *ListBegin;

    }
    delete ui;
}

void MastersMenu::SetMasterBusyStatusByRegCode(QString RegCode, int OrderNumber)
{
    auto ListBegin = MasterList.begin();
    auto ListEnd = MasterList.end();
    for (;ListBegin<ListEnd; ListBegin++)
    {
        if ((*ListBegin)->GetRegCode() == RegCode)
        {
            break;
        }
    }

    (*ListBegin)->SetOrder(OrderNumber);
    model->setItem(ListBegin-MasterList.begin(), 5, new QStandardItem((*ListBegin)->GetOrderStatus()));
}

void MastersMenu::SetModelHeader()
{
    model->setHeaderData(0, Qt::Horizontal, "Номер");
    model->setHeaderData(1, Qt::Horizontal, "ФИО");
    model->setHeaderData(2, Qt::Horizontal, "Должность");
    model->setHeaderData(3, Qt::Horizontal, "Точка");
    model->setHeaderData(4, Qt::Horizontal, "Статус");
    model->setHeaderData(5, Qt::Horizontal, "Заказ");
}

void MastersMenu::ClearInputs()
{
    ui->AddMaster->setDisabled(true);
    ui->RemoveMaster->setDisabled(true);

    ui->FIOEdit->clear();
    ui->PositionCombo->setCurrentIndex(0);
    ui->RegEdit->clear();
}

void MastersMenu::AddNewMasterToModel(Master* MasterInfo)
{
    int IndexForAdd = ++this->NumOfMasters-1;
    model->setItem(IndexForAdd, 0, new QStandardItem(MasterInfo->GetRegCode()));
    model->setItem(IndexForAdd, 1, new QStandardItem(MasterInfo->GetFIO()));
    model->setItem(IndexForAdd, 2, new QStandardItem(MasterInfo->GetPosition()));
    model->setItem(IndexForAdd, 3, new QStandardItem(MasterInfo->GetPlaceName()));
    model->setItem(IndexForAdd, 4, new QStandardItem(MasterInfo->GetStatusString()));
    model->setItem(IndexForAdd, 5, new QStandardItem(MasterInfo->GetOrderStatus()));
    MasterList.append(MasterInfo);

    ui->MastersTable->resizeRowToContents(model->rowCount() - 1);

    OrderManipulate::NewAction("Добавлен мастер " + MasterInfo->GetRegCode() + " " + MasterInfo->GetFIO());
}

void MastersMenu::UpdatePlaceList(QString PlaceName)
{
    ui->PlaceComboBox->addItem(PlaceName);
}

void MastersMenu::FireMaster(QString RegCode)
{
    auto ListBegin = MasterList.begin();
    auto ListEnd = MasterList.end();
    QList<Master*>::iterator finded = ListEnd;
    for (;ListBegin<ListEnd; ListBegin++)
    {
        if ((*ListBegin)->GetRegCode() == RegCode)
        {
            finded = ListBegin;
            break;
        }
    }
    int IndexOfFinded = finded-MasterList.begin();
    if (finded != ListEnd)
    {
        OrderManipulate::NewAction("Мастер " + (*finded)->GetRegCode() + " " + (*finded)->GetFIO() + " уволен");
        (*finded)->SetStatus(false);
        model->setItem(IndexOfFinded, 4, new QStandardItem((*finded)->GetStatusString()));
    }
}

bool MastersMenu::IsMasterInList(QString RegCode)
{
    auto ListBegin = MasterList.begin();
    auto ListEnd = MasterList.end();
    for (;ListBegin<ListEnd; ListBegin++)
    {
        if ((*ListBegin)->GetRegCode() == RegCode)
        {
            return true;
        }
    }
    return false;
}

Master* MastersMenu::GetMasterByRegCode(QString RegCode)
{
    auto ListBegin = MasterList.begin();
    auto ListEnd = MasterList.end();
    for (;ListBegin<ListEnd; ListBegin++)
    {
        if ((*ListBegin)->GetRegCode() == RegCode)
        {
            return *ListBegin;
        }
    }
    return nullptr;
}

void MastersMenu::RequestToAddMaster()
{
    QString FIO = ui->FIOEdit->text();
    QString Position = ui->PositionCombo->currentText();
    QString RegCode = Master::FIOnPosToRegCode(FIO, Position);
    QString PlaceName = ui->PlaceComboBox->currentText();
    if (not(IsMasterInList(RegCode)))
    {
        AddNewMasterToModel(new Master(nullptr, FIO, Position, PlaceName));
    }
    else
    {
        OrderManipulate::SendErrorMessage("Такой мастер уже существует.");
        return;
    }
    ClearInputs();
}

void MastersMenu::InfoChanged()
{
    if (not(ui->PositionCombo->currentText().isEmpty()) && not(ui->FIOEdit->text().isEmpty()) &&
        not(ui->FIOEdit->text().size() > 31))
    {
        ui->AddMaster->setDisabled(false);
    }
    else
    {
        ui->AddMaster->setDisabled(true);
    }
}

void MastersMenu::RegNumberChanged()
{
    if (ui->RegEdit->hasAcceptableInput() && NumOfMasters>0)
    {
        ui->RemoveMaster->setDisabled(false);
    }
    else
    {
        ui->RemoveMaster->setDisabled(true);
    }
}
