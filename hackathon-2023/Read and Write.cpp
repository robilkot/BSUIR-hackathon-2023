#include <iostream>
#include <vector>
#include <string>
#include<fstream>
#include<regex>

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

class Question
{
public:
    Difficulty difficulty = Difficulty::MIDDLE;
    Subject subject = Subject::NONCLASSIFIED;

    pair<string, string> task{ "Empty question", "" };

};


class TestQuestion : Question
{


public:

    vector<pair<string, string>> options{ { "", "" }, { "", "" } };
    unsigned short correctAnswer = 0;


    bool isAnswerRight(const unsigned short& selectedAnswer) {
        return selectedAnswer == correctAnswer;
    }
};

class OpenQuestion : Question
{
    string correctAnswer = "Empty correct answer";

    float getAnswerCorrentness(string answer) {
        // Тут должна быть хуйня из питона которая сравнивает строки по значению
    }
};


struct Set {

    Question question;
    TestQuestion testquestion;
    OpenQuestion openquestion;

};

void read(vector<Set>& test) {

    bool correct = false,
        only_pic = false,
        photo = false, 
        need = false;
    string path = "input.txt";
    ifstream file(path);
    regex check_1("([(]{1}[1-3]{1}[)]{1})");
    regex check_2("([a-zA-Z]{1}[:]{1}[\\\\]{1})");
    smatch check;
    if (file.is_open()) {
        string temp, buf;
        unsigned short j = -1, i = -1;
        while (getline(file, temp)) {
            
            if (temp == "HISTORY" || temp == "MATH" || temp == "RPIIS" ) {
                need = false;
                only_pic = false;
                buf = "";
                i++, j = -1;
                test.resize(i + 1);
                
                if (temp == "HISTORY") test[i].question.subject = Subject::HISTORY;
                else if (temp == "RPIIS") test[i].question.subject = Subject::RPIIS;
                else if (temp == "MATH") test[i].question.subject = Subject::MATH;
                
                
            }
            else if (regex_search(temp, check, check_1)) {
                if (need == true) {
                    only_pic = false;
                    buf = "";
                    need = false;
                    j = -1;
                    i++;
                    test.resize(i + 1);
                }
                
                if (check.str() == "(1)")test[i].question.difficulty = Difficulty::EASY;
                else if (check.str() == "(2)")test[i].question.difficulty = Difficulty::MIDDLE;
                else if (check.str() == "(3)") test[i].question.difficulty = Difficulty::HARD;
                
                test[i].question.task.first = temp;

            }

            else if (regex_search(temp, check, check_2)) {
                
                if (photo == false && buf.empty()) {
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
                        test[i].testquestion.correctAnswer = j;
                        correct = false;
                    }
                    test[i].testquestion.options.resize(j + 1);
                    if (j == 0) {
                        test[i].testquestion.options[j].second = buf;
                        j++;
                        test[i].testquestion.options.resize(j + 1);
                    }
                    test[i].testquestion.options[j].second = temp;
                }
                
               
            }
            else if (temp == "*") correct = true;
           
            else if (temp.empty()) continue;
            else {


                if (photo == true) {
                    test[i].question.task.second = buf;
                    photo = false;
                }


                need = true;
                j++;
                test[i].testquestion.options.resize(j + 1);
                test[i].testquestion.options[j].first = temp;
                
               

                if (correct == true) {
                    test[i].testquestion.correctAnswer =j;
                    correct = false;
                }



            }
            
        }
        file.close();
    }
}



void save(vector<Set>& test) {
    string path = "inp.txt";
    ofstream file(path);
    if (file.is_open()) {
        for (const auto& currentQuestion : test) {

            switch (currentQuestion.question.subject) {
            case Subject::HISTORY: file << "HISTORY" << endl; break;
            case Subject::RPIIS: file << "RPIIS" << endl; break;
            case Subject::MATH: file << "MATH" << endl; break;
            }
            file << currentQuestion.question.task.first << endl;
            if (!currentQuestion.question.task.second.empty()) file << currentQuestion.question.task.second << endl;
            unsigned short j = 0;
            for (const auto& option : currentQuestion.testquestion.options) {
                if (currentQuestion.testquestion.correctAnswer == j) file << "*" << endl;
                if (option.first.empty()) file << option.second << endl;
                else if (option.second.empty()) file << option.first << endl;
                else file << option.first << endl << option.second << endl;
                j++;
            }

        }
        file.close();
    }
}

int main() {
    setlocale(LC_ALL, "Russian");
    vector<Set> test;
    read(test);
    /*for (int i = 0; i < test.size(); i++) {
       if (test[i].question.difficulty == Difficulty::EASY)cout << "1" << endl;
       else if (test[i].question.difficulty == Difficulty::MIDDLE)cout << "2" << endl;
       else cout << "3" << endl;
       cout << test[i].question.task.first<<"\t";
       if (!test[i].question.task.second.empty())  cout << test[i].question.task.second << endl;
       else cout << endl;
       for (int j = 0; j < test[i].testquestion.options.size(); j++) {
           if (test[i].testquestion.correctAnswer == j) cout << "Correct answer : ";
           if (!test[i].testquestion.options[j].first.empty())cout << test[i].testquestion.options[j].first << endl;
           if (!test[i].testquestion.options[j].second.empty())cout << test[i].testquestion.options[j].second << endl;
       }
    }*/ //SHOWING
    save(test);
    return 0;
}