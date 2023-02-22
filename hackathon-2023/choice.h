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


    bool easySelected = 0, middleSelected = 1, hardSelected = 0;
    Subject selectedSubject = Subject::NONSPECIFIED;

    void setSubject(int index);

    queue<TestElement> buildQueue(vector<TestElement>& questions);
    queue<TestElement> test;
    queue<TestElement> getTest() const;

    vector<TestElement> getQuestions() const;
    void setQuestions(const vector<TestElement> &newQuestions);
signals:

    void mainWindow();
    void examWindow();
    void updateQueue();
private slots:
    void on_menuButton_clicked();

    void on_examButton_clicked();

    void on_comboBox_currentIndexChanged(int index);

    void on_middleCheck_stateChanged(int arg1);

    void on_hardCheck_stateChanged(int arg1);

    void on_easyCheck_stateChanged(int arg1);

private:
    vector<TestElement> questions; // из mainwindow

    Ui::Choice *ui;
};

#endif // DIFFICULTY_H
