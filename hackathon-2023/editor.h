#ifndef EDITOR_H
#define EDITOR_H

#include <QDialog>

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
};

#endif // EDITOR_H
