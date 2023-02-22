#ifndef DIFFICULTY_H
#define DIFFICULTY_H

#include <QDialog>
#include "questions.cpp"
#include <vector>
#include <queue>

namespace Ui {
class Choice;
}

class Choice : public QDialog//окно выбора сложности
{
    Q_OBJECT

public:
    explicit Choice(QWidget *parent = nullptr);
    ~Choice();


    Difficulty selectedDifficulty = Difficulty::MIDDLE;
    Subject selectedSubject = Subject::NONSPECIFIED;

    void setDifficulty(int index);
    void setSubject(int index);

    queue<TestElement> buildQueue(vector<TestElement>& questions, Difficulty difficulty, Subject subject);
    queue<TestElement> test;//для exam
    queue<TestElement> getTest() const;

    vector<TestElement> getQuestions() const;
    void setQuestions(const vector<TestElement> &newQuestions);

signals:

    void mainWindow();
    void examWindow();
    void updateQueue();
private slots:
    void on_pushButton_clicked();

    void on_pushButton_5_clicked();

    void on_pushButton_3_clicked();

    void on_pushButton_2_clicked();

    void on_pushButton_4_clicked();

    void on_comboBox_currentIndexChanged(int index);

private:
    vector<TestElement> questions;//из mainwindow
    Ui::Choice *ui;
};

#endif // DIFFICULTY_H
