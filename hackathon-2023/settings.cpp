#include "settings.h"
#include "ui_settings.h"

Settings::Settings(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Settings)
{
    ui->setupUi(this);

    ui->menuButton->setIcon(QIcon(":/icons/notebook.png"));
    this->setFixedSize(this->width(), this->height());
}

Settings::~Settings()
{
    delete ui;
}

void Settings::on_menuButton_clicked()
{
    this->close();      // Закрываем окно
    emit mainWindow();  // Сигнал на открытие главного окна
}


void Settings::on_pathEdit_textChanged(const QString &arg1)
{
    path=arg1;
}

QString Settings::getPath() const
{
    return path;
}

void Settings::setPath(const QString &newPath)
{
    path = newPath;
}

