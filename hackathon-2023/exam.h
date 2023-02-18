#ifndef EXAM_H
#define EXAM_H

#include <QDialog>

namespace Ui {
class Exam;
}

class Exam : public QDialog
{
    Q_OBJECT

public:
    explicit Exam(QWidget *parent = nullptr);
    ~Exam();
signals:
    void mainWindow();
private slots:
    void on_pushButton_5_clicked();

private:
    Ui::Exam *ui;
};

#endif // EXAM_H
