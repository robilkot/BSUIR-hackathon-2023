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

#include "questions.cpp"

class TestElement;

namespace Ui {

class Exam;
}

class Exam : public QDialog
{
    Q_OBJECT
public:

    class Prepod;
    float currentQuestionScore = 0;

    Prepod* prepod;

    queue<TestElement> questionsQueue;

    explicit Exam(QWidget *parent = nullptr);
    ~Exam();

    void finishExam();
    void updateRating();
    void nextQuestion();
    void clearHBoxLayout(QHBoxLayout* layout);

    void falseAnswer();
    void correctAnswer();

signals:
    void mainWindow();
private slots:
    void on_exitButton_clicked();

private:
    Ui::Exam *ui;
};

#endif // EXAM_H
