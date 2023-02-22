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
Q_SIGNALS:
    void mainWindow();
    void addQ();
    void deleteQ();
    void typeChange();
private Q_SLOTS:

    void on_exitButton_clicked();

    void on_addQButton_clicked();

    void updateTable();

    void on_deleteQButon_clicked();

    void on_addAns_clicked();

    void slotGetNumber();

    void on_deleteAns_clicked();

    void on_comboBox_2_activated(int index);

    void on_comboBox_activated(int index);

    void on_hardRadioButton_clicked(bool checked);

    void on_normRadioButton_clicked(bool checked);

    void on_easyRadioButton_clicked(bool checked);

    void on_textEdit_textChanged();

    void editOfDynamicEditText();

    void on_textEdit_2_textChanged();

    void on_saveButton_clicked();

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
