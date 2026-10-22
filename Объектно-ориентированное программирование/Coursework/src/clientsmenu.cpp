#include "clientsmenu.h"
#include "client.h"
#include "ui_clientsmenu.h"
#include "ordermanipulate.h"
#include <QStandardItemModel>

ClientsMenu::ClientsMenu(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::ClientsMenu)
{
    ui->setupUi(this);
    this->setWindowFlag(Qt::Window);

    this->NumOfClients = 0;
    auto ClientTable = ui->ClientTable;
    ClientTable->setEditTriggers(QAbstractItemView::NoEditTriggers);
    ClientTable->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);

    model = new QStandardItemModel(0, 4, this);
    SetModelHeader();

    ClientTable->setModel(model);
    ClientTable->setWordWrap(true);
    ui->PhoneEdit->setInputMask("+7 999 999 99-99;_");

    AddNewClientToModel(new Client(nullptr, "Коновалов Валерий Александрович", "ул. Кооперативная, 13, кв. 94", "+7 946 535 54-35"));
    AddNewClientToModel(new Client(nullptr, "Рыбаков Григорий Валерьянович", "ул. Речная, 4, кв. 51", "+7 945 541 54-35"));
    AddNewClientToModel(new Client(nullptr, "Петухова Ульяна Тимуровна", "ул. Школьная, 48, кв. 18", "+7 435 435 58-85"));
    AddNewClientToModel(new Client(nullptr, "Архипов Арсений Куприянович", "ул. Фрунзе, 24, кв. 32", "+7 435 795 58-85"));

    connect(ui->AddClient, &QPushButton::clicked, this, &ClientsMenu::RequestToAddClient);
    connect(ui->FIOEdit, &QLineEdit::textChanged, this, &ClientsMenu::InfoChanged);
    connect(ui->AdressEdit, &QLineEdit::textChanged, this, &ClientsMenu::InfoChanged);
    connect(ui->PhoneEdit, &QLineEdit::textChanged, this, &ClientsMenu::InfoChanged);
}

ClientsMenu::~ClientsMenu()
{
    auto ListBegin = ClientsList.begin();
    auto ListEnd = ClientsList.end();
    for (;ListBegin<ListEnd; ListBegin++)
    {
        delete *ListBegin;

    }
    delete ui;
}

void ClientsMenu::SetModelHeader()
{
    model->setHeaderData(0, Qt::Horizontal, "Регистрационный номер");
    model->setHeaderData(1, Qt::Horizontal, "ФИО");
    model->setHeaderData(2, Qt::Horizontal, "Адрес");
    model->setHeaderData(3, Qt::Horizontal, "Телефон");
}

void ClientsMenu::ClearInputs()
{
    ui->AddClient->setDisabled(true);

    ui->FIOEdit->clear();
    ui->AdressEdit->clear();
    ui->PhoneEdit->clear();
}

void ClientsMenu::AddNewClientToModel(Client* ClientInfo)
{
    int IndexForAdd = ++this->NumOfClients-1;
    model->setItem(IndexForAdd, 0, new QStandardItem(QString::number(ClientInfo->GetRegNumber())));
    model->setItem(IndexForAdd, 1, new QStandardItem(ClientInfo->GetFIO()));
    model->setItem(IndexForAdd, 2, new QStandardItem(ClientInfo->GetAdress()));
    model->setItem(IndexForAdd, 3, new QStandardItem(ClientInfo->GetPhoneNumber()));
    ClientsList.append(ClientInfo);

    ui->ClientTable->resizeRowToContents(model->rowCount() - 1);

    OrderManipulate::NewAction("Добавлен клиент " + QString::number(ClientInfo->GetRegNumber()) + " " + ClientInfo->GetFIO());
}

void ClientsMenu::RemoveClientFromModel(int RegNumber)
{
    auto ListBegin = ClientsList.begin();
    auto ListEnd = ClientsList.end();
    QList<Client*>::iterator finded = ListEnd;
    for (;ListBegin<ListEnd; ListBegin++)
    {
        if ((*ListBegin)->GetRegNumber() == RegNumber)
        {
            finded = ListBegin;
            break;
        }
    }

    int IndexOfFinded = finded-ClientsList.begin();
    if (finded != ListEnd)
    {
        OrderManipulate::NewAction("Удалён клиент " + QString::number((*finded)->GetRegNumber()) + " " + (*finded)->GetFIO());

        ClientsList.erase(finded);
        model->removeRow(IndexOfFinded);
        this->NumOfClients--;
    }


}

bool ClientsMenu::IsClientInList(int RegNumber)
{
    auto ListBegin = ClientsList.begin();
    auto ListEnd = ClientsList.end();
    for (;ListBegin<ListEnd; ListBegin++)
    {
        if ((*ListBegin)->GetRegNumber() == RegNumber)
        {
            return true;
        }
    }
    return false;
}

void ClientsMenu::RequestToAddClient()
{
    QString PhoneNumber = ui->PhoneEdit->text();
    if (not(IsClientInList(Client::PhoneNumberToRegNumber(PhoneNumber))))
    {
        AddNewClientToModel(new Client(nullptr, ui->FIOEdit->text(), ui->AdressEdit->text(), PhoneNumber));
    }
    else
    {
        OrderManipulate::SendErrorMessage("Такой клиент уже существует.");
        return;
    }
    ClearInputs();
}

void ClientsMenu::InfoChanged()
{
    if (ui->PhoneEdit->hasAcceptableInput() && not(ui->FIOEdit->text().isEmpty()) && not(ui->AdressEdit->text().isEmpty()))
    {
        ui->AddClient->setDisabled(false);
    }
    else
    {
        ui->AddClient->setDisabled(true);
    }
}
