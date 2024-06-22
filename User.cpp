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
        QSqlQuery query;
        query.prepare("SELECT * FROM users WHERE user_name = :userName AND user_pwd = :pwd"); // TODO 密码 + SHA256
        query.bindValue(":userName", f_username);
        query.bindValue(":pwd", f_pwd);
        query.exec();

        if (query.next()) {
            m_userName = query.value("user_name").toString();
            m_userRole = query.value("user_role").toInt();
            m_uid = query.value("user_uid").toInt();
            return 200;
        }
        return 401;
    }


} // SSMS