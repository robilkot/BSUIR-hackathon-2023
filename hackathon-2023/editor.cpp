#include "editor.h"
#include "ui_editor.h"
#include <QDebug>
#include "dynamiclabel.h"
#include "dynamiclineedit.h"
#include "dynamicradiobutton.h"
#include <QGroupBox>
Editor::Editor(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Editor)
{

    ui->setupUi(this);

    QuestionVector = new vector<questionStruct>;//вектор для хранения списака вопросов

    ui->comboBox->addItem("Test");
    ui->comboBox->addItem("Open");

    ui->comboBox_2->addItem("NONSPECIFIED");
    ui->comboBox_2->addItem("RPIIS");
    ui->comboBox_2->addItem("MATH");
    ui->comboBox_2->addItem("HISTORY");

    ui->tableWidget->setColumnCount(2);

    connect(this,&Editor::addQ,this,&Editor::updateTable);//подключил расширение таблицы к нажатию кнопки добавления эл-та
    connect(this,&Editor::deleteQ,this,&Editor::updateTable);//подключил уменьшение таблицы к нажатию кнопки удаления эл-та
    connect(this,&Editor::typeChange,this,&Editor::updateTable);//подключил переключение типа к обновлению таблицы

}

Editor::~Editor()
{
    delete ui;
}

void Editor::on_exitButton_clicked()
{
    this->close();      // Закрываем окно
    Q_EMIT mainWindow();  //сигнал на открытие главного окна
}

void Editor::on_addQButton_clicked()
{

    questionStruct *a= new questionStruct();
    QuestionVector->push_back(*a);
    Q_EMIT on_comboBox_activated(0);
    Q_EMIT addQ();
    ui->textEdit->clear();
}
void Editor::on_deleteQButon_clicked()
{
    if(!QuestionVector->empty())
    {
     QuestionVector->pop_back();
        if(!QuestionVector->empty())
        {
            ui->textEdit->setText(QuestionVector->back().a->task.first);
        }

    }
    Q_EMIT deleteQ();

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
           // qDebug()<<"Text "<< QuestionVector->at(i).a->task.first;
            //qDebug()<<"Text of back "<< QuestionVector->back().a->task.first;
           // qDebug()<<"Difficulty  "<< QuestionVector->back().a->difficulty;
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

void Editor::on_addAns_clicked()
{
    DynamicLabel *label = new DynamicLabel(this);
    label->setText("Ответ "+QString::number(label->getID()));
    ui->verticalLayout_4->addWidget(label);

   DynamicLineEdit *lineEdit = new DynamicLineEdit(this);
   lineEdit->setText("Ответ");
   ui->verticalLayout_3->addWidget(lineEdit);
   lineEdit->show();

   DynamicRadioButton *radioButton = new DynamicRadioButton(this);
   ui->verticalLayout_2->addWidget(radioButton);

    qDebug()<< "counter "<< ui->verticalLayout_3->count();

   if(!QuestionVector->back().a->options.empty())
       if(ui->verticalLayout_3->count()>2)
       {
           questionStruct &temp =QuestionVector->back();
          temp.a->options.push_back(pair<QString, QString>{ "Empty answer", "" });
       }
   {
       connect(lineEdit,&DynamicLineEdit::textEdited,this,&Editor::editOfDynamicEditText);
    //questionStruct &temp =QuestionVector->back();
   }
}

void Editor::on_deleteAns_clicked()
{
    if(ui->verticalLayout_4->count()!=0)
    {
    DynamicLabel *label = qobject_cast<DynamicLabel*>(ui->verticalLayout_4->itemAt(ui->verticalLayout_4->count()-1)->widget());
    if(ui->verticalLayout_4->count()==1)
    {
        label->ResID=0;
    }else
    {
        DynamicLabel *labelTemp = qobject_cast<DynamicLabel*>(ui->verticalLayout_4->itemAt(ui->verticalLayout_4->count()-1)->widget());
        labelTemp->ResID=ui->verticalLayout_4->count()-1;
    }
    label->hide();
    delete label;
    }

    if(ui->verticalLayout_3->count()!=0)
    {
    DynamicLineEdit *lineEdit = qobject_cast<DynamicLineEdit*>(ui->verticalLayout_3->itemAt(ui->verticalLayout_3->count()-1)->widget());
    if(ui->verticalLayout_3->count()==1)
    {
        lineEdit->ResID=0;
    }else
    {
        DynamicLineEdit *lineEdit = qobject_cast<DynamicLineEdit*>(ui->verticalLayout_3->itemAt(ui->verticalLayout_3->count()-1)->widget());
        lineEdit->ResID=ui->verticalLayout_3->count()-1;
    }
    lineEdit->hide();
    delete lineEdit;
    }

    if(ui->verticalLayout_2->count()!=0)
    {
    DynamicRadioButton *radioButton = qobject_cast<DynamicRadioButton*>(ui->verticalLayout_2->itemAt(ui->verticalLayout_2->count()-1)->widget());
    if(ui->verticalLayout_2->count()==1)
    {
        radioButton->ResID=0;
    }else
    {
        DynamicRadioButton *radioButton = qobject_cast<DynamicRadioButton*>(ui->verticalLayout_2->itemAt(ui->verticalLayout_2->count()-1)->widget());
        radioButton->ResID=ui->verticalLayout_2->count()-1;
    }
    radioButton->hide();
    delete radioButton;
    }
}
void Editor::slotGetNumber()
{

}

void Editor::on_comboBox_2_activated(int index)
{
    if(!QuestionVector->empty()){
    questionStruct &temp =QuestionVector->back();
    switch (index) {
    case 1:
    {
        if(temp.type)
        {
            temp.b->subject=Subject::RPIIS;
        }
        else
        {
            temp.a->subject=Subject::RPIIS;
        }
        break;
    }
    case 2:
    {
        if(temp.type)
        {
            temp.b->subject=Subject::MATH;
        }
        else
        {
            temp.a->subject=Subject::MATH;
        }
        break;
    }
    case 3:
    {
        if(temp.type)
        {
            temp.b->subject=Subject::HISTORY;
        }
        else
        {
            temp.a->subject=Subject::HISTORY;
        }
        break;
    }

    default:
    {
        break;
    }
    }
}
}


void Editor::on_comboBox_activated(int index)
{
    ui->comboBox->setCurrentIndex(index);
    if(index==0)
    {
        ui->textEdit_2->hide();
        ui->addAns->show();
        ui->deleteAns->show();

    }
    else
    {
        int count = ui->verticalLayout_2->count();
        for(int i=0;i<count;i++)
        {
            Q_EMIT on_deleteAns_clicked();
        }
        ui->addAns->hide();
        ui->deleteAns->hide();
        ui->textEdit_2->show();
    }
    if(QuestionVector->size()!=0)
    {
    QuestionVector->at(QuestionVector->size()-1).type=index;
    Q_EMIT typeChange();
    }
}


void Editor::on_hardRadioButton_clicked(bool checked)
{
    if(!QuestionVector->empty()){
    questionStruct &temp =QuestionVector->back();
    if(!temp.type)
    {
        temp.b->difficulty = Difficulty::HARD;
    }
    else
    {
        temp.a->difficulty = Difficulty::HARD;
    }
    }
}


void Editor::on_normRadioButton_clicked(bool checked)
{
    if(!QuestionVector->empty()){
    questionStruct &temp =QuestionVector->back();
    if(!temp.type)
    {
        temp.b->difficulty = Difficulty::MIDDLE;
    }
    else
    {
        temp.a->difficulty = Difficulty::MIDDLE;
    }
    }
}


void Editor::on_easyRadioButton_clicked(bool checked)
{
    if(!QuestionVector->empty()){
    questionStruct &temp =QuestionVector->back();
    if(!temp.type)
    {
        temp.b->difficulty = Difficulty::EASY;
    }
    else
    {
        temp.a->difficulty = Difficulty::EASY;
    }
    }
}


void Editor::on_textEdit_textChanged()
{
    if(!QuestionVector->empty()){
    questionStruct &temp =QuestionVector->back();
    temp.a->task.first=ui->textEdit->document()->toRawText();
    temp.b->task.first=ui->textEdit->document()->toRawText();
    }
    Q_EMIT updateTable();

}

void Editor::editOfDynamicEditText()
{
        DynamicLineEdit *lineEdit = qobject_cast<DynamicLineEdit*>(ui->verticalLayout_3->itemAt(ui->verticalLayout_3->count()-1)->widget());
        questionStruct &temp =QuestionVector->back();
        qDebug()<< "text " << (lineEdit->displayText());
        temp.a->options.at(ui->verticalLayout_3->count()).first = (lineEdit->displayText());
        questionStruct &temp1 =QuestionVector->back();
        qDebug()<< "first  "<< temp1.a->options.back().first;
}
