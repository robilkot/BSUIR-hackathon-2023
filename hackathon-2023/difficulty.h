#ifndef DIFFICULTY_H
#define DIFFICULTY_H

#include <QDialog>

namespace Ui {
class Difficulty;
}

class Difficulty : public QDialog//окно выбора сложности
{
    Q_OBJECT

public:
    explicit Difficulty(QWidget *parent = nullptr);
    ~Difficulty();
signals:
    void mainWindow();
    void examWindow();
private slots:
    void on_pushButton_clicked();

    void on_pushButton_5_clicked();

private:
    Ui::Difficulty *ui;
};

#endif // DIFFICULTY_H
