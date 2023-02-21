#include <QLabel>
#include <QLineEdit>
#include <QPixmap>
#include <QVector>
#include <QMovie>
#include <QProgressBar>
#include <QTimer>

class Prepod
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
        QObject::connect(timer, &QTimer::timeout, [=]() {
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
