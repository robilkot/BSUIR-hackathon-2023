#include "dynamiclabel.h"

DynamicLabel::DynamicLabel(QWidget *parent)  : QLabel(parent)
{
    ResID++;            // Увеличение счетчика на единицу
    labelID = ResID;   /* Присвоение кнопке номера, по которому будет производиться
                             * дальнейшая работа с кнопок
                             * */
}
DynamicLabel::~DynamicLabel(){}

/* Метод для возврата значения номера
 * */
int DynamicLabel::getID()
{
    return labelID;
}

/* Инициализация статической переменной класса.
 * Статическая переменная класса должна инициализироваться в обязательном порядке
 * */
int DynamicLabel::ResID = 0;
