#include "exam.h"
#include "ui_exam.h"

class Exam::Prepod {
    uint8_t state = 5;
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
    Exam::Prepod prepod(ui->prepodPicture);
}

Exam::~Exam()
{
    delete ui;
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

class TestQuestion {
public:
    QVector<QPair<QString, QString>> options;
};

class OpenQuestion {

};

class Test {
 public:
    int type = 0; // Тип вопросв (тестовый, текстовый, ..)

    TestQuestion testQuestion;
    OpenQuestion openQuestion;
};

void Exam::checkAnswer() {
    QLineEdit *lineEdit = qobject_cast<QLineEdit*>(sender());
       if (lineEdit != nullptr) {
           // Если ввод закончился то епта ладно
       }
}

void Exam::clearHBoxLayout(QHBoxLayout* layout) {
    QLayoutItem *item;
    while ((item = layout->takeAt(0)) != nullptr) {
        delete item->widget();
        delete item;
    }
}

void Exam::nextQuestion(QQueue<Test>& queue) {
    Test nextQuestion = queue.dequeue();

    clearHBoxLayout(ui->answerLayout); // Очистка зоны ответов

    switch(nextQuestion.type) {
    case '0' : { // Если вопрос тестовый
        QListWidget *list = new QListWidget; // Создаем лист

        ui->answerLayout->addWidget(list); // Кидаем его на лейаут

        for(const auto& option : nextQuestion.testQuestion.options) // Заполняем список
            list->addItem(new CustomListItem(option.first, QPixmap(option.second), list));
    }
    case '1': { // Если вопрос открытый
        QLineEdit *lineEdit = new QLineEdit;

        ui->answerLayout->addWidget(lineEdit); // Создаем строку для ввода

        connect(lineEdit, &QLineEdit::editingFinished, this, &Exam::checkAnswer); // Подключаем слот проверки ответа по окончании ввода
    }
    }
}

void Exam::on_exitButton_clicked()
{
    this->close();      // Закрываем окно
    emit mainWindow();  //сигнал на открытие главного окна
}

