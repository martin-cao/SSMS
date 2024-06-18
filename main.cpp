//
// Created by Martin Cao on 2024/06/18.
//

#include <QApplication>
#include "ssms_ui.h"

int main(int argc, char *argv[]) {
    QApplication a(argc, argv);

    SSMS_UI w;
    w.show();

    return QApplication::exec();
}
