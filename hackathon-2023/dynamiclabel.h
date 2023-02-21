#ifndef DYNAMICLABEL_H
#define DYNAMICLABEL_H
#include <QLabel>
#include <QObject>
class DynamicLabel : public QLabel
{
    Q_OBJECT
public:
    explicit DynamicLabel(QWidget *parent = 0);
    ~DynamicLabel();
    static int ResID;   // Статическая переменная, счетчик номеров
    int getID();         // Функция для возврата локального номера
private:
    int labelID = 0;   // Локальная переменная, номер
};

#endif // DYNAMICLABEL_H
