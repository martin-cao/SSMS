//
// Created by Martin Cao on 2024/06/18.
//

#include "config.h"
#include "ssms_ui.h"

#include <QApplication>
#include <QtSql/QSqlDatabase>
#include <QFile>
#include <QDir>


int main(int argc, char *argv[]) {
    QApplication a(argc, argv);

    QSqlDatabase db = QSqlDatabase::addDatabase("QSQLITE");

    // Get the Applicatoin Support (macOS) / AppData (Windows) directory
    QString supportDir = QStandardPaths::writableLocation(QStandardPaths::AppDataLocation);

    // Create the directory if not exist
    QDir dir(supportDir);
    if (!dir.exists())
        dir.mkpath(".");

    // Set the database file path
    QString dbPath = supportDir + "/data.db";
    db.setDatabaseName(dbPath);

    // Copy the database file from the resource to the AppDataLocation directory
//    if (!QFile::exists(dbPath)) {
//        QFile::copy(":/data.db", dbPath);
//        QFile::setPermissions(dbPath, QFile::ReadUser | QFile::WriteUser);
//    }

    if (!QFile::exists(dbPath) || resetDB) {
        QFile file(":/data.db");
        qDebug() << "Resource file path: " << QFileInfo(file).absoluteFilePath();

        if (resetDB && QFile::exists(dbPath)) {
            // If resetDB is true and the target file exists, remove the target file first
            QFile::remove(dbPath);
        }

        if (!file.copy(dbPath)) {
            qDebug() << "Failed to copy database file: " << file.errorString();
        } else if (!file.setPermissions(QFile::ReadUser | QFile::WriteUser)) {
            qDebug() << "Failed to set permissions: " << file.errorString();
        } else {
            qDebug() << "Copy succeed";
        }
    }

    db.open();

    Q_INIT_RESOURCE(data);  // Initialize the resource

    SSMS_UI window;
    window.show();
    window.startUp();

    return QApplication::exec();
}
