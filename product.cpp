#include "product.h"
#include "ui_product.h"
#include <QApplication>
#include <QMainWindow>
#include <QPushButton>
#include <QTableWidget>
#include <QLineEdit>
#include <QMessageBox>

Product::Product(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::Product)
{
    ui->setupUi(this);
}

Product::~Product()
{
    delete ui;
}

void Product::addProduct()
{
    // Считывание данных из полей ввода
    QString sku = ui->skuLineEdit->text();
    QString name = ui->nameLineEdit->text();
    double price = ui->priceSpinBox->value();
    int quantity = ui->quantitySpinBox->value();

    // Проверка на правильность введенных данных
    if (sku.isEmpty() || name.isEmpty() || price <= 0 || quantity <= 0) {
        QMessageBox::warning(this, "Внимание", "Все поля должны быть корректно заполнены!");
        return;
    }

    // Создание новой строки в таблице
    int currentRow = ui->tableWidget->rowCount();
    ui->tableWidget->insertRow(currentRow);

    QTableWidgetItem *skuItem = new QTableWidgetItem(sku);
    QTableWidgetItem *nameItem = new QTableWidgetItem(name);
    QTableWidgetItem *priceItem = new QTableWidgetItem(QString::number(price, 'f', 2));
    QTableWidgetItem *quantityItem = new QTableWidgetItem(QString::number(quantity));


    ui->tableWidget->setItem(currentRow, 0, nameItem);
    ui->tableWidget->setItem(currentRow, 1, skuItem);
    ui->tableWidget->setItem(currentRow, 2, priceItem);
    ui->tableWidget->setItem(currentRow, 3, quantityItem);


    ui->skuLineEdit->clear();
    ui->nameLineEdit->clear();
    ui->priceSpinBox->setValue(0.0);
    ui->quantitySpinBox->setValue(0);
}

void Product::deleteLProduct()
{
    // Получаем список выделенных элементов в таблице
    QList<QTableWidgetItem*> selectedItems = ui->tableWidget->selectedItems();

    if (selectedItems.isEmpty()) {
        QMessageBox::warning(this, "Внимание", "Необходимо выбрать продукт для удаления!");
        return;
    }

    // Спрашиваем пользователя, уверен ли он в своем действии
    auto reply = QMessageBox::question(this, "Подтверждение удаления",
                                       "Вы уверены, что хотите удалить выбранные продукты?",
                                       QMessageBox:: Yes | QMessageBox::No);

    if (reply == QMessageBox::Yes)
    {
        // Проходимся по всем выделенным строкам и удаляем их
        while (!selectedItems.isEmpty())
        {
            // Удаляем строку каждого первого элемента из списка выделенных
            int row = selectedItems.first()->row();
            ui->tableWidget->removeRow(row);
            // Необходимо обновить список выделенных элементов после удаления строки
            selectedItems = ui->tableWidget->selectedItems();
        }
    }
}

void Product::sellProduct()
{
    // Получаем выбранную строку
    int currentRow = ui->tableWidget->currentRow();
    if (currentRow == -1)
    {
        QMessageBox::warning(this, "Внимание", "Выберите продукт для продажи!");
                return;
    }

    // Получаем элементы из строки таблицы
    QTableWidgetItem *quantityItem = ui->tableWidget->item(currentRow, 3);
    QTableWidgetItem *priceItem = ui->tableWidget->item(currentRow, 2);

    // Обновляем количество
    int quantity = quantityItem->text().toInt();
    if (quantity > 0)
    {
        quantity--;
        quantityItem->setText(QString::number(quantity));

        // Обновляем сумму продаж
        double price = priceItem->text().toDouble();
        totalSales += price; // Обновление суммы продаж
    }
    else
    {
        QMessageBox::warning(this, "Ошибка", "Продукт невозможно продать, так как его нет на складе!");
    }
}

double Product::getTotalSales() const
{
    return totalSales;
}

void Product::calculateTotalBudget()
{
    double totalInventoryValue = 0.0;
    double totalSalesValue = 0.0;

    // Обход всех строк в таблице
    for (int row = 0; row < ui->tableWidget->rowCount(); ++row)
    {
        QTableWidgetItem *priceItem = ui->tableWidget->item(row, 2);
        QTableWidgetItem *quantityItem = ui->tableWidget->item(row, 3);

        if (!priceItem || !quantityItem) continue; // Пропустить пустые строки

        double price = priceItem->text().toDouble();
        int quantity = quantityItem->text().toInt();

        totalInventoryValue += price * quantity;
    }

    totalSalesValue = getTotalSales();
    QMessageBox::information(this, "Общий бюджет",
                                 "Общая стоимость инвентаря: " + QString::number(totalInventoryValue, 'f', 2) +
                                 "\nОбщая стоимость продаж: " + QString::number(totalSalesValue, 'f', 2));

}

void Product::getRemainsSales()
{
    double totalInventoryValue = 0.0;

    // Обход всех строк в таблице
    for (int row = 0; row < ui->tableWidget->rowCount(); ++row)
    {
        QTableWidgetItem *priceItem = ui->tableWidget->item(row, 2);
        QTableWidgetItem *quantityItem = ui->tableWidget->item(row, 3);

        if (!priceItem || !quantityItem) continue; // Пропустить пустые строки

        double price = priceItem->text().toDouble();
        int quantity = quantityItem->text().toInt();

        totalInventoryValue += price * quantity;
    }


    // Показать результаты в диалоговом окне
    QMessageBox::information(this, "Общий бюджет",
                             "Общая стоимость инвентаря: " + QString::number(totalInventoryValue, 'f', 2));
}

void Product::performRevision()
{
    double totalInventoryValue = 0.0;
    double totalSalesValue = getTotalSales(); // Эта переменная должна хранить общую сумму продаж

    // Расчет общей стоимости всех продуктов в инвентаре
    for (int row = 0; row < ui->tableWidget->rowCount(); ++row)
    {
        QTableWidgetItem *priceItem = ui->tableWidget->item(row, 2);
        QTableWidgetItem *quantityItem = ui->tableWidget->item(row, 3);

        if (!priceItem || !quantityItem) continue; // Пропустить пустые строки

        double price = priceItem->text().toDouble();
        int quantity = quantityItem->text().toInt();

        totalInventoryValue += price * quantity;
    }

    // Вычисление разницы
    double revisionResult = totalInventoryValue - totalSalesValue;

    // Вывод результата
    QMessageBox::information(this, "Ревизия",
                             "Результат ревизии:\nОбщий бюджет: " + QString::number(totalInventoryValue, 'f', 2) +
                             "\nПродано на: " + QString::number(totalSalesValue, 'f', 2) +
                             "\nРазница: " + QString::number(revisionResult, 'f', 2));
}

void Product::TotalSalesSum()
{
    double totalSalesValue = 0.0;

    totalSalesValue = getTotalSales();

    // Показать результаты в диалоговом окне
    QMessageBox::information(this, "Общий бюджет",
                             "Общая стоимость продаж: " + QString::number(totalSalesValue, 'f', 2));
}

void Product::displayProductInfo()
{
    QString skuToFind = ui->skuLineEdit->text();
    if (skuToFind.isEmpty())
    {
        QMessageBox::warning(this, "Ошибка", "Введите артикул продукта.");
        return;
    }

    bool found = false;
    QString info;

    // Поиск в каждой строке таблицы
    for (int row = 0; row < ui->tableWidget->rowCount(); ++row)
    {
        QTableWidgetItem *skuItem = ui->tableWidget->item(row, 1);
        if (skuItem && skuItem->text() == skuToFind)
        {
            found = true;
            // Сбор информации о продукте
            QString name = ui->tableWidget->item(row, 0)->text();
            QString price = ui->tableWidget->item(row, 2)->text();
            QString quantity = ui->tableWidget->item(row, 3)->text();

            double totalPrice = price.toDouble() * quantity.toInt(); // Расчет общей стоимости

            info = "Артикул: " + skuToFind + "\nНазвание: " + name +
                   "\nЦена за единицу: " + price + "\nКоличество: " + quantity +
                   "\nОбщая стоимость: " + QString::number(totalPrice, 'f', 2);
            break;
        }
    }

    if (!found)
    {
        QMessageBox::information(this, "Результат поиска", "Продукт с артикулом '" + skuToFind + "' не найден.");
    }
    else
    {
        QMessageBox::information(this, "Информация о продукте", info);
    }
}

void Product::on_addProduct_clicked()
{
    addProduct();
}


void Product::on_deleteLProduct_clicked()
{
    deleteLProduct();
}


void Product::on_sellProduct_clicked()
{
    sellProduct();
}


void Product::on_calculateTotalBudget_clicked()
{
    calculateTotalBudget();
}


void Product::on_sale_clicked()
{
    TotalSalesSum();
}


void Product::on_Remains_clicked()
{
    getRemainsSales();
}


void Product::on_revizion_clicked()
{
    performRevision();
}


void Product::on_Information_clicked()
{
    displayProductInfo();
}

