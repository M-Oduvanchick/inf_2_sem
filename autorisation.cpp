#include "autorisation.h"
#include "ui_autorisation.h"

Autorisation::Autorisation(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Autorisation)
{
    ui->setupUi(this);
    QFile file("./Users.json");
    setWindowTitle("Регистрация");
    file.open(QIODevice::ReadOnly|QFile::Text);
    doc = QJsonDocument::fromJson(QByteArray(file.readAll()), &docError);
    file.close();
    QJsonValue Users = doc.object().value("Users");
    docAr = QJsonValue(Users).toArray();
    json = docAr.at(0).toObject();
    setFixedSize(width(), height());
}

Autorisation::~Autorisation()
{
    delete ui;
}

bool Autorisation::isLogValid()
{
    //Логин не менее 4 символов
    //Содержит хотя бы одну букву
    //Не соддержит пробелов
    //Латиница
    bool Valid = (Log.length() > 3);
    bool ContainsW = false;
    for (int i = 0; i < Log.length() && Valid; i++)
    {
        Valid = (Log[i] != ' ') && (Log[i] < 127);
        if ((Log[i] > 64 && Log[i] < 91) || (Log[i] > 96  && Log[i] < 123))
        {
            ContainsW = true;
        }
    }
    return (Valid && ContainsW);
}

bool Autorisation::isPasValid()
{
    //Не менее 8 символов
    //Не содержит пробелов
    bool Valid = (Pas.length() > 7);
    for (int i = 0; i < Log.length() && Valid; i++) {
        Valid = (Log[i] != ' ');
    }
    return Valid;
}

void Autorisation::ToLogin()
{
    hide();
    to_login=new Login(this);
    to_login->show();
}

void Autorisation::ToRegistr()
{
    hide();
    to_autor=new Autorisation(this);
    to_autor->show();
}

void Autorisation::on_Registr_pushButton_clicked()
{
    QFile file("./Users.json");
        Log = ui->Login_lineEdit->text();
        Pas = ui->Password_lineEdit->text();
        if (!isLogValid() && !isPasValid())
        {
            char a[1000] = "Логин и пароль не корректны!\n\n"
                          "৹ Логин должен:\n"
                          "৹ Содержать не менее 4 символов\n"
                          "৹ Включать в себя хотя бы одну латинскую букву\n"
                          "৹ Не содержать пробелы\n"
                          "৹ Базироваться на латинице\n\n"
                           "Пароль должен:\n"
                           "৹ Содержать не менее 8 символов\n"
                           "৹ Не включать в себя пробелы";
            QMessageBox::critical(this, "Ошибка", a);
            ToRegistr();

        }
        else if (!isLogValid())
        {
            char a[1000] = "Логин не корректен!\n\n"
                          "৹ Логин должен:\n"
                          "৹ Содержать не менее 4 символов\n"
                          "৹ Включать в себя хотя бы одну латинскую букву\n"
                          "৹ Не содержать пробелы\n"
                          "৹ Базироваться на латинице";
            QMessageBox::critical(this, "Ошибка", a);
            ToRegistr();
        }
        else if (!isPasValid())
        {
            char a[1000] = "Пароль не корректен!\n\n"
                           "Пароль должен:\n"
                           "৹ Содержать не менее 8 символов\n"
                           "৹ Не включать в себя пробелы";
            QMessageBox::critical(this, "Ошибка", a);
            ToRegistr();
        }
        else if (json.find(Log) == json.end())
        {    //проверка на оригинальность логина
            file.open(QIODevice::WriteOnly);
            json.insert(Log, Pas);
            QJsonArray docToWrite = {};
            docToWrite.append(json);
            doc.setArray(docToWrite);
            file.write("{\"Users\":"+doc.toJson()+"}");
            file.close();
            QMessageBox::about(this, "Регистрация", "Регистрация прошла успешно!");
            ToLogin();
        }
        else
        {
            QMessageBox::critical(this, "Ошибка", "Логин уже используется!");
            ToLogin();
        }
}

