//
// Created by Martin Cao on 2024/06/21.
//

#include "User.h"

#include <iostream>

namespace SSMS {

    // Constructor
    User::User() {
        std::cout << "[SSMS_SYSTEM] class User member constructed" << std::endl;
    }

    // Inquiring functions
    QString User::get_userName() {
        return m_userName;
    }

    int User::get_userRole_int() {
        return m_userRole;
    }

    QString User::get_userRole_str() {
        switch (m_userRole) {
            case 1:
                return "admin";
            case 2:
                return "manager";
            case 3:
                return "staff";
            default:
                return "unknown";
        }
    }

    int User::get_uid() {
        return m_uid;
    }

    // Operating function
    int User::login(QString f_username, QString f_pwd) {
        // Generate the SHA256 hash of the password
        QByteArray pwdHash = QCryptographicHash::hash(f_pwd.toUtf8(), QCryptographicHash::Sha256).toHex();
        QString pwdHashStr = QString::fromUtf8(pwdHash);

        QSqlQuery query;
        query.prepare("SELECT * FROM users WHERE user_name = :userName AND user_pwd = :pwd");
        query.bindValue(":userName", f_username);
        query.bindValue(":pwd", pwdHashStr);

        // Debug output before executing the query
        qDebug() << "[SSMS_SYSTEM_DB] Preparing to execute query";
        qDebug() << "Username: " << f_username;
        qDebug() << "Password hash: " << pwdHashStr;

        if (!query.exec()) {
            // Debug output if the query execution fails
            qDebug() << "[SSMS_SYSTEM_DB] Query execution failed";
            qDebug() << "Query error: " << query.lastError().text();
            return 401;
        }

        if (query.next()) {
            m_userName = query.value("user_name").toString();
            m_userRole = query.value("user_role").toInt();
            m_uid = query.value("user_uid").toInt();
            qDebug() << "[SSMS_SYSTEM_LOGIN] Logged in";
            return 200;
        }
        qDebug() << "[SSMS_SYSTEM_LOGIN] Log in failed";
        return 401;
    }

    void User::logOut() {
        m_userName = "";
        m_userRole = 0;
        m_uid = 0;
    }


} // SSMS