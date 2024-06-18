//
// Created by Martin Cao on 2024/06/18.
//

#ifndef SSMS_SSMS_UI_H
#define SSMS_SSMS_UI_H

#include <QMainWindow>


QT_BEGIN_NAMESPACE
namespace Ui { class SSMS_UI; }
QT_END_NAMESPACE

class SSMS_UI : public QMainWindow {
Q_OBJECT

public:
    explicit SSMS_UI(QWidget *parent = nullptr);

    ~SSMS_UI() override;

private:
    Ui::SSMS_UI *ui;

public slots:
    static void on_selling_searchButton_clicked();
};


#endif //SSMS_SSMS_UI_H
