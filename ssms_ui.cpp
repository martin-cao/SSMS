//
// Created by Martin Cao on 2024/06/18.
//

// You may need to build the project (run Qt uic code generator) to get "ui_SSMS_UI.h" resolved

#include "ssms_ui.h"
#include <QMessageBox>

// Constructor and Deconstructor
SSMS_UI::SSMS_UI(QWidget *parent) :
        QMainWindow(parent), ui(new Ui::SSMS_UI) {
    ui->setupUi(this);
    startUp();
}

SSMS_UI::~SSMS_UI() {
    delete ui;
}

// region System Ui functions
void SSMS_UI::startUp() {
    ui->stackedWidget_main->setCurrentIndex(1);
    ui->tabWidget->setCurrentIndex(0);
    // on_slots_done()...
    refreshSellingSummary();
}

void SSMS_UI::refreshSellingSummary() {
    // 更新结账小结 to-be-done
}

void SSMS_UI::refreshAccountsTable() {
    // 更新账户列表 to-be-done
}
// endregion

// Slot functions

// Login and Log out
void SSMS_UI::on_button_login_clicked() {
    QString username = ui->lineEdit_login_username->text();
    QString password = ui->lineEdit_login_password->text();
    int status = user.login(username, password);

    if (status == 200) {
        ui->label_system_currentUser->setText(user.get_userName());
        QMessageBox::information(nullptr, "Log in succeed", "Welcome, [" + user.get_userRole_str() + "] " + user.get_userName() + ".");
        ui->stackedWidget_main->setCurrentIndex(0);
    } else {
        QMessageBox::warning(nullptr, "Log in failed", "Username or password is incorrect.");
    }
}

void SSMS_UI::on_button_logOut_clicked() {
    ui->stackedWidget_main->setCurrentIndex(1);
}

// Main view

// Reset transaction instance
void SSMS_UI::on_tabWidget_currentChanged() {
    switch (ui->tabWidget->currentIndex()) {
        case 0:
            qDebug() << "[SSMS_SYSTEM_VIEW] Turned to tab Selling";
            transaction.reset();
            break;
        case 1:
            qDebug() << "[SSMS_SYSTEM_VIEW] Turned to tab Stock";
            break;
        case 2:
            qDebug() << "[SSMS_SYSTEM_VIEW] Turned to tab Refund";
            transaction.reset();
            break;
        case 3:
            qDebug() << "[SSMS_SYSTEM_VIEW] Turned to tab Stats";
            break;
        case 4:
            qDebug() << "[SSMS_SYSTEM_VIEW] Turned to tab User";
            break;
        default:
            break;
    }
}

// region Selling tab
/*
comboBox_selling_searchBy
lineEdit_selling_search
tableView_selling_search

spinBox_selling_quantity
textBrowser_selling_summary
*/

void SSMS_UI::on_button_selling_search_clicked() {

}

void SSMS_UI::on_button_selling_add_clicked() {

}

void SSMS_UI::on_button_selling_checkOut_clicked() {

}
// endregion

// region Stock tab
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
void SSMS_UI::on_button_stock_search_clicked() {

}

void SSMS_UI::on_button_stock_add_add_clicked() {

}

void SSMS_UI::on_button_stock_edit_confirm_clicked() {

}

void SSMS_UI::on_button_stock_delete_delete_clicked() {

}
// endregion

// region Refund tab
/*
calendar_refund_date
tableView_refund_transactions
lineEdit_refund_transactionID
checkBox_refund_manualInput
tableView_refund_transactionDetail

*/
void SSMS_UI::on_button_refund_search_clicked() {

}

void SSMS_UI::on_button_refund_refund_clicked() {

}
// endregion

// region Stats tab
/*
comboBox_stats_statisticsBy
tableView_stats_table
*/
void SSMS_UI::on_comboBox_stats_statisticsBy_currentIndexChanged() {

}
// endregion

// region User tab
void SSMS_UI::on_button_user_switchToPersonalMode_clicked() {
    ui->stackedWidget_user->setCurrentIndex(1);
}

void SSMS_UI::on_button_user_switchToAdminMode_clicked() {
    ui->stackedWidget_user->setCurrentIndex(0);
}
// endregion



