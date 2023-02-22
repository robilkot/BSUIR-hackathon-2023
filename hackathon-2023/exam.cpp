#include "exam.h"
#include "ui_exam.h"

void Exam::setQuestionsQueue(const queue<TestElement>& newQuestionsQueue) // Setter
{
    questionsQueue = newQuestionsQueue;
}

Exam::Exam(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Exam)
{
    ui->setupUi(this);
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

void Exam::startExam() {
    prepod = new Prepod(ui->prepodPicture, ui->prepodSatisfaction, ui->prepodMessage);

    currentQuestionScore = 0;
    ui->nextButton->setEnabled(true);
    currentQuestionNumber = 0; // С 0 а не 1 т.к. вызывается следующий вопрос, включая инкремент
    questionsNumber = questionsQueue.size();
    nextQuestion();
}

void Exam::updateRating()
{
    if(currentQuestionScore == 0) return; // Первый вопрос, когда баллов еще нету

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
    ui->nextButton->setEnabled(false);

    // emit resultwindow or transform interface
}

void Exam::nextQuestion()
{
    updateRating();

    if(questionsQueue.empty()) {
        finishExam();
        return;
    }

    currentQuestionNumber++;
    QString prepodMessage = "Question " + QString::number(currentQuestionNumber) + '/' +  QString::number(questionsNumber);
    ui->questionNumber->setText(prepodMessage);

    TestElement newQuestion = questionsQueue.front(); // Получение из очереди следующего вопроса
    questionsQueue.pop();

    clearHBoxLayout(ui->answerLayout); // Очистка зоны ответов

    currentQuestionScore = -10; // По дефолту значение -10, для ситуации с невыбранным вариантом ответа

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

        connect(lineEdit, &QLineEdit::returnPressed, this, [=]()
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
    nextQuestion();
}

