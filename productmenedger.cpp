#include "productmenedger.h"

ProductMenedger::ProductMenedger()
{
}


void ProductMenedger::addProduct(const Product_class &product) {
    products.append(product);
}

bool ProductMenedger::removeProduct(const QString &sku) {
    for (int i = 0; i < products.size(); ++i) {
        if (products[i].getSku() == sku) {
            products.removeAt(i);
            return true;
        }
    }
    return false;
}

void ProductMenedger::sellProduct(const QString &sku) {
    for (int i = 0; i < products.size(); ++i)
    {
        if (products[i].getSku() == sku && products[i].getQuantity() > 0)
        {
            // Уменьшаем количество на 1
            int newQuantity = products[i].getQuantity() - 1;
            products[i].setQuantity(newQuantity);

            // Добавляем продукт в список проданных
            Product_class soldProduct = products[i];
            soldProduct.setQuantity(1); // Устанавливаем количество проданного товара равным 1 для корректной записи в истории продаж
            soldProducts.append(soldProduct);

            // Если количество продукта становится равным нулю, удаляем его из списка доступных
            if (newQuantity == 0)
            {
                products.removeAt(i);
            }
            return; // Завершаем функцию, так как продукт уже обработан
        }
    }
}

double ProductMenedger::calculateTotal() const {
    double total = 0;
    for (const Product_class &product : products) {
        total += product.getPrice() * product.getQuantity();
    }
    return total;
}

double ProductMenedger::calculateSoldTotal() const {
    double total = 0;
    for (const Product_class &product : soldProducts) {
        total += product.getPrice();
    }
    return total;
}

double ProductMenedger::calculateInventoryValue() const {
    return calculateTotal() - calculateSoldTotal();
}
