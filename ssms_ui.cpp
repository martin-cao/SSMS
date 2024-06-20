//
// Created by Martin Cao on 2024/06/18.
//

// You may need to build the project (run Qt uic code generator) to get "ui_SSMS_UI.h" resolved

#include "ssms_ui.h"
#include "ui_ssms_ui.h"
#include <QMessageBox>

SSMS_UI::SSMS_UI(QWidget *parent) :
        QMainWindow(parent), ui(new Ui::SSMS_UI) {
    ui->setupUi(this);
}

SSMS_UI::~SSMS_UI() {
    delete ui;
}


