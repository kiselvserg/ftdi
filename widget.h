#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include <QDebug>
#include <QTimer>
#include "./inc/ftd2xx.h"
#include <windows.h>

namespace Ui {
class Widget;
}

class Widget : public QWidget
{
    Q_OBJECT

public:
    explicit Widget(QWidget *parent = 0);
    ~Widget();

private slots:
    void on_pushButton_clicked();
    void on_lineEdit_returnPressed();
    void timerTO();
    void on_pushButton_2_clicked();

private:
    Ui::Widget *ui;
    FT_HANDLE ftHandle;
    FT_STATUS ftStatus;
    QString data;
    QTimer *timer;
    char count;
    bool state;
    void initDevice();
};

#endif // WIDGET_H
