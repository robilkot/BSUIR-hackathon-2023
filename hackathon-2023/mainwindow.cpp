#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include <QScreen>
#include "questions.cpp"
#include "filesystem.h"
MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    ui->examButton->setIcon(QIcon(":/icons/checked.png"));
    ui->exitButton->setIcon(QIcon(":/icons/exit.png"));
    ui->editorButton->setIcon(QIcon(":/icons/edit.png"));
    ui->settingsButton->setIcon(QIcon(":/icons/settings.png"));

    ui->logo->setPixmap(QPixmap(":/icons/books.png"));

    this->setFixedSize(QSize(400, 400));
    path= "E:/work/hackathon-2023/hackathon-2023/input.txt";
    read(path);

    choiceWindow = new Choice();
    //соединяю слот открытия главного окна с кнопкой в окне выбора сложности
     connect(choiceWindow,&Choice::mainWindow,this,&MainWindow::show);

    settingsWindow= new Settings();
     //соединяю слот открытия главного окна с кнопкой в окне редактора
    connect(settingsWindow,&Settings::mainWindow,this,&MainWindow::show);
    connect(settingsWindow,&Settings::mainWindow,this,&MainWindow::setPath);

    editorWindow = new Editor();
    //соединяю слот открытия главного окна с кнопкой в окне настроек
    connect(editorWindow,&Editor::mainWindow,this,&MainWindow::show);

    examWindow = new Exam();
    //соединяю слот открытия главного окна с кнопкой в окне экзамена
    connect(examWindow,&Exam::mainWindow,this,&MainWindow::show);
    //соединяю слот открытия окна экзамена с кнопкой в окне сложности
    connect(choiceWindow,&Choice::examWindow,this,&MainWindow::openExamWindow);

    // Когда открывается окно экзамена запускаем его
    connect(choiceWindow, &Choice::examWindow, examWindow, &Exam::startExam);
    //передаю из choice в exam объект test
    connect(choiceWindow,&Choice::updateQueue,this,&MainWindow::updateQueue);
    //connect(editorWindow,&Editor::mainWindow,this,&MainWindow::show);
}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::read(QString path)
{
    FileSystem *system = new FileSystem();
    system->readQuestions(test,path);
    qDebug()<< "size of q " << test.size() << "\n";
    delete system;
}

void MainWindow::on_examButton_clicked()
{
    //choiceWindow->setFixedSize(this->size());//делаем размер окна таким же, как и у основного
    choiceWindow->setQuestions(test);
    choiceWindow->show();  // Показываем окно выбора сложности
    this->close();           // Закрываю главное окно
}

void MainWindow::on_editorButton_clicked()
{
    //editorWindow->setFixedSize(this->size());//делаем размер окна таким же, как и у основного
    editorWindow->setTest(test);
    editorWindow->editorStart();
    editorWindow->show();  // Показываем окно редактора
    this->close();         // Закрываю главное окно
}
void MainWindow::on_settingsButton_clicked()
{
    //settingsWindow->setFixedSize(this->size());//делаем размер окна таким же, как и у основного
    settingsWindow->show();  // Показываем окно настроек
    this->close();           // Закрываю главное окно
}

void MainWindow::on_exitButton_clicked()
{
     QCoreApplication::quit();
}

void MainWindow::openExamWindow()
{
    //examWindow->setFixedSize(this->size());//делаем размер окна таким же, как и у основного
    examWindow->show();  // Показываем окно экзамена
    this->close();           // Закрываю главное окно
}

void MainWindow::updateQueue()
{
    examWindow->setQuestionsQueue(choiceWindow->getTest());
}

void MainWindow::setPath()
{
path= settingsWindow->getPath();
test.clear();
read(path);
}




