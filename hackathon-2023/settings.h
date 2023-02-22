#ifndef SETTINGS_H
#define SETTINGS_H

#include <QDialog>

namespace Ui {
class Settings;
}

class Settings : public QDialog//окно настроек
{
    Q_OBJECT

public:
    explicit Settings(QWidget *parent = nullptr);
    ~Settings();
signals:
    void mainWindow();
private slots:
    void on_menuButton_clicked();

private:
    Ui::Settings *ui;
};

#endif // SETTINGS_H
