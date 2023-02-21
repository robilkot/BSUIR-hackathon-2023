#include "dynamiclineedit.h"

DynamicLineEdit::DynamicLineEdit(QWidget *parent)  : QLineEdit(parent)
{
    ResID++;            // Увеличение счетчика на единицу
    editID = ResID;   /* Присвоение кнопке номера, по которому будет производиться
                             * дальнейшая работа с кнопок
                             * */
}
DynamicLineEdit::~DynamicLineEdit(){}

/* Метод для возврата значения номера
 * */
int DynamicLineEdit::getID()
{
    return editID;
}

/* Инициализация статической переменной класса.
 * Статическая переменная класса должна инициализироваться в обязательном порядке
 * */
int DynamicLineEdit::ResID = 0;
