#include "choice.h"
#include "ui_choice.h"

Choice::Choice(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Choice)
{
    ui->setupUi(this);

    connect(ui->comboBox, QOverload<int>::of(&QComboBox::currentIndexChanged),
        [=](int index){
            setSubject(index);
        });
}

Choice::~Choice()
{
    delete ui;
}

void Choice::setSubject(int index)
{
    this->selectedSubject = (Subject)index;
}

void Choice::on_pushButton_clicked()
{
    this->close();      // Закрываем окно
    emit mainWindow();  //сигнал на открытие главного окна
}

void Choice::on_pushButton_5_clicked()
{
    this->close();      // Закрываем окно

    TestQuestion tempq = {
        Difficulty::EASY,
        Subject::NONSPECIFIED,
        "Fuck this damn project",
        "",
        {{"opt1", "path1"}, {"opt2", ""}, {"opt3", ""}},
        1
    };

    OpenQuestion tempq2 = {
        Difficulty::MIDDLE,
        Subject::NONSPECIFIED,
        "Fuck this damn project 2",
        "",
        "Correct answer is so"
    };

    TestQuestion tempq3 = {
        Difficulty::HARD,
        Subject::NONSPECIFIED,
        "Fuck this damn projec 3 ",
        "",
        {{"opt11", "path1"}, {"opt22", ""}, {"opt33", ""}},
        0
    };

    TestElement temp = {
        {},
        tempq,
        Questions::TEST
    }, temp2 = {
        tempq2,
        {},
        Questions::OPEN
    }, temp3 = {
        {},
        tempq3,
        Questions::TEST
    };

    vector<TestElement> questions;
    questions.push_back(temp);
    questions.push_back(temp2);
    questions.push_back(temp3);

    questions.push_back(temp);
    questions.push_back(temp2);
    questions.push_back(temp3);

    questions.push_back(temp);
    questions.push_back(temp2);
    questions.push_back(temp3);

    test = buildQueue(questions);

    // Передать test в поле questionsQueue экзамена
    emit updateQueue();
    emit examWindow();  //сигнал на открытие окна экзамена
}

// Формирование очереди вопросов из общего списка по заданным условиям
queue<TestElement> Choice::buildQueue(vector<TestElement>& questions)
{
    queue<TestElement> queue;

    for(auto& testElement : questions)
    {
        if(queue.size() >= 10) break; // Если накопилось 10 вопросов в очереди, то дальше не ищем

        bool isQuestionSuitable = 0; // Проверяем подходит ли вопрос из списка под наше условие
        Difficulty questionDifficulty;

        switch(testElement.questions) {
        case Questions::TEST :
        {
            isQuestionSuitable = testElement.testQuestion.subject == selectedSubject;
            questionDifficulty = testElement.testQuestion.difficulty;
            break;
        }
        case Questions::OPEN :
        {
            isQuestionSuitable = testElement.openQuestion.subject == selectedSubject;
            questionDifficulty = testElement.openQuestion.difficulty;
            break;
        }
        }

        if(!isQuestionSuitable) continue; // Если вопрос по предмету не подошел, сразу мимо
        isQuestionSuitable = false;

        switch(questionDifficulty)
        {
        case Difficulty::EASY : {
                isQuestionSuitable = easySelected;
                break;
        }
        case Difficulty::MIDDLE : {
                isQuestionSuitable = middleSelected;
                break;
        }
        case Difficulty::HARD: {
                isQuestionSuitable = hardSelected;
                break;
        }
        }

        if(isQuestionSuitable) queue.push(testElement); // Пушим вопрос в очередь если подходит
    }

    return queue;
}

queue<TestElement> Choice::getTest() const
{
    return test;
}

void Choice::on_comboBox_currentIndexChanged(int index)
{
    setSubject(index);
}

void Choice::on_middleCheck_stateChanged(int arg1)
{
    middleSelected = !middleSelected;
}


void Choice::on_hardCheck_stateChanged(int arg1)
{
    hardSelected = !hardSelected;
}


void Choice::on_easyCheck_stateChanged(int arg1)
{
    easySelected = !easySelected;
}

