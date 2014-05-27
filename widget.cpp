#include "widget.h"
#include "ui_widget.h"

Widget::Widget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Widget)
{
    ui->setupUi(this);
    count = 1;
    state = 0;
    this->initDevice();
}

Widget::~Widget()
{
    delete ui;
    FT_Close(ftHandle);
}

void Widget::initDevice()
{
    wchar_t name[] = L"MD212rev1 #2";
    ui->textEdit->append("<font color = \"blue\">Поиск устройства MD212rev1 #2...</font>");

   ftStatus = FT_ListDevices(0, name, FT_LIST_BY_INDEX | FT_OPEN_BY_DESCRIPTION);
   if(ftStatus != FT_OK)
   {
       ui->textEdit->append("<font color = \"red\">Устройство не найдено!</font>");
       ui->pushButton->setEnabled(false);
       return;
   }
   ui->textEdit->append("Устройство найдено");
   ftHandle = FT_W32_CreateFile(name, GENERIC_WRITE, 0, 0, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL | FT_OPEN_BY_DESCRIPTION, 0);
   if(ftHandle == INVALID_HANDLE_VALUE)
       ui->textEdit->append(tr("<font color = \"red\">Ошибка при открытии устройства: ") + FT_W32_GetLastError(ftHandle));
   else ui->textEdit->append(tr("<font color = \"green\">Готово</font>"));
}

void Widget::on_pushButton_clicked()
{
    data = ui->spinBox->text();
    DWORD dataWrited;
    char d = data.toUtf8().toInt(0, 16);

    ftStatus = FT_W32_WriteFile(ftHandle, &d, sizeof(d), &dataWrited, NULL);
    ftStatus = FT_W32_WriteFile(ftHandle, &d, sizeof(d), &dataWrited, NULL);
    ftStatus = FT_W32_WriteFile(ftHandle, &d, sizeof(d), &dataWrited, NULL);
    ftStatus = FT_W32_WriteFile(ftHandle, &d, sizeof(d), &dataWrited, NULL);
    ftStatus = FT_W32_WriteFile(ftHandle, &d, sizeof(d), &dataWrited, NULL);
    if(ftStatus != 0)
        ui->textEdit->append(tr("Значение успешно передано: ") + data);
    else ui->textEdit->append(tr("<font color = \"red\">Произошла ошибка во время передачи значнеия: ") + FT_W32_GetLastError(ftHandle));
}

//void Widget::on_lineEdit_returnPressed()
//{
//    this->on_pushButton_clicked();
//}

void Widget::on_spinBox_editingFinished()
{
    this->on_pushButton_clicked();
}
