#include <QLabel>
#include <QLineEdit>
#include <QPixmap>
#include <QVector>
#include <QMovie>
#include <QProgressBar>
#include <QTimer>

class Prepod
{
    unsigned short state = 50; // Удовлетворенность препода
    QLabel* picture; // Указатель на лейбл который представляет пикчу препода
    QProgressBar *satisfaction; // Указатель на прогресс бар который представляет удовлетворенность препода
    QLabel* message;

    QMovie *idle = new QMovie(":/exam/prepod_idle.gif"),
            *agree = new QMovie(":/exam/prepod_agree.gif"),
            *agreePartly = new QMovie(":/exam/prepod_agree_partly.gif"),
            *disagree = new QMovie(":/exam/prepod_disagree.gif"),
            *result = new QMovie(":/exam/prepod_result.gif");

    public:
    Prepod(QLabel* picture, QProgressBar* satisfaction, QLabel* message)
    {
        this->picture = picture;
        this->satisfaction = satisfaction;
        this->message = message;

        adjustSatisfaction(0);
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

    void stopAnimation(QMovie* picture, QLabel* message, int delay) { // Stop given animation after given delay
        QTimer *timer = new QTimer();
        QObject::connect(timer, &QTimer::timeout, [=]() {
            picture->stop();
            animateIdle();
            delete timer;
        } );
        timer->start(delay);
    }

    void adjustSatisfaction(signed short increment) {
        signed short target = state + increment;
        if(target <= 100 && target >= 0) {
            state = target; // Меняем удовольствие препода
        }
        satisfaction->setValue(state); // Прогресс бару нужное значение ставим
    }

    void animateIdle() {
        picture->setMovie(idle);
        message->setText("Well, i'm waiting for your answer...");
        idle->start();
    }
    void animateAgree() {
        picture->setMovie(agree);
        agree->start();
        message->setText("Okay, your answer seems correct. Now to the next question.");

        stopAnimation(agree, message, 3000);
    }
    void animateDisagree() {
        picture->setMovie(disagree);
        disagree->start();
        message->setText("No, that isn't correct.");

        stopAnimation(disagree, message, 3000);
    }
    void animateAgreePartly() {
        picture->setMovie(agreePartly);
        agreePartly->start();
        message->setText("This is... not quite right. Anyway, next question.");

        stopAnimation(agreePartly, message, 3000);
    }
    void animateResult() {
        picture->setMovie(result);
        result->start();
        message->setText("That was it. Now let's take a look at your results.");

        QTimer *timer = new QTimer();
        QObject::connect(timer, &QTimer::timeout, [=]() {
            result->stop();
            delete timer;
        } );
        timer->start(1000);
    }
};
