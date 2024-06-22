//
// Created by Martin Cao on 2024/06/21.
//

#ifndef SSMS_USER_H
#define SSMS_USER_H

#pragma once

#include <QApplication>

#include <QtSql/QSqlDatabase>
#include <QtSql/QSqlError>
#include <QtSql/QSqlQuery>
#include <QSqlQueryModel>

#include <QDate>
#include <QSqlTableModel>
#include <QTableView>

#include <QDebug>

namespace SSMS {

    class User {
    private:
        QString m_userName;
        int m_userRole;
        int m_uid;
        /* userRole
         * 1 - admin
         * 2 - manager
         * 3 - staff
         */

    public:
        // Constructor
        User();

        // Inquiring functions
        QString get_userName();
        int get_userRole_int();
        QString get_userRole_str();
        int get_uid();


        // Operating function
        int login(QString f_username, QString f_pwd);

    };

} // SSMS

#endif //SSMS_USER_H
