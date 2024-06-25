//
// Created by Martin Cao on 2024/06/20.
//

#ifndef SSMS_GOODS_H
#define SSMS_GOODS_H

#pragma once

#include <QApplication>

#include <QtSql/QSqlDatabase>
#include <QtSql/QSqlError>
#include <QtSql/QSqlQuery>
#include <QSqlQueryModel>

#include <QDate>
#include <QSqlTableModel>
#include <QTableView>
#include <QMessageBox>

#include <QMetaEnum>

#include <QDebug>

namespace SSMS {

    class Goods {
        Q_GADGET

    public:
        // region Enumeration - goodType & goodStatus

        // goodType - types of goods
        enum goodType {
            food,
            beverage,
            dailyUse,
            makeups
        };
        Q_ENUM(goodType)

        enum goodStatus {
            available,
            unavailable,
            outOfStock, // 缺货
            discontinued // 停产
        };
        Q_ENUM(goodStatus)
        // endregion

    private:
        // region Parameters

        // Basic parameters
        QString m_goodID;
        QString m_goodName;
        goodType m_goodType;
        QString m_goodBrand;
        QString m_goodCode;

        // Stock and selling parameters
        int m_goodStockQty;
        double m_goodPurchasePrice;
        double m_goodSellingPrice;
        double m_goodDiscount;

        // Status parameters
        goodStatus m_goodStatus;
        bool m_goodIsOnSale;

        // Other parameters
        QString m_goodDescription;

        // SSMS parameters
        bool m_SSMS_isSelected;

        // endregion

    public:
        // region Member Functions

        // Constructor
        Goods();
        Goods(const Goods& other);

        // Inquiring functions
        QString get_goodID();
        QString get_goodName();
        goodType get_goodType();
        QString get_goodBrand();
        QString get_goodCode();
        int get_goodStockQty();
        double get_goodPurchasePrice();
        double get_goodSellingPrice();
        double get_goodDiscount();
        goodStatus get_goodStatus();
        bool get_goodIsOnSale();
        QString get_goodDescription();

        bool isStockEnough(int f_qty, bool f_msg = true);
        bool isCoveredAfterDiscount(double f_discount, bool f_msg = true);

        bool isSelected(bool f_msg = true);

        // Operating functions
        void select(QString f_id);
        void unselect();

        void setStock(int f_stock);
        // endregion
    };

} // SSMS

#endif //SSMS_GOODS_H
