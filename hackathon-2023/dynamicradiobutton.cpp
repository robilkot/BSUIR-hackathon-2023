#include "dynamicradiobutton.h"

DynamicRadioButton::DynamicRadioButton(QWidget *parent)  : QRadioButton(parent)
{
    ResID++;            // Увеличение счетчика на единицу
    buttonID = ResID;   /* Присвоение кнопке номера, по которому будет производиться
                             * дальнейшая работа с кнопок
                             * */
}
DynamicRadioButton::~DynamicRadioButton(){}

/* Метод для возврата значения номера
 * */
int DynamicRadioButton::getID()
{
    return buttonID;
}

/* Инициализация статической переменной класса.
 * Статическая переменная класса должна инициализироваться в обязательном порядке
 * */
int DynamicRadioButton::ResID = 0;
