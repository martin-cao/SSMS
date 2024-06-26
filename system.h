//
// Created by Martin Cao on 2024/06/23.
//

#ifndef SSMS_SYSTEM_H
#define SSMS_SYSTEM_H

#pragma once

#include "User.h"
#include "Goods.h"
#include "Transactions.h"

#include <QApplication>
#include <QStandardPaths>

#include <QDate>
#include <QDir>
#include <QDateTime>

#include <QSqlDatabase>
#include <QSqlQuery>
#include <QSqlError>
#include <QSqlQueryModel>
#include <QSqlTableModel>

#include <QtPrintSupport/QPrinter>
#include <QtPrintSupport/QPrintDialog>

#include <QTableView>
#include <QMessageBox>

#include <QCryptographicHash>

#include <QDebug>


extern SSMS::User user;
extern SSMS::Goods good;
extern SSMS::Transactions transaction;


#endif //SSMS_SYSTEM_H
