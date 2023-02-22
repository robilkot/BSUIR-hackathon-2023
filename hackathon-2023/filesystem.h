#ifndef FILESYSTEM_H
#define FILESYSTEM_H
#include <QCoreApplication>
#include <QLocale>
#include <QTranslator>
#include <QTextStream>
#include <QIODevice>

#include "questions.cpp"

#include <iostream>
#include <vector>
#include <QString>
#include <QFile>
#include <QRegularExpression>
#include <QRegularExpressionMatch>
#include <QDebug>
using namespace std;
class FileSystem
{
public:
    FileSystem();
    void readQuestions(vector<TestElement>& test, QString path);
    void saveQuestions(vector<TestElement>& test, QString path);
};

#endif // FILESYSTEM_H
