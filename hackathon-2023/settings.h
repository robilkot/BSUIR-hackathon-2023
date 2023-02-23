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
    QString getPath() const;
    void setPath(const QString &newPath);

signals:
    void mainWindow();

private slots:
    void on_menuButton_clicked();

    void on_pathEdit_textChanged(const QString &arg1);

private:
    Ui::Settings *ui;
    QString path;
};

#endif // SETTINGS_H
