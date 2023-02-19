#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include <QScreen>
MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    difficultyWindow = new Difficulty();
    //соединяю слот открытия главного окна с кнопкой в окне выбора сложности
   connect(difficultyWindow,&Difficulty::mainWindow,this,&MainWindow::show);

    settingsWindow= new Settings();
     //соединяю слот открытия главного окна с кнопкой в окне редактора
    connect(settingsWindow,&Settings::mainWindow,this,&MainWindow::show);

    editorWindow = new Editor();
    //соединяю слот открытия главного окна с кнопкой в окне настроек
    connect(editorWindow,&Editor::mainWindow,this,&MainWindow::show);

    examWindow = new Exam();
    //соединяю слот открытия главного окна с кнопкой в окне экзамена
    connect(examWindow,&Exam::mainWindow,this,&MainWindow::show);
    //соединяю слот открытия окна экзамена с кнопкой в окне сложности
    connect(difficultyWindow,&Difficulty::examWindow,this,&MainWindow::openExamWindow);

}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_pushButton_clicked()
{
    difficultyWindow->setFixedSize(this->size());//делаем размер окна таким же, как и у основного
    difficultyWindow->show();  // Показываем окно выбора сложности
    this->close();           // Закрываю главное окно
}

void MainWindow::on_pushButton_2_clicked()
{
    editorWindow->setFixedSize(this->size());//делаем размер окна таким же, как и у основного
    editorWindow->show();  // Показываем окно редактора
    this->close();         // Закрываю главное окно
}
void MainWindow::on_pushButton_3_clicked()
{
    settingsWindow->setFixedSize(this->size());//делаем размер окна таким же, как и у основного
    settingsWindow->show();  // Показываем окно настроек
    this->close();           // Закрываю главное окно
}

void MainWindow::on_pushButton_4_clicked()
{
     QCoreApplication::quit();
}

void MainWindow::openExamWindow()
{
    examWindow->setFixedSize(this->size());//делаем размер окна таким же, как и у основного
    examWindow->show();  // Показываем окно экзамена
    this->close();           // Закрываю главное окно
}




