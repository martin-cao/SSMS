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

};


#endif //SSMS_SSMS_UI_H
