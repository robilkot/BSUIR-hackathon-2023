#ifndef DYNAMICLINEEDIT_H
#define DYNAMICLINEEDIT_H

#include <QObject>
#include <QLineEdit>
class DynamicLineEdit :public QLineEdit
{
    Q_OBJECT
public:
    explicit DynamicLineEdit(QWidget *parent = 0);
    ~DynamicLineEdit();
    static int ResID;   // Статическая переменная, счетчик номеров
    int getID();         // Функция для возврата локального номера
private:
    int editID = 0;   // Локальная переменная, номер
};

#endif // DYNAMICLINEEDIT_H
