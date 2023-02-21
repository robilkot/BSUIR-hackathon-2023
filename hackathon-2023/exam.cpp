#include "exam.h"
#include "ui_exam.h"

class Exam::Prepod
{
    float state = 5; // Удовлетворенность препода
    QLabel* picture; // Указатель на лейбл который представляет пикчу препода
    QProgressBar *satisfaction; // Указатель на прогресс бар который представляет удовлетворенность препода

    QMovie *idle = new QMovie(":/exam/prepod_idle.gif"),
            *agree = new QMovie(":/exam/prepod_agree.gif"),
            *agreePartly = new QMovie(":/exam/prepod_agree_partly.gif"),
            *disagree = new QMovie(":/exam/prepod_disagree.gif"),
            *result = new QMovie(":/exam/prepod_result.gif");

    public:
    Prepod(QLabel* picture, QProgressBar* satisfaction)
    {
        this->picture = picture;
        this->satisfaction = satisfaction;

        animateIdle();
    }

    ~Prepod()
    {
        delete idle;
        delete agree;
        delete agreePartly;
        delete disagree;
        delete result;
    }

    void stopAnimation(QMovie* picture, int delay) { // Stop given animation after given delay
        QTimer *timer = new QTimer();
        connect(timer, &QTimer::timeout, [&]() {
            picture->stop();
            animateIdle();
            delete timer;
        } );
        timer->start(delay);
    }

    void adjustSatisfaction(short increment) {
        if(state + increment <= 10 && state + increment >= 0) {
            state += increment; // Меняем удовольствие препода
            satisfaction->setValue(state); // Прогресс бару нужное значение ставим
        }
    }

    void animateIdle() {
        picture->setMovie(idle);
        idle->start();
    }
    void animateAgree() {
        picture->setMovie(agree);
        agree->start();

        stopAnimation(agree, 1000);
    }
    void animateDisagree() {
        picture->setMovie(disagree);
        disagree->start();

        stopAnimation(disagree, 1000);
    }
    void animateAgreePartly() {
        picture->setMovie(agreePartly);
        agreePartly->start();

        stopAnimation(agreePartly, 1000);
    }
    void animateResult() {
        picture->setMovie(result);
        result->start();

        stopAnimation(result, 1000);
    }
};

Exam::Exam(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Exam)
{
    ui->setupUi(this);
    prepod = new Prepod(ui->prepodPicture, ui->prepodSatisfaction);
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
                connect(list, &QListWidget::itemChanged, [=]() {
                    if(list->selectedItems().front() == newOption) { // Тут обязательно контекст по значению т.к. newOption меняется
                    currentQuestionScore = +0.5;
                    Exam::nextQuestion();
                    }
                });
            } else {
                connect(list, &QListWidget::itemChanged, [=]() {
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

        connect(lineEdit, &QLineEdit::editingFinished, [&]()
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

