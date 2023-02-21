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

    // Тут надо передавать в exam вызванную buildQueue; ...

    emit examWindow();  //сигнал на открытие окна экзамена
}


queue<TestElement> Choice::buildQueue(vector<TestElement>& questions, Difficulty selectedDifficulty, Subject selectedSubject)
{
    queue<TestElement> queue;

    for(auto& testElement : questions)
    {
        if(queue.size() >= 10) break; // Если накопилось 10 вопросов в очереди, то дальше не ищем

        bool isQuestionSuitable = 0; // Проверяем подходит ли вопрос из списка под наше условие

        switch(testElement.questions) {
        case Questions::TEST :
        {
            isQuestionSuitable = testElement.testQuestion.difficulty == selectedDifficulty && testElement.testQuestion.subject == selectedSubject;
            break;
        }
        case Questions::OPEN :
        {
            isQuestionSuitable = testElement.openQuestion.difficulty == selectedDifficulty && testElement.openQuestion.subject == selectedSubject;
            break;
        }
        }
        if(isQuestionSuitable) queue.push(testElement); // Пушим вопрос в очередь если подходит
    }

    return queue;
}
