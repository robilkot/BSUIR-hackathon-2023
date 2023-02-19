#include "choice.h"
#include "ui_choice.h"

Choice::Choice(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Choice)
{
    ui->setupUi(this);
}

Choice::~Choice()
{
    delete ui;
}

void Choice::on_pushButton_clicked()
{
    this->close();      // Закрываем окно
    emit mainWindow();  //сигнал на открытие главного окна
}


void Choice::on_pushButton_5_clicked()
{
    this->close();      // Закрываем окно
    emit examWindow();  //сигнал на открытие окна экзамена
}

