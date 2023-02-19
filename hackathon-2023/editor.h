#ifndef EDITOR_H
#define EDITOR_H

#include <QDialog>
#include "questions.cpp"
#include <QVector>
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
    void addQ();
    void deleteQ();
private slots:

    void on_exitButton_clicked();

    void on_addQButton_clicked();

    void updateTable();
    void on_deleteQButon_clicked();

    void on_comboBox_currentIndexChanged(int index);

private:
    Ui::Editor *ui;

    struct questionStruct
    {
      TestQuestion *a = new TestQuestion();
      OpenQuestion *b = new OpenQuestion();
      bool type = false;//изначально стоит test
    };
    std::vector<questionStruct> *QuestionVector;

};

#endif // EDITOR_H
