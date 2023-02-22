#include "exam.h"
#include "ui_exam.h"

Exam::Exam(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Exam)
{
    ui->setupUi(this);
    prepod = new Prepod(ui->prepodPicture, ui->prepodSatisfaction);

    // Тестовый вопрос
    TestQuestion tempq = {
        Difficulty::HARD,
        Subject::RPIIS,
        "Fuck this damn project",
        "",
        {{"opt1", "path1"}, {"opt2", ""}, {"opt3", ""}},
        1
    };

    OpenQuestion tempq2 = {
        Difficulty::HARD,
        Subject::RPIIS,
        "Fuck this damn project",
        "",
        "Correct answer is so"
    };

    TestQuestion tempq3 = {
        Difficulty::HARD,
        Subject::RPIIS,
        "Fuck this damn projec 2 2 2 t",
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

   questionsQueue.push(temp);
   questionsQueue.push(temp2);
   questionsQueue.push(temp3);

   questionsQueue.push(temp);
   questionsQueue.push(temp2);
   questionsQueue.push(temp3);

   questionsQueue.push(temp);
   questionsQueue.push(temp2);
   questionsQueue.push(temp3);

   questionsNumber = questionsQueue.size();

   nextQuestion();
}

Exam::~Exam()
{
    delete ui;
    delete prepod;
}

// Кастомный элемент списка (фото+текст)
class CustomListItem : public QListWidgetItem
{
public:
    CustomListItem(QString text, QPixmap pixmap, QListWidget *parent = nullptr) : QListWidgetItem(parent)
    {
        // Create labels for text and image
        QLabel *textLabel = new QLabel(text);
        QLabel *imageLabel = new QLabel;
        imageLabel->setPixmap(pixmap);

        // Create layout for item
        QHBoxLayout *layout = new QHBoxLayout;
        layout->addWidget(textLabel);
        layout->addWidget(imageLabel);

        // Set layout for item
        QWidget *widget = new QWidget;
        widget->setLayout(layout);
        setSizeHint(widget->sizeHint());
        parent->setItemWidget(this, widget);
    }
};

void Exam::clearHBoxLayout(QHBoxLayout* layout)
{
    QLayoutItem *item;
    while ((item = layout->takeAt(0)) != nullptr) {
        delete item->widget();
        delete item;
    }
}

void Exam::updateRating()
{
    if(currentQuestionScore < 0) {
        prepod->animateDisagree();
    } else if(currentQuestionScore < 10) {
        prepod->animateAgreePartly();
    } else
        prepod->animateAgree();

    prepod->adjustSatisfaction(currentQuestionScore);
}

void Exam::finishExam()
{
    prepod->animateResult();
    //...
    qDebug() << "Exam finished!\n";
}

void Exam::nextQuestion()
{
    updateRating();

    QString prepodMessage = "Question " + QString::number(currentQuestionNumber) + '/' +  QString::number(questionsNumber);
    ui->prepodMessage->setText(prepodMessage);

    if(questionsQueue.empty()) {
        finishExam();
        return;
    }

    TestElement newQuestion = questionsQueue.front(); // Получение из очереди следующего вопроса
    questionsQueue.pop();

    clearHBoxLayout(ui->answerLayout); // Очистка зоны ответов

    currentQuestionScore = 0;

    switch(newQuestion.questions) {
    case Questions::TEST : // Если вопрос тестовый
    {
        ui->questionText->setText(newQuestion.testQuestion.task.first);
        ui->questionPhoto->setPixmap(newQuestion.testQuestion.task.first); // Текст и фото вопроса ставим

        QListWidget *list = new QListWidget; // Создаем лист

        ui->answerLayout->addWidget(list); // Кидаем его на лейаут

        for(const auto& option : newQuestion.testQuestion.options) { // Заполняем список
            CustomListItem *newOption = new CustomListItem(option.first, QPixmap(option.second), list);
            list->addItem(newOption);
        }

        connect(list, &QListWidget::itemClicked, this, [=]()
        {
            if(!list->selectedItems().isEmpty()) {
                int selectedIndex = list->row(list->selectedItems().front());

                if(newQuestion.testQuestion.correctAnswer == selectedIndex) {
                    currentQuestionScore = 10;
                } else {
                    currentQuestionScore = -10;
                }
            }
        });

        break;
    }
    case Questions::OPEN: // Если вопрос открытый
    {
        QLineEdit *lineEdit = new QLineEdit;

        ui->answerLayout->addWidget(lineEdit); // Создаем строку для ввода

        connect(lineEdit, &QLineEdit::returnPressed, this, [=]() // ACHTUNG Тут сегфаулт!
        {
            float similarity = 0.5; //= nextQuestion.openQuestion.getAnswerCorrentness(lineEdit->text());

            if(similarity > 0.85) {
                currentQuestionScore = 15;
            } else if(similarity > 0.7) {
                currentQuestionScore = 10;
            } else currentQuestionScore = -10;
        });
    }
        break;
    }
}

void Exam::on_exitButton_clicked()
{
    this->close();      // Закрываем окно
    emit mainWindow();  //сигнал на открытие главного окна
}

void Exam::on_nextButton_clicked()
{
    currentQuestionNumber++;
    nextQuestion();
}

