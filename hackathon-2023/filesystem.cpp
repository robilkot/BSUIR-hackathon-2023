#include "filesystem.h"

FileSystem::FileSystem() { }

void FileSystem::readQuestions(vector<TestElement> &test, QString path)
{
    bool correct = false,
            only_pic = false,
            need = true,
            open=false;

    QFile file(path);
    static QRegularExpression check_1("([(]{1}[1-3]{1}[)]{1})");
    static QRegularExpression check_2 ("[a-zA-Z[:space:]]+[:]{1}[\\/]");


    if (file.open(QIODevice::ReadOnly |QIODevice::Text)) {


        QString temp, buf_1, buf_2;
        unsigned short j = 0, i = -1;
        QTextStream s(&file);

        while (!s.atEnd()) {
            temp=s.readLine();
           if(temp=="HISTORY" || temp=="MATH" || temp=="RPISS"){
               if(need==true){
               i++;
               j=0;
               test.resize(i+1);
               need=false;
               only_pic=false;
               }
               if(temp=="HISTORY") {
                   test[i].testQuestion.subject=Subject::HISTORY;
                   test[i].openQuestion.subject=Subject::HISTORY;
               }
                   else if(temp=="MATH") {
                   test[i].testQuestion.subject=Subject::MATH;
                   test[i].openQuestion.subject=Subject::MATH;
               }
                   else if(temp=="RPIIS"){
                   test[i].testQuestion.subject=Subject::RPIIS;
                    test[i].openQuestion.subject=Subject::RPIIS;

               }
                       else {
                   test[i].testQuestion.subject=Subject::NONSPECIFIED;
                   test[i].openQuestion.subject=Subject::NONSPECIFIED;
               }

            }
           else if(check_1.match(temp).hasMatch()){
               if(need==true){
                   i++;
                   test.resize(i+1);
                   j=0;
                   need=false;
                   only_pic=false;
               }


               if(check_1.match(temp).captured()=="(1)"){
                   test[i].testQuestion.difficulty=Difficulty::EASY;
                   test[i].openQuestion.difficulty=Difficulty::EASY;
               }
               else if (check_1.match(temp).captured()=="(2)"){
                   test[i].testQuestion.difficulty=Difficulty::MIDDLE;
                   test[i].openQuestion.difficulty=Difficulty::MIDDLE;
               }
               else if (check_1.match(temp).captured()=="(3)"){
                   test[i].testQuestion.difficulty=Difficulty::HARD;
                   test[i].openQuestion.difficulty=Difficulty::HARD;
               }
               temp=s.readLine();
               buf_1=temp;
           }
           else if(check_2.match(temp).hasMatch()){
               if(only_pic==false) {
                   only_pic=true;
                   buf_2=temp;
               }
               else {
                   if(!buf_2.isEmpty()){
                       test[i].questions=Questions::TEST;
                       test[i].testQuestion.task.first=buf_1;
                       test[i].testQuestion.task.second=buf_2;

                       buf_2="";
                       buf_1="";
                   }
                   if(need==false)need=true;
                   test[i].testQuestion.options.resize(j+1);
                   test[i].testQuestion.options[j].second=temp;

                   if(correct==true) {
                       test[i].testQuestion.correctAnswer=j;
                       correct=false;
                   }
                   j++;
               }
           }
           else if(temp=="**"){
               temp=s.readLine();
               test[i].openQuestion.task.first=buf_1;
               test[i].questions=Questions::OPEN;
               test[i].openQuestion.correctAnswer=temp;
               if(!buf_2.isEmpty())test[i].openQuestion.task.second=buf_2;
               buf_1="";
               buf_2="";
               need=true;
           }
           else if(temp=="*") correct=true;
           else if(temp.isEmpty()) continue;
           else {
               if(only_pic==true){
                   only_pic=false;
                   test[i].testQuestion.task.second=buf_2;
                   buf_2="";
               }
               if(!buf_1.isEmpty()){
                   test[i].questions=Questions::TEST;
                   test[i].testQuestion.task.first=buf_1;

                   buf_1="";
               }
               if(need==false)need =true;
               test[i].testQuestion.options.resize(j+1);
               test[i].testQuestion.options[j].first=temp;
               if(correct==true){
                   test[i].testQuestion.correctAnswer=j;
                   correct=false;
               }
               j++;
           }

        }
        file.close();
    }
}

void FileSystem::saveQuestions(vector<TestElement>& test, QString path) {
    QFile file(path);
    QTextStream st(&file);
    if (file.open(QFile::WriteOnly)) {
        for (const auto& currentQuestion : test) {

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

            if(currentQuestion.openQuestion.task.first.isEmpty())st<<currentQuestion.testQuestion.task.first<<"\n";
            else st<<currentQuestion.openQuestion.task.first<<"\n";

            if (!currentQuestion.testQuestion.task.second.isEmpty()) st << currentQuestion.testQuestion.task.second << "\n";
            if (!currentQuestion.openQuestion.task.second.isEmpty()) st << currentQuestion.openQuestion.task.second << "\n";
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
