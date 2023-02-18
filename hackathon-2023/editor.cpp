#include "editor.h"
#include "ui_editor.h"

Editor::Editor(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Editor)
{
    ui->setupUi(this);
}

Editor::~Editor()
{
    delete ui;
}

void Editor::on_pushButton_clicked()
{
    this->close();      // Закрываем окно
    emit mainWindow();  //сигнал на открытие главного окна
}

