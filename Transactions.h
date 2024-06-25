//
// Created by Martin Cao on 2024/06/24.
//

#ifndef SSMS_TRANSACTIONS_H
#define SSMS_TRANSACTIONS_H

#pragma once

#include "Goods.h"

#include <QApplication>

#include <QtSql/QSqlDatabase>
#include <QtSql/QSqlError>
#include <QtSql/QSqlQuery>
#include <QSqlQueryModel>

#include <QDate>
#include <QSqlTableModel>
#include <QTableView>

#include <QMessageBox>

#include <QDebug>

namespace SSMS {

    struct TransactionItem {
        Goods m_good;
        int m_qty;
        double m_unitPrice;

        TransactionItem(const Goods& f_good, int f_qty) : m_good(f_good), m_qty(f_qty), m_unitPrice(m_good.get_goodSellingPrice() * (1 - m_good.get_goodDiscount())) {}
    };

    class Transactions {
    private:
        // Parameters
        std::vector<TransactionItem> m_itemList;
        QDateTime m_transactionTime;
        double m_totalPrice;

        // SSMS Parameter
        bool m_SSMS_isSelected;

    public:
        // Constructor
        Transactions(const QDateTime& f_transactionTime) : m_transactionTime(f_transactionTime), m_totalPrice(0), m_SSMS_isSelected(false) {}

        // Inquiring functions
        std::vector<TransactionItem> get_itemList();
        QDateTime get_transactionTime();
        double get_totalPrice();
        bool isSelected(bool f_msg = true);

        // Operationg functions
        void addItem(Goods f_good, int f_qty);
        void removeItem(std::string f_goodID);
        void modifyQty(std::string f_goodID, int f_qty);
        void calcTotalPrice();

        // System functions
        void reset();
        void select(int f_transaction_id);
        void unselect();
    };

} // SSMS

#endif //SSMS_TRANSACTIONS_H
