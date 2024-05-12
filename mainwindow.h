#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "autorisation.h"
#include "login.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_Enter_clicked();

    void on_Registration_pushButton_clicked();

private:
    Ui::MainWindow *ui;
    Autorisation *window;
    Login *login_window;
};
#endif // MAINWINDOW_H
