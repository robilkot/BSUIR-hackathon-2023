#ifndef EXAM_H
#define EXAM_H

#include <QDialog>

#include <QListWidget>
#include <QListWidgetItem>
#include <QHBoxLayout>
#include <QLabel>
#include <QLineEdit>
#include <QPixmap>

#include <QQueue>
#include <QVector>
#include <QMovie>

class Test;

namespace Ui {

class Exam;
}

class Exam : public QDialog
{
    class Prepod;

    Q_OBJECT

public:
    explicit Exam(QWidget *parent = nullptr);
    ~Exam();

    void nextQuestion(QQueue<Test>& queue);
    void clearHBoxLayout(QHBoxLayout* layout);
signals:
    void mainWindow();
private slots:
    void on_exitButton_clicked();
    void checkAnswer();

private:
    Ui::Exam *ui;
};

#endif // EXAM_H
