//
// Created by Martin Cao on 2024/06/24.
//

#include "Transactions.h"

namespace SSMS {

    // region Inquiring functions
    std::vector<TransactionItem> Transactions::get_itemList() {
        return m_itemList;
    }

    QDateTime Transactions::get_transactionTime() {
        return m_transactionTime;
    }

    double Transactions::get_totalPrice() {
        return m_totalPrice;
    }

    bool Transactions::isSelected(bool f_msg) {
        if (m_SSMS_isSelected)
            return true;

        if (f_msg)
            QMessageBox::warning(nullptr, "No transaction selected", "Please select a transaction first.");

        return false;
    }
    //endregion

    // region Operating functions
    void Transactions::addItem(Goods &f_good, int f_qty) {
        m_itemList.emplace_back(f_good, f_qty);
//        m_totalPrice += f_good.get_goodSellingPrice() * (1 - f_good.get_goodDiscount()) * f_qty;
    }

    void Transactions::removeItem(std::string f_goodID) {
        for (auto item = m_itemList.begin(); item != m_itemList.end(); ++item) {
            if (item->m_good.get_goodID().toStdString() == f_goodID) {
                m_itemList.erase(item);
                break;
            }
        }
    }

    void Transactions::modifyQty(std::string f_goodID, int f_qty) {
        for (auto& item : m_itemList) {
            if (item.m_good.get_goodID().toStdString() == f_goodID) {
                item.m_qty = f_qty;
                break;
            }
        }
    }

    void Transactions::calcTotalPrice() {
        m_totalPrice = 0;
        for (auto& item : m_itemList) {
            m_totalPrice += item.m_unitPrice * (1 - item.m_good.get_goodDiscount()) * item.m_qty;
        }
    }
    // endregion

    // region System functions
    void Transactions::reset() {
        m_itemList.clear();
        m_totalPrice = 0;
        m_transactionTime = QDateTime();
        m_SSMS_isSelected = false;
        qDebug() << "[SSMS_SYSTEM] Transaction reset";
    }

    void Transactions::select(int f_transaction_id) {
        QSqlQuery query;
        query.prepare("SELECT * FROM transactions WHERE transaction_id = :transactionID");
        query.bindValue(":transactionID", f_transaction_id);
        query.exec();

        if (query.next()) {
            // Clear the current transaction
            reset();

            // Get the transaction details from the database
            m_transactionTime = query.value("transaction_time").toDateTime();

            // Get the transaction items from the database
            QSqlQuery itemQuery;
            itemQuery.prepare("SELECT * FROM transaction_details WHERE transaction_id = :transactionID");
            itemQuery.bindValue(":transactionID", f_transaction_id);
            itemQuery.exec();

            while (itemQuery.next()) {
                Goods good;
                good.select(itemQuery.value("good_id").toString());
                int qty = itemQuery.value("good_qty").toInt();
                addItem(good, qty);
            }

            // Calculate the total price after all items are added
            calcTotalPrice();
        }
    }

    void Transactions::unselect() {
        reset();
    }
    // endregion

} // SSMS