//
// Created by Martin Cao on 2024/06/20.
//

#include "Goods.h"

#include <iostream>

namespace SSMS {

    // Constructor
    Goods::Goods() {
        m_SSMS_isSelected = false;
        std::cout << "[SSMS_SYSTEM] class Goods member constructed" << std::endl;
    }

    // region Inquiring functions
    QString Goods::get_goodID() {
        return m_goodID;
    }

    QString Goods::get_goodName() {
        return m_goodName;
    }

    Goods::goodType Goods::get_goodType() {
        return m_goodType;
    }

    QString Goods::get_goodBrand() {
        return m_goodBrand;
    }

    QString Goods::get_goodCode() {
        return m_goodCode;
    }

    int Goods::get_goodStockQty() {
        return m_goodStockQty;
    }

    double Goods::get_goodPurchasePrice() {
        return m_goodPurchasePrice;
    }

    double Goods::get_goodSellingPrice() {
        return m_goodSellingPrice;
    }

    double Goods::get_goodDiscount() {
        return m_goodDiscount;
    }

    Goods::goodStatus Goods::get_goodStatus() {
        return m_goodStatus;
    }

    bool Goods::get_goodIsOnSale() {
        return m_goodIsOnSale;
    }

    QString Goods::get_goodDescription() {
        return m_goodDescription;
    }


    bool Goods::isStockEnough(int f_qty, bool f_msg) {
        if (m_goodStockQty >= f_qty)
            return true;

        if (f_msg)
            QMessageBox::warning(nullptr, "Out of stock", "Current stock: " + QString::number(m_goodStockQty) + ", stock is insufficient!");

        return false;
    }

    bool Goods::isCoveredAfterDiscount(double f_discount, bool f_msg) {
        if (m_goodSellingPrice * (1 - m_goodDiscount) >= m_goodPurchasePrice)
            return true;

        if (f_msg)
            QMessageBox::warning(nullptr, "Discount too high", "The actual price after discount is lower than the purchase price, please reset the discount!");

        return false;
    }
    /* TODO 允许结账时主动设置折扣，并且允许override该提示 */

    bool Goods::isSelected(bool f_msg) {
        if (m_SSMS_isSelected)
            return true;

        if (f_msg)
            QMessageBox::warning(nullptr, "No goods selected", "Please select a product first.");

        return false;
    }

    // endregion

    // region Operating functions
    void Goods::select(QString f_id) {
        QSqlQuery query;
        query.prepare("SELECT * FROM goods WHERE good_id = :goodID");
        query.bindValue(":goodID", m_goodID);
        query.exec();

        if (query.next())
            m_SSMS_isSelected = true;

        m_goodID = query.value("good_id").toString();
        m_goodName = query.value("good_name").toString();
        QMetaEnum metaEnum_goodType = QMetaEnum::fromType<Goods::goodType>();
        m_goodType = static_cast<Goods::goodType>(metaEnum_goodType.keyToValue(query.value("good_type").toString().toStdString().c_str()));
        m_goodBrand = query.value("good_brand").toString();
        m_goodCode = query.value("good_code").toString();
        m_goodStockQty = query.value("good_stock_qty").toInt();
        m_goodPurchasePrice = query.value("good_purcahse_price").toDouble();
        m_goodSellingPrice = query.value("good_selling_price").toDouble();
        m_goodDiscount = query.value("good_discount").toDouble();
        QMetaEnum metaEnum__goodStatus = QMetaEnum::fromType<SSMS::Goods::goodStatus>();
        m_goodStatus = static_cast<Goods::goodStatus>(metaEnum__goodStatus.keyToValue(query.value("good_status").toString().toStdString().c_str()));
        m_goodIsOnSale = query.value("good_is_on_sale").toBool();
        m_goodDescription = query.value("good_description").toString();
    }

    void Goods::unselect() {
        m_SSMS_isSelected = false;
    }

    void Goods::setStock(int f_stock) {
        m_goodStockQty = f_stock;
        QSqlQuery query;
        query.prepare("UPDATE goods SET good_stock_qty = :goodStockQty WHERE good_id = :goodID");
        query.bindValue(":goodStockQty", m_goodStockQty);
        query.bindValue(":goodID", m_goodID);
        query.exec();
    }
    // endregion

} // SSMS