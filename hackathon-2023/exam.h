#ifndef EXAM_H
#define EXAM_H

#include <QDialog>

#include <QListWidget>
#include <QListWidgetItem>
#include <QHBoxLayout>
#include <QLabel>
#include <QLineEdit>
#include <QPixmap>

#include <queue>
#include <QVector>
#include <QMovie>
#include <QTimer>

#include <QDebug>

#include "questions.cpp"
#include "prepod.cpp"

class TestElement;

namespace Ui {

class Exam;
}

class Exam : public QDialog
{
    Q_OBJECT
public:
    Prepod* prepod;

    signed short currentQuestionScore = 0;

    queue<TestElement> questionsQueue;
    size_t questionsNumber = 10,
           currentQuestionNumber = 1;

    explicit Exam(QWidget *parent = nullptr);
    ~Exam();

    void finishExam();
    void updateRating();
    void nextQuestion();
    void clearHBoxLayout(QHBoxLayout* layout);

    void setQuestionsQueue(const queue<TestElement> &newQuestionsQueue);

signals:
    void mainWindow();

public slots:
    void startExam(); //queue<TestElement> queue);

private slots:
    void on_exitButton_clicked();

    void on_nextButton_clicked();

private:
    Ui::Exam *ui;
};

#endif // EXAM_H
