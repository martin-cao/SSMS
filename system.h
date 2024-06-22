//
// Created by Martin Cao on 2024/06/23.
//

#ifndef SSMS_SYSTEM_H
#define SSMS_SYSTEM_H

#pragma once

#include "User.h"
#include "Goods.h"

#include <QApplication>
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QSqlError>
#include <QSqlQueryModel>
#include <QDate>
#include <QSqlTableModel>
#include <QTableView>
#include <QtPrintSupport/QPrinter>
#include <QtPrintSupport/QPrintDialog>
#include <QMessageBox>
#include <QDateTime>

extern SSMS::User user;
extern SSMS::Goods good;


#endif //SSMS_SYSTEM_H
