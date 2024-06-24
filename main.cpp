//
// Created by Martin Cao on 2024/06/18.
//

#include "ssms_ui.h"

#include <QApplication>
#include <QtSql/QSqlDatabase>


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
    db.open();

    SSMS_UI window;
    window.show();

    return QApplication::exec();
}
