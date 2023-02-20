#include "exam.h"
#include "ui_exam.h"

class Exam::Prepod {
    float state = 5;
    QLabel* picture; // Указатель на лейбл который представляет пикчу препода
    QMovie *idle, *agree, *agreePartly, *disagree, *result;

    public:
    Prepod(QLabel* picture)
    {
        this->picture = picture;

        idle = new QMovie("path/to/animated.gif");
        agree = new QMovie("path/to/animated.gif");
        agreePartly = new QMovie("path/to/animated.gif");
        disagree = new QMovie("path/to/animated.gif");
        result = new QMovie("path/to/animated.gif");

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

    void adjust(short increment) {
        if(state + increment <= 10 && state + increment >= 0) state += increment;
    }

    void animateIdle() {
        picture->setMovie(idle);
        idle->start();
    }
    void animateAgree() {
        picture->setMovie(agree);

        QTimer *timer = new QTimer();
        connect(timer, &QTimer::timeout, [=]() {
            agree->stop();
            animateIdle();
            delete timer;
        } );
        timer->start(1000);

        agree->start();
    }
    void animateDisagree() {
        picture->setMovie(disagree);

        QTimer *timer = new QTimer();
        connect(timer, &QTimer::timeout, [=]() {
            disagree->stop();
            animateIdle();
            delete timer;
        } );
        timer->start(1000);

        disagree->start();
    }
    void animateAgreePartly() {
        picture->setMovie(agreePartly);

        QTimer *timer = new QTimer();
        connect(timer, &QTimer::timeout, [=]() {
            agreePartly->stop();
            animateIdle();
            delete timer;
        } );
        timer->start(1000);

        agreePartly->start();
    }
    void animateResult() {
        picture->setMovie(result);

        QTimer *timer = new QTimer();
        connect(timer, &QTimer::timeout, [=]() {
            result->stop();
            animateIdle();
            delete timer;
        } );
        timer->start(1000);

        result->start();
    }
};

Exam::Exam(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Exam)
{
    ui->setupUi(this);
    prepod = new Prepod(ui->prepodPicture);
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

void Exam::clearHBoxLayout(QHBoxLayout* layout) {
    QLayoutItem *item;
    while ((item = layout->takeAt(0)) != nullptr) {
        delete item->widget();
        delete item;
    }
}

void Exam::updateRating() {
    if(currentQuestionScore < 0) {
        prepod->animateDisagree();
    } else if(currentQuestionScore < 0.5) {
        prepod->animateAgreePartly();
    } else
        prepod->animateAgree();

    prepod->adjust(currentQuestionScore);
}

void Exam::finishExam() {
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

    TestElement nextQuestion = questionsQueue.front();

    clearHBoxLayout(ui->answerLayout); // Очистка зоны ответов

    switch(nextQuestion.questions) {
    case Questions::TEST : { // Если вопрос тестовый
        QListWidget *list = new QListWidget; // Создаем лист

        ui->answerLayout->addWidget(list); // Кидаем его на лейаут

        size_t optionIndex = 0;
        for(const auto& option : nextQuestion.testQuestion.options) { // Заполняем список
            CustomListItem *newOption = new CustomListItem(option.first, QPixmap(option.second), list);
            list->addItem(newOption);

            if(optionIndex == nextQuestion.testQuestion.correctAnswer) {
                connect(newOption, &QListWidget::itemClicked, [&]()
                {
                currentQuestionScore = -0.5;
                Exam::nextQuestion();
                }); // Оценка ответа и новый вопрос при нажатии
            } else {
                connect(newOption, &QListWidget::itemClicked, [&]()
                {
                currentQuestionScore = +0.5;
                Exam::nextQuestion();
                }); // Оценка ответа и новый вопрос при нажатии
            }

            optionIndex++;
        }
    }
    case Questions::OPEN: { // Если вопрос открытый
        QLineEdit *lineEdit = new QLineEdit;

        ui->answerLayout->addWidget(lineEdit); // Создаем строку для ввода

        connect(lineEdit, &QLineEdit::editingFinished, [&]()
        {
            //currentQuestionScore =
            // Оценка ответа
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

