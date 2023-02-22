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
    ui->nextButton->setEnabled(false);

    ui->exitButton->setIcon(QIcon(":/icons/exit.png"));
    ui->nextButton->setIcon(QIcon(":/icons/checked.png"));
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
        QLabel *imageLabel;

        textLabel->setWordWrap(true);

        // Create layout for item
        QHBoxLayout *layout = new QHBoxLayout;
        layout->addWidget(textLabel);

        if(!pixmap.isNull()) { // Эта функция проклята
            pixmap = pixmap.scaled(pixmap.width() / pixmap.height() * 100,  100);

            imageLabel = new QLabel;
            imageLabel->setPixmap(pixmap);
            imageLabel->setMask(pixmap.mask());

            imageLabel->setFixedSize(pixmap.width(), pixmap.height());
            layout->addWidget(imageLabel);
        } //else
            //imageLabel->clear();

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

    ui->nextButton->setEnabled(true);

    currentQuestionScore = 0;
    currentQuestionNumber = 0; // С 0 а не 1 т.к. вызывается следующий вопрос, включая инкремент

    questionsNumber = questionsQueue.size();

    if(questionsNumber != 0)
        nextQuestion();
    else
        ui->prepodMessage->setText("I have no questions for you...");
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

    clearHBoxLayout(ui->answerLayout);

    QString result = "So, here is your result:\n";

    unsigned short state = prepod->getState();
    if (state > 60) {
        result += "Prepod was glad to hear your answers. He is satisfied with your level of knowledge. Continue studying!";
    } else if (state > 30) {
        result += "Prepod believes you could have done it better. Continue studying!";
    } else {
        result += "As prepod already said, it smells like a retake. Begin studying!";
    }

    ui->questionText->setText(result);
    ui->questionPhoto->clear();
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

        QPixmap* pixmap = new QPixmap(newQuestion.testQuestion.task.second);
        if(!pixmap->isNull()) {
            ui->questionPhoto->setPixmap(*pixmap); // Текст и фото вопроса ставим
            ui->questionPhoto->setMask(pixmap->mask());
            ui->questionPhoto->setFixedSize(pixmap->width() * ui->questionText->height() / pixmap->height(),  ui->questionText->height());
        } else
            ui->questionPhoto->clear();

        QListWidget *list = new QListWidget; // Создаем лист

        ui->answerLayout->addWidget(list); // Кидаем его на лейаут

        for(const auto& option : newQuestion.testQuestion.options) { // Заполняем список
            qDebug() << option.second << "\n";
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
        ui->questionText->setText(newQuestion.openQuestion.task.first);

        qDebug() << newQuestion.openQuestion.task.second << " QUESTION PHOTO\n";
        qDebug() << newQuestion.openQuestion.correctAnswer << " QUESTION ANS\n";

        QPixmap* pixmap = new QPixmap(newQuestion.openQuestion.task.second);
        if(!pixmap->isNull()) {
            ui->questionPhoto->setPixmap(*pixmap); // Текст и фото вопроса ставим
            ui->questionPhoto->setMask(pixmap->mask());
            ui->questionPhoto->setFixedSize(pixmap->width() * ui->questionText->height() / pixmap->height(),  ui->questionText->height());
        } else
            ui->questionPhoto->clear();
        QLineEdit *lineEdit = new QLineEdit;

        ui->answerLayout->addWidget(lineEdit); // Создаем строку для ввода

        connect(lineEdit, &QLineEdit::returnPressed, this, [=]()
        {
            float similarity = lineEdit->text() == newQuestion.openQuestion.correctAnswer; //= nextQuestion.openQuestion.getAnswerCorrentness(lineEdit->text());

            qDebug() << newQuestion.openQuestion.correctAnswer << " YOUR ANS\n";

            if(similarity > 0.85) {
                currentQuestionScore = 15;
            } else if(similarity > 0.7) {
                currentQuestionScore = 10;
            } else currentQuestionScore = -10;
        });
        break;
    }
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

