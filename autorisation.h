#ifndef AUTORISATION_H
#define AUTORISATION_H

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
#include "login.h"

namespace Ui {
class Autorisation;
}

class Autorisation : public QDialog
{
    Q_OBJECT

public:
    explicit Autorisation(QWidget *parent = nullptr);
    ~Autorisation();
    QJsonDocument doc;
    QJsonArray docAr;
    QJsonParseError docError;
    QJsonObject UsersDataJson;
    QJsonObject json;

private slots:

    void on_Registr_pushButton_clicked();

private:
    Ui::Autorisation *ui;
    Login* to_login;
    Autorisation* to_autor;
    void ToRegistr();
    void ToLogin();
    QString Log, Pas;
    QMap<QString, QString> UsersData;
    bool isLogValid();
    bool isPasValid();
};

#endif // AUTORISATION_H
