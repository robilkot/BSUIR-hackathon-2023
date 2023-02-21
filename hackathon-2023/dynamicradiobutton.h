#ifndef DYNAMICRADIOBUTTON_H
#define DYNAMICRADIOBUTTON_H
#include <QRadioButton>
#include <QObject>

class DynamicRadioButton :public QRadioButton
{
    Q_OBJECT
public:
    explicit DynamicRadioButton(QWidget *parent = 0);
    ~DynamicRadioButton();
    static int ResID;   // Статическая переменная, счетчик номеров
    int getID();         // Функция для возврата локального номера
private:
    int buttonID = 0;   // Локальная переменная, номер
};
#endif // DYNAMICRADIOBUTTON_H
