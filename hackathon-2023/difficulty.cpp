#include "difficulty.h"
#include "ui_difficulty.h"

Difficulty::Difficulty(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Difficulty)
{
    ui->setupUi(this);
}

Difficulty::~Difficulty()
{
    delete ui;
}

void Difficulty::on_pushButton_clicked()
{
    this->close();      // Закрываем окно
    emit mainWindow();  //сигнал на открытие главного окна
}


void Difficulty::on_pushButton_5_clicked()
{
    this->close();      // Закрываем окно
    emit examWindow();  //сигнал на открытие окна экзамена
}

