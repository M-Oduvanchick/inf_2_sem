#ifndef PRODUCT_CLASS_H
#define PRODUCT_CLASS_H
#include <QString>

class Product_class
{
public:
    Product_class();
    Product_class(const QString &sku, const QString &name, double price, int quantity);

    QString getSku() const;
    QString getName() const;
    double getPrice() const;
    int getQuantity() const;

    void setQuantity(int newQuantity);
private:
    QString sku;
    QString name;
    double price;
    int quantity;
};

#endif // PRODUCT_CLASS_H
