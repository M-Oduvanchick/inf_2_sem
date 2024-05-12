#ifndef LOGIN_H
#define LOGIN_H

#include <QDialog>
#include <QMainWindow>
#include <QMessageBox>
#include <QMap>
#include <QFile>
#include <QJsonObject>
#include <QFileDialog>
#include <QStandardItem>
#include <QJsonDocument>
#include <QJsonArray>
#include <QJsonParseError>
#include "product.h"

namespace Ui {
class Login;
}

class Login : public QDialog
{
    Q_OBJECT

public:
    explicit Login(QWidget *parent = nullptr);
    ~Login();
    QJsonDocument doc;
    QJsonArray docAr;
    QJsonParseError docError;
    QJsonObject UsersDataJson;
    QJsonObject json;

private slots:

    void on_Enter_pushButton_clicked();

private:
    Ui::Login *ui;
    Product* main_product;
    void ToMain();
    QString Log, Pas;
    QMap<QString, QString> UsersData;
    bool isLogValid();
    bool isPasValid();
};

#endif // LOGIN_H
