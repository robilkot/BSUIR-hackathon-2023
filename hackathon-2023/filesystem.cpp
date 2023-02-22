#include "filesystem.h"

FileSystem::FileSystem()
{

}

void FileSystem::readQuestions(vector<TestElement> &test, QString path)
{
    bool correct = false,
            only_pic = false,
            photo = false,
            need = false,
            open=false;

        QFile file(path);
        static QRegularExpression check_1("([(]{1}[1-3]{1}[)]{1})");


        if (file.open(QIODevice::ReadOnly |QIODevice::Text))
        {
            QString temp, buf;
            QChar c;
            unsigned short j = -1, i = -1;
            QTextStream s(&file);
            while (!s.atEnd())
            {
                temp = s.readLine();
                c=temp[0];

                if (temp == "HISTORY" || temp == "MATH" || temp == "RPIIS" ) {

                    need = false;
                    only_pic = false;
                    buf = "";
                    i++, j = -1;
                    test.resize(i + 1);

                    if (temp == "HISTORY") {
                        test[i].testQuestion.subject = Subject::HISTORY;
                        test[i].openQuestion.subject = Subject::HISTORY;
                    } else if (temp == "RPIIS") {
                        test[i].testQuestion.subject = Subject::RPIIS;
                        test[i].openQuestion.subject = Subject::RPIIS;
                    }
                    else if (temp == "MATH") {
                        test[i].testQuestion.subject = Subject::MATH;
                        test[i].openQuestion.subject = Subject::MATH;
                    }
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
                    temp=s.readLine();
                    if (check_1.match(temp).captured() == "(1)") {
                        test[i].testQuestion.difficulty = Difficulty::EASY;
                        test[i].openQuestion.difficulty = Difficulty::EASY;
                    } else if (check_1.match(temp).captured() == "(2)") {
                        test[i].testQuestion.difficulty = Difficulty::MIDDLE;
                        test[i].openQuestion.difficulty = Difficulty::MIDDLE;
                    } else if (check_1.match(temp).captured() == "(3)") {
                        test[i].testQuestion.difficulty = Difficulty::HARD;
                        test[i].openQuestion.difficulty = Difficulty::HARD;
                    }
                    test[i].testQuestion.task.first = temp;
                    test[i].openQuestion.task.first = temp;
                }

                else if (!c.isDigit() && c!='*') {

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
                    else if(temp=="**") {
                        test[i].questions = Questions::OPEN;
                        temp=s.readLine();
                        test[i].openQuestion.correctAnswer = temp;

                        need=true;
                    }

                else if (temp.isEmpty()) {
                    continue;
                }

                else
                {
                    if (photo == true) {
                        test[i].testQuestion.task.second = buf;
                        test[i].openQuestion.task.second = buf;
                        photo = false;
                    }

                    need = true;
                    j++;
                    test[i].testQuestion.options.resize(j + 1);
                    test[i].testQuestion.options[j].first = temp;

                    if (correct == true) {
                        test[i].testQuestion.correctAnswer = j;
                        correct = false;
                    }
                }
            }
            file.close();
        }
}

void FileSystem::saveQuestions(vector<TestElement> &test, QString path)
{
    QFile file(path);
        QTextStream st(&file);
        if (file.open(QFile::WriteOnly)) {
            for (const auto& currentQuestion : test)
            {
                switch (currentQuestion.testQuestion.subject) {
                case Subject::HISTORY: st<<"HISTORY\n"; break;
                case Subject::RPIIS: st<<"RPIIS\n"; break;
                case Subject::MATH: st<<"MATH\n"; break;
                case Subject::NONSPECIFIED: break;
                }
                switch(currentQuestion.testQuestion.difficulty){
                case Difficulty::EASY: st<<"(1)\n";break;
                case Difficulty::MIDDLE:st<<"(2)\n";break;
                case Difficulty::HARD:st<<"(3)\n";break;
                }
                st<<currentQuestion.testQuestion.task.first<<"\n";

                if (!currentQuestion.testQuestion.task.second.isEmpty()) st << currentQuestion.testQuestion.task.second << "\n";
                unsigned short j = 0;
                if(currentQuestion.openQuestion.correctAnswer.isEmpty()){
                for (const auto& option : currentQuestion.testQuestion.options)
                {
                    if (currentQuestion.testQuestion.correctAnswer == j) st << "*\n";
                    if (option.first.isEmpty()) st << option.second << '\n';
                    else if (option.second.isEmpty()) st<<option.first << '\n';
                    else st << option.first << '\n' << option.second << '\n';
                    j++;
                }
                }
                else st << "**\n" << currentQuestion.openQuestion.correctAnswer << '\n';

            }
            file.close();
}
}
