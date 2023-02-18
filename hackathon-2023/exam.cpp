#include "exam.h"
#include "ui_exam.h"

Exam::Exam(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Exam)
{
    ui->setupUi(this);
}

Exam::~Exam()
{
    delete ui;
}

void Exam::on_pushButton_5_clicked()
{
    this->close();      // Закрываем окно
    emit mainWindow();  //сигнал на открытие главного окна
}

