#include "product_class.h"

Product_class::Product_class()
{

}

Product_class::Product_class(const QString &sku, const QString &name, double price, int quantity)
    : sku(sku), name(name), price(price), quantity(quantity) {}

QString Product_class::getSku() const {
    return sku;
}

QString Product_class::getName() const {
    return name;
}

double Product_class::getPrice() const {
    return price;
}

int Product_class::getQuantity() const {
    return quantity;
}

void Product_class::setQuantity(int newQuantity) {
    quantity = newQuantity;
}
