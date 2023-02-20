

#include <QCoreApplication>
#include <QLocale>
#include <QTranslator>
#include<QTextStream>
#include <QIODevice>

#include <iostream>
#include <vector>
#include<QString>
#include<QFile>
#include <QRegularExpression>
#include<QRegularExpressionMatch>
#include <QDebug>
using namespace std;

enum class Difficulty {
    EASY,
    MIDDLE,
    HARD
};

enum class Subject {
    RPIIS,
    MATH,
    HISTORY,
    NONCLASSIFIED
};

enum class Questions {
    TEST,
    OPEN
};

class Question
{
public:
    Difficulty difficulty = Difficulty::MIDDLE;
    Subject subject = Subject::NONCLASSIFIED;

    pair<QString, QString> task{ "", "" };

};


class TestQuestion : public Question
{


public:

    vector<pair<QString, QString>> options{ { "", "" }, { "", "" } };
    unsigned short correctAnswer = 0;


    bool isAnswerRight(const unsigned short& selectedAnswer) {
        return selectedAnswer == correctAnswer;
    }
};

class OpenQuestion : Question
{
public:
    QString correctAnswer = "";

    /*float getAnswerCorrentness(QString answer) {
        // Тут должна быть хуйня из питона которая сравнивает строки по значению
    }*/
};

class TestElement
{
public:
    OpenQuestion openQuestion;
    TestQuestion testQuestion;

    Questions questions = Questions::TEST;
};




void read(vector<TestElement>& test) {

    bool correct = false,
        only_pic = false,
        photo = false,
        need = false,
            open=false;
    QString path = "c:\\users\\user\\desktop\\input.txt";
    QFile file(path);
    static QRegularExpression check_1("([(]{1}[1-3]{1}[)]{1})");
    static QRegularExpression check_2("([a-zA-Z]{1}[:]{1}[\\\\]{1})");


    if (file.open(QIODevice::ReadOnly |QIODevice::Text)) {


        QString temp, buf;
        unsigned short j = -1, i = -1;
        QTextStream s(&file);
        while (!s.atEnd()) {

            temp=s.readLine();
           // qDebug()<<temp;


            if (temp == "HISTORY" || temp == "MATH" || temp == "RPIIS" ) {

                need = false;
                only_pic = false;
                buf = "";
                i++, j = -1;
                test.resize(i + 1);

                if (temp == "HISTORY") test[i].testQuestion.subject = Subject::HISTORY;
                else if (temp == "RPIIS") test[i].testQuestion.subject = Subject::RPIIS;
                else if (temp == "MATH") test[i].testQuestion.subject = Subject::MATH;

            }
            else if (check_1.match(temp).hasMatch()) {
                if (need == true) {
                    only_pic = false;
                    buf = "";
                    need = false;
                    j = -1;
                    i++;
                    test.resize(i + 1);
                }

                if (check_1.match(temp).captured() == "(1)")test[i].testQuestion.difficulty = Difficulty::EASY;
                else if (check_1.match(temp).captured() == "(2)")test[i].testQuestion.difficulty = Difficulty::MIDDLE;
                else if (check_1.match(temp).captured() == "(3)") test[i].testQuestion.difficulty = Difficulty::HARD;

                test[i].testQuestion.task.first = temp;

            }

            else if (check_2.match(temp).hasMatch()) {

                if (photo == false && buf.isEmpty()) {
                    buf = temp;
                    photo = true;
                }
                else if (photo == true) {
                    only_pic = true;
                    photo = false;
                }
                if (only_pic == true) {

                    need = true;
                    j++;
                    if (correct == true) {
                        test[i].testQuestion.correctAnswer = j;
                        correct = false;
                    }
                    test[i].testQuestion.options.resize(j + 1);
                    if (j == 0) {
                        test[i].testQuestion.options[j].second = buf;
                        j++;
                        test[i].testQuestion.options.resize(j + 1);
                    }
                    test[i].testQuestion.options[j].second = temp;
                }


            }
            else if (temp == "*") correct = true;
            else if(temp=="**") open=true;
            else if (temp.isEmpty()) {

                continue;

            }
            else if(open==true){
                  test[i].openQuestion.correctAnswer=temp;
                  open=false;

                  need=true;
            }
            else {


                if (photo == true) {
                    test[i].testQuestion.task.second = buf;
                    photo = false;
                }


                need = true;
                j++;
                test[i].testQuestion.options.resize(j + 1);
                test[i].testQuestion.options[j].first = temp;



                if (correct == true) {
                    test[i].testQuestion.correctAnswer =j;
                    correct = false;
                }



            }

        }
        file.close();
    }

}



void save(vector<TestElement>& test) {
    QString path = "c:\\users\\user\\desktop\\inp.txt";
    QFile file(path);
    QTextStream st(&file);
    if (file.open(QFile::WriteOnly)) {
        for (const auto& currentQuestion : test) {

            switch (currentQuestion.testQuestion.subject) {
            case Subject::HISTORY: st<<"HISTORY\n"; break;
            case Subject::RPIIS: st<<"RPIIS\n"; break;
            case Subject::MATH: st<<"MATH\n"; break;
            case Subject::NONCLASSIFIED: break;
            }

            st<<currentQuestion.testQuestion.task.first<<"\n";

            if (!currentQuestion.testQuestion.task.second.isEmpty()) st << currentQuestion.testQuestion.task.second << "\n";
            unsigned short j = 0;
            if(currentQuestion.openQuestion.correctAnswer.isEmpty()){
            for (const auto& option : currentQuestion.testQuestion.options) {
                if (currentQuestion.testQuestion.correctAnswer == j) st << "*\n";
                if (option.first.isEmpty()) st << option.second <<"\n";
                else if (option.second.isEmpty()) st<<option.first<<"\n";
                else st << option.first << "\n" << option.second << "\n";
                j++;
            }
            }
            else st<<"**\n"<<currentQuestion.openQuestion.correctAnswer<<"\n";

        }
        file.close();
    }
}

int main() {


vector<TestElement> test;

    read(test);
/*
    for (int i = 0; i < test.size(); i++) {
       if (test[i].testQuestion.difficulty == Difficulty::EASY)cout << "1" << endl;
       else if (test[i].testQuestion.difficulty == Difficulty::MIDDLE)cout << "2" << endl;
       else cout << "3" << endl;
       qDebug()<< test[i].testQuestion.task.first<<"\t";
       if (!test[i].testQuestion.task.second.isEmpty())  qDebug()<<test[i].testQuestion.task.second << "\n";
       else qDebug()<<"\n";
       if(test[i].openQuestion.correctAnswer.isEmpty()){
       for (int j = 0; j < test[i].testQuestion.options.size(); j++) {
           if (test[i].testQuestion.correctAnswer == j) cout << "Correct answer : ";
           if (!test[i].testQuestion.options[j].first.isEmpty())qDebug()<<test[i].testQuestion.options[j].first;
           if (!test[i].testQuestion.options[j].second.isEmpty())qDebug()<<test[i].testQuestion.options[j].second<<"\n";
       }
       }
       else qDebug()<<test[i].openQuestion.correctAnswer<<"\n";
    }*/

    save(test);

    return 0;
}


