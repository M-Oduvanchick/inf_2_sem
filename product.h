#ifndef PRODUCT_H
#define PRODUCT_H

#include <QMainWindow>

namespace Ui {
class Product;
}

class Product : public QMainWindow
{
    Q_OBJECT

public:


    explicit Product(QWidget *parent = nullptr);
    ~Product();
    void addProduct();
    void deleteLProduct();
    void sellProduct();
    double totalSales = 0.0;
    double getTotalSales() const;
    void calculateTotalBudget();
    void TotalSalesSum();
    void getRemainsSales();
    void performRevision();
    void displayProductInfo();

private slots:

    void on_addProduct_clicked();
    void on_deleteLProduct_clicked();
    void on_sellProduct_clicked();

    void on_calculateTotalBudget_clicked();

    void on_sale_clicked();

    void on_Remains_clicked();

    void on_revizion_clicked();

    void on_Information_clicked();

private:
    Ui::Product *ui;

};

#endif // PRODUCT_H
