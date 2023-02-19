#include <iostream>
#include <vector>
#include <string>
#include<fstream>


using namespace std;

struct Set {

    Question question;
    TestQuestion testquestion;
    OpenQuestion openquestion;

};

void read(vector<Set>& test) {

    bool correct = false;

    string path = "input.txt";
    ifstream file(path);

    if (file.is_open()) {
        string temp;
        size_t j = 0, i = -1;
        while (getline(file, temp)) {

            if (temp == "HISTORY" || temp == "CALCULUS" || temp == "NONSPECIFIED") {
                i++;
                j = 0;
                test.resize(i + 1);
                if (temp == "HISTORY") test[i].question.subject = Subject::HISTORY;
                else if (temp == "CALCULUS") test[i].question.subject = Subject::CALCULUS;
                else if (temp == "NONSPECIFIED") test[i].question.subject = Subject::NONSPECIFIED;
                getline(file, temp);
                if (temp == "(1)")test[i].question.difficulty = Difficulty::EASY;
                else if (temp == "(2)")test[i].question.difficulty = Difficulty::MIDDLE;
                else if (temp == "(3)") test[i].question.difficulty = Difficulty::HARD;
                getline(file, temp);
                test[i].question.task.first = temp;
            }
            else if (temp[0] == '(') {

                if (test[i].testquestion.options.size() != 0) {
                    j = 0;
                    i++;
                    test.resize(i + 1);
                }

                if (temp == "(1)")test[i].question.difficulty = Difficulty::EASY;
                else if (temp == "(2)")test[i].question.difficulty = Difficulty::MIDDLE;
                else if (temp == "(3)") test[i].question.difficulty = Difficulty::HARD;
                getline(file, temp);
                test[i].question.task.first = temp;

            }

            else if (temp[0] == '[') {
                getline(file, temp);
                test[i].question.task.second = temp;
            }
            else if (temp[0] == '*') correct = true;

            else {

                test[i].testquestion.options.resize(j + 1);
                if (test[i].testquestion.options[j].first.empty()) test[i].testquestion.options[j].first = temp;
                else {
                    test[i].testquestion.options[j].second = temp;
                    j++;
                }
                if (correct == true) {
                    test[i].testquestion.correctAnswer = test[i].testquestion.options.begin() + j;
                    correct = false;
                }
            }
        }
        file.close();
    }
}