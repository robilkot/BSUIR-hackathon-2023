#include "exam.h"
#include "ui_exam.h"

Exam::Exam(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Exam)
{
    ui->setupUi(this);
    prepod = new Prepod(ui->prepodPicture, ui->prepodSatisfaction);

    // Тестовый вопрос
//    TestQuestion tempq = {
//        Difficulty::HARD,
//        Subject::RPIIS,
//        "Fuck this damn project",
//        "",
//        {{"opt1", "path1"}, {"opt2", ""}, {"opt3", ""}},
//        1
//    };

//    TestElement temp = {
//        {},
//        tempq,
//        Questions::TEST
//    };

//    questionsQueue.push(temp);
//    questionsQueue.push(temp);

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
    } else if(currentQuestionScore < 0.5) {
        prepod->animateAgreePartly();
    } else
        prepod->animateAgree();

    prepod->adjustSatisfaction(currentQuestionScore);
}

void Exam::finishExam()
{
    prepod->animateResult();
    //...
}

void Exam::nextQuestion()
{
    updateRating();

    if(questionsQueue.empty()) {
        finishExam();
        return;
    }

    TestElement nextQuestion = questionsQueue.front(); // Получение из очереди следующего вопроса

    clearHBoxLayout(ui->answerLayout); // Очистка зоны ответов

    switch(nextQuestion.questions) {
    case Questions::TEST : // Если вопрос тестовый
    {
        ui->questionText->setText(nextQuestion.testQuestion.task.first);
        ui->questionPhoto->setPixmap(nextQuestion.testQuestion.task.first); // Текст и фото вопроса ставим

        QListWidget *list = new QListWidget; // Создаем лист

        ui->answerLayout->addWidget(list); // Кидаем его на лейаут

        size_t optionIndex = 0;
        for(const auto& option : nextQuestion.testQuestion.options) { // Заполняем список
            CustomListItem *newOption = new CustomListItem(option.first, QPixmap(option.second), list);

            list->addItem(newOption);

            if(optionIndex == nextQuestion.testQuestion.correctAnswer) {
                connect(list, &QListWidget::itemChanged, this, [=]() {
                    if(list->selectedItems().front() == newOption) { // Тут обязательно контекст по значению т.к. newOption меняется
                    currentQuestionScore = +0.5;
                    Exam::nextQuestion();
                    }
                });
            } else {
                connect(list, &QListWidget::itemChanged, this, [=]() {
                    if(list->selectedItems().front() == newOption) {
                    currentQuestionScore = -0.5;
                    Exam::nextQuestion();
                    }
                });
            }
        }

        optionIndex++;
    }
    case Questions::OPEN: // Если вопрос открытый
    {
        QLineEdit *lineEdit = new QLineEdit;

        ui->answerLayout->addWidget(lineEdit); // Создаем строку для ввода

        connect(lineEdit, &QLineEdit::editingFinished, this, [&]()
        {
            float similarity = 0.5; //= nextQuestion.openQuestion.getAnswerCorrentness(lineEdit->text());

            if(similarity > 0.85) {
                currentQuestionScore = 1;
            } else if(similarity > 0.7) {
                currentQuestionScore = 0.5;
            } else currentQuestionScore = -0.5;

            Exam::nextQuestion();
        });
    }
    }
}

void Exam::on_exitButton_clicked()
{
    this->close();      // Закрываем окно
    emit mainWindow();  //сигнал на открытие главного окна
}

