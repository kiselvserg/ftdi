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
    ui->textEdit->append("Searching for device MD212rev1 #2");

   ftStatus = FT_ListDevices(0, name, FT_LIST_BY_INDEX | FT_OPEN_BY_DESCRIPTION);
   if(ftStatus != FT_OK)
   {
       ui->textEdit->append("Device not found!");
       ui->pushButton->setEnabled(false);
       return;
   }
   ui->textEdit->append("Device is found");
   ftHandle = FT_W32_CreateFile(name, GENERIC_WRITE, 0, 0, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL | FT_OPEN_BY_DESCRIPTION, 0);
   if(ftHandle == INVALID_HANDLE_VALUE)
       ui->textEdit->append(tr("Error while open device: ") + FT_W32_GetLastError(ftHandle));
   else ui->textEdit->append(tr("Ready for write data"));
}

void Widget::on_pushButton_clicked()
{
    data = ui->spinBox->text();
    DWORD dataWrited;
    char d = data.toUtf8().toInt(0, 16);

    ftStatus = FT_W32_WriteFile(ftHandle, &d, sizeof(d), &dataWrited, NULL);
    if(ftStatus != 0)
        ui->textEdit->append(tr("Data is succesfully written: ") + data);
    else ui->textEdit->append(tr("Something gone wrong while writing data: ") + data);
    ui->spinBox->clear();
}

void Widget::on_lineEdit_returnPressed()
{
    this->on_pushButton_clicked();
}
