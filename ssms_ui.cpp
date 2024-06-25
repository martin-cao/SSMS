//
// Created by Martin Cao on 2024/06/18.
//

// You may need to build the project (run Qt uic code generator) to get "ui_SSMS_UI.h" resolved

#include "ssms_ui.h"
#include <QMessageBox>
#include <QtPrintSupport/QPrinter>
#include <QtPrintSupport/QPrintDialog>


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

    // Selling tab initialization
    on_button_selling_search_clicked();
    refreshSellingSummary();
}

void SSMS_UI::refreshSellingSummary() {
    QString display = "";
    double totalPrice = 0;

    for (auto& item : transaction.get_itemList()) {
        QString goodName = item.m_good.get_goodName();
//        qDebug() << "Good name: " << goodName;
        int qty = item.m_qty;
        double discount = item.m_good.get_goodDiscount();
        double unitPrice = item.m_unitPrice;
        double itemTotalPrice = item.m_unitPrice * qty;

        display += QString("Name: %1, Qty: %2, Discount: %3, Unit Price: %4\n")
                .arg(goodName)
                .arg(qty)
                .arg(discount)
                .arg(unitPrice);
    }

    totalPrice = transaction.get_totalPrice();
    display += QString("\nTotal Price: %1").arg(totalPrice);

    ui->textBrowser_selling_summary->setText(display);
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
    ui->lineEdit_login_username->clear();
    ui->lineEdit_login_password->clear();
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
    QString term;
    QString keyword = ui->lineEdit_selling_search->text();

    switch (ui->comboBox_selling_searchBy->currentIndex()) {
        case 0:
            term = "good_id";
            break;
        case 1:
            term = "good_name";
            break;
        case 2:
            term = "good_code";
            break;
        case 3:
            term = "good_brand";
            break;
        default:
            QMessageBox::warning(nullptr, "Search error", "\"Search by\" invalid.");
    }

    QSqlTableModel* model = new QSqlTableModel;

    model->setTable("goods");
    model->setFilter(QString("%1 LIKE '%%2%'").arg(term, keyword));
    model->select();

    ui->tableView_selling_search->setModel(model);
    ui->tableView_selling_search->resizeColumnsToContents();
    ui->tableView_selling_search->show();
}

void SSMS_UI::on_tableView_selling_search_clicked(const QModelIndex &index) {
    int row = index.row();

    QModelIndex goodIDIndex = ui->tableView_selling_search->model()->index(row, 0);
    QString goodID = ui->tableView_selling_search->model()->data(goodIDIndex).toString();

    good.select(goodID);

    ui->spinBox_selling_quantity->setValue(1);
}

void SSMS_UI::on_button_selling_add_clicked() {
    int goodQty = ui->spinBox_selling_quantity->value();

    transaction.addItem(good, goodQty);
    transaction.calcTotalPrice();
    refreshSellingSummary();
}

void SSMS_UI::on_button_selling_reset_clicked() {
    transaction.reset();
    refreshSellingSummary();
}

void SSMS_UI::on_button_selling_checkOut_clicked() {
    qDebug() << "on_button_selling_checkOut_clicked() started.";

    if (transaction.get_itemList().empty()) {
        QMessageBox::warning(this, "Checkout Error", "The shopping cart is empty.");
        return;
    }

    QString dateStr = QDateTime::currentDateTime().toString("yyyy/MM/dd hh:mm:ss");

    // Create a new transaction record
    QSqlQuery query;
    query.prepare("INSERT INTO transactions (transaction_time, transaction_uid) VALUES (:transactionTime, :transactionUid)");
    query.bindValue(":transactionTime", dateStr);
    query.bindValue(":transactionUid", user.get_uid());

    qDebug() << "on_button_selling_checkOut_clicked() finished.";
    if (!query.exec()) {
        qDebug() << "Query execution failed: " << query.lastError();
        QSqlDatabase::database().rollback();
        QMessageBox::warning(this, "Checkout Error", "Failed to create a new transaction record.");
        return;
    }

    // Get the generated transaction id
    QVariant transactionID = query.lastInsertId();

    // Create transaction detail records for each item in the shopping cart
    for (auto& item : transaction.get_itemList()) {
        query.prepare("INSERT INTO transaction_details (transaction_id, good_id, good_qty, good_discount, good_unitPrice) VALUES (:transactionId, :goodId, :goodQty, :goodDiscount, :goodUnitPrice)");
        query.bindValue(":transactionId", transactionID);
        query.bindValue(":goodId", item.m_good.get_goodID());
        query.bindValue(":goodQty", item.m_qty);
        query.bindValue(":goodDiscount", item.m_good.get_goodDiscount());
        query.bindValue(":goodUnitPrice", item.m_unitPrice);

        if (!query.exec()) {
            QSqlDatabase::database().rollback();
            QMessageBox::warning(this, "Checkout Error", "Failed to create a new transaction detail record.");
            return;
        }

        // Update the stock quantity of the good
        int newStockQty = item.m_good.get_goodStockQty() - item.m_qty;
        item.m_good.setStock(newStockQty);
    }


    // Print the receipt
    QString printContent = "";
    printContent += "---------- XX Supermarket ----------\n";
    printContent += "Transaction date: " + dateStr + "\n";
    printContent += "Transaction ID: " + transactionID.toString() + "\n";
    printContent += "Operator: " + QString::number(user.get_uid()) + "\n";
    printContent += "--------- Purchase Contents --------\n";

    // Add each item in the shopping cart to the receipt
    for (auto& item : transaction.get_itemList()) {
        printContent += "Good ID: " + item.m_good.get_goodID() + "\n";
        printContent += "Good Name: " + item.m_good.get_goodName() + "\n";
        printContent += "Quantity: " + QString::number(item.m_qty) + "\n";
        printContent += "Unit Price: " + QString::number(item.m_unitPrice) + "\n";
        printContent += "Discount: " + QString::number(item.m_good.get_goodDiscount()) + "\n";
        printContent += "Total Price: " + QString::number(item.m_unitPrice * item.m_qty) + "\n";
        printContent += "------------------------------------\n";
    }

    printContent += "Total Price: " + QString::number(transaction.get_totalPrice()) + "\n";

    printContent += "------------------------------------\n";
    printContent += "Please keep the return and exchange credentials properly.\n";
    printContent += "";

    ui->textBrowser_selling_summary->setText(printContent);

    QPrinter printer;
    QPrintDialog printDialog(&printer, this);

    if (printDialog.exec() == QPrintDialog::Accepted)
        ui->textBrowser_selling_summary->print(&printer);


    // Reset the shopping cart
    ui->textBrowser_selling_summary->clear();
    transaction.reset();

    qDebug() << "on_button_selling_checkOut_clicked() finished.";
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



