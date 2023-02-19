#ifndef EDITOR_H
#define EDITOR_H

#include <QDialog>
#include "questions.cpp"
namespace Ui {
class Editor;
}

class Editor : public QDialog//окно редактора
{
    Q_OBJECT

public:
    explicit Editor(QWidget *parent = nullptr);
    ~Editor();
signals:
    void mainWindow();
private slots:
    void on_pushButton_clicked();

private:
    Ui::Editor *ui;
    struct Set {

        Question question;
        TestQuestion testquestion;
        OpenQuestion openquestion;

    };
};

#endif // EDITOR_H
