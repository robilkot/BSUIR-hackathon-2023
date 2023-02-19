#ifndef DIFFICULTY_H
#define DIFFICULTY_H

#include <QDialog>
#include "questions.cpp"
namespace Ui {
class Choice;
}

class Choice : public QDialog//окно выбора сложности
{
    Q_OBJECT

public:
    explicit Choice(QWidget *parent = nullptr);
    ~Choice();
signals:
    void mainWindow();
    void examWindow();
private slots:
    void on_pushButton_clicked();

    void on_pushButton_5_clicked();

private:
    Ui::Choice *ui;
};

#endif // DIFFICULTY_H
