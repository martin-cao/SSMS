//
// Created by Martin Cao on 2024/06/18.
//

#ifndef SSMS_SSMS_UI_H
#define SSMS_SSMS_UI_H

#pragma once

#include "system.h"
#include "ui_ssms_ui.h"

#include <QMainWindow>



QT_BEGIN_NAMESPACE
namespace Ui { class SSMS_UI; }
QT_END_NAMESPACE

class SSMS_UI : public QMainWindow {
Q_OBJECT

public:
    // Constructor and Destructor
    explicit SSMS_UI(QWidget *parent = nullptr);

    ~SSMS_UI() override;

    // region System Ui functions
    void startUp();
//        void showPath();
    void refreshSellingSummary();

private:
    void refreshAccountsTable();
    // endregion

private:
    Ui::SSMS_UI *ui;

    QSqlTableModel *queryTable = new QSqlTableModel;

private slots:
    // Slots

// Login and Log out
    /*
    lineEdit_login_username
    lineEdit_login_password
    */
    void on_button_login_clicked();
    void on_button_logOut_clicked();

    // Main view

    // Reset transaction instance
    void on_tabWidget_currentChanged();

    // Selling tab
    /*
    comboBox_selling_searchBy
    lineEdit_selling_search
    tableView_selling_search

    spinBox_selling_quantity
    textBrowser_selling_summary
    */

    void on_button_selling_search_clicked();
    void on_tableView_selling_search_clicked(const QModelIndex& index);
    void on_button_selling_add_clicked();
    void on_button_selling_reset_clicked();
    void on_button_selling_checkOut_clicked();

    // Stock tab
    /*
    comboBox_stock_searchBy
    lineEdit_stock_search
    tableView_stock_search

    lineEdit_stock_add_id
    lineEdit_stock_add_name
    comboBox_stock_add_type
    lineEdit_stock_add_brand
    comboBox_stock_add_specs
    lineEdit_stock_add_code
    */
    void on_button_stock_search_clicked();
    void on_button_stock_add_add_clicked();
    void on_button_stock_edit_confirm_clicked();
    void on_button_stock_delete_delete_clicked();

    // Refund tab
    /*
    calendar_refund_date
    tableView_refund_transactions
    lineEdit_refund_transactionID
    checkBox_refund_manualInput
    tableView_refund_transactionDetail

    */
    void on_calendar_refund_date_selectionChanged();
    void on_tableView_refund_transactions_clicked(const QModelIndex& index);
    void on_lineEdit_refund_transactionID_textChanged();
    void on_checkBox_refund_manualInput_stateChanged();
    void on_button_refund_search_clicked();
    void on_button_refund_refund_clicked();

    // Stats tab
    /*
    comboBox_stats_statisticsBy
    tableView_stats_table
    */
    void on_comboBox_stats_statisticsBy_currentIndexChanged();

    // User tab
    void on_button_user_switchToPersonalMode_clicked();
    void on_button_user_switchToAdminMode_clicked();

};


#endif //SSMS_SSMS_UI_H
