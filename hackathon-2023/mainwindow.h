#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "choice.h"
#include "editor.h"
#include "exam.h"
#include "settings.h"
#include <QMainWindow>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

   void read(QString path);

   vector<TestElement> test;
private slots:
    void on_examButton_clicked();

    void on_exitButton_clicked();

    void on_settingsButton_clicked();

    void on_editorButton_clicked();

    void openExamWindow();

    void updateQueue();

private:
    Choice *choiceWindow;
    Settings *settingsWindow;
    Editor *editorWindow;
    Exam *examWindow;
    Ui::MainWindow *ui;
};
#endif // MAINWINDOW_H
