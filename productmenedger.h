#ifndef PRODUCTMENEDGER_H
#define PRODUCTMENEDGER_H
#include <QList>
#include "product_class.h"

class ProductMenedger
{
public:
    ProductMenedger();
    void addProduct(const Product_class &product);
    bool removeProduct(const QString &sku);
    void sellProduct(const QString &sku);
    double calculateTotal() const;
    double calculateSoldTotal() const;
    double calculateInventoryValue() const;
private:
    QList<Product_class> products;
    QList<Product_class> soldProducts;
};

#endif // PRODUCTMENEDGER_H
