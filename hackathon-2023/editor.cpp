#include "editor.h"
#include "ui_editor.h"

Editor::Editor(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Editor)
{
    ui->setupUi(this);

    QuestionVector = new vector<questionStruct>;//вектор для хранения списака вопросов

    ui->comboBox->addItem("Test");
    ui->comboBox->addItem("Open");

    ui->tableWidget->setColumnCount(2);

    connect(this,&Editor::addQ,this,&Editor::updateTable);//подключил расширение таблицы к нажатию кнопки добавления эл-та
    connect(this,&Editor::deleteQ,this,&Editor::updateTable);//подключил уменьшение таблицы к нажатию кнопки удаления эл-та
}

Editor::~Editor()
{
    delete ui;
}

void Editor::on_exitButton_clicked()
{
    this->close();      // Закрываем окно
    emit mainWindow();  //сигнал на открытие главного окна
}

void Editor::on_addQButton_clicked()
{
    questionStruct *a= new questionStruct();
    QuestionVector->push_back(*a);
    emit addQ();
}
void Editor::on_deleteQButon_clicked()
{
    if(!QuestionVector->empty())
    {
     QuestionVector->pop_back();
    }
    emit deleteQ();
}

void Editor::updateTable()
{
    ui->tableWidget->setRowCount(QuestionVector->size());
    for(int i=0;i<QuestionVector->size();i++)
    {
        QTableWidgetItem* temp;
        QTableWidgetItem* temp1;
        if(!QuestionVector->at(i).type)//если testQuestion
        {
            TestQuestion *q =QuestionVector->at(i).a;
            temp = new QTableWidgetItem(q->task.first);
        }
        else
        {
            OpenQuestion *q = QuestionVector->at(i).b;
            temp = new QTableWidgetItem(q->task.first);
        }
        temp1 = new QTableWidgetItem(QString::fromStdString(to_string(QuestionVector->at(i).type)));
        ui->tableWidget->setItem(i,0,temp);
         ui->tableWidget->setItem(i,1,temp1);
    }
}



void Editor::on_comboBox_currentIndexChanged(int index)
{

}

