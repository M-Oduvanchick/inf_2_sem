#include "login.h"
#include "ui_login.h"
#include <autorisation.h>

Login::Login(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Login)
{
    ui->setupUi(this);
    setWindowTitle("Вход");
    QFile file("./Users.json");
    file.open(QIODevice::ReadOnly|QFile::Text);
    doc = QJsonDocument::fromJson(QByteArray(file.readAll()), &docError);
    file.close();
    QJsonValue Users = doc.object().value("Users");
    docAr = QJsonValue(Users).toArray();
    json = docAr.at(0).toObject();
}

Login::~Login()
{
    delete ui;
}

void Login::ToMain()
{
    hide();
    main_product=new Product(this);
    main_product->show();
}

void Login::on_Enter_pushButton_clicked()
{
    Log = ui->Login_reg_lineEdit->text();
    Pas = ui->Password_reg_lineEdit->text();
    if (json.find(Log) != json.end())
   {//если логин существует
        if (json.value(Log) == Pas)
        {//проверка сходимости паролей
            ToMain();
        }
        else
        {
            QMessageBox::critical(this, "Ошибка", "Логин или пароль не верны!");
        }
    }
    else
    {
        QMessageBox::critical(this, "Ошибка", "Указанный логин не существует!");
    }
}

