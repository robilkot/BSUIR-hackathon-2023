#include <iostream>
#include <vector>
#include <string>
#include<fstream>


using namespace std;

enum class Difficulty {
    EASY,
    MIDDLE,
    HARD
};

enum class Subject {
    RPIIS,
    MATH,
    HISTORY
};

class Question
{
public:
    Difficulty difficulty = Difficulty::MIDDLE;
    Subject subject = Subject::RPIIS;

    pair<string, string> task{ "Empty question", "" };

};


class TestQuestion : Question
{


public:

    vector<pair<string, string>> options{ { "", "" }, { "", "" } };
    vector<pair<string, string>>::iterator correctAnswer = options.begin();


    bool isAnswerRight(const vector<pair<string, string>>::iterator& selectedAnswer) {
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

    bool correct = false;

    bool only_pic = false;

    string path = "input.txt";
    ifstream file(path);

    if (file.is_open()) {
        string temp;
        size_t j = -1, i = -1;
        while (getline(file, temp)) {

            if (temp == "HISTORY" || temp == "MATH" || temp == "RPIIS") {
                i++, j = -1;
                test.resize(i + 1);
                only_pic = true;
                if (temp == "HISTORY") test[i].question.subject = Subject::HISTORY;
                else if (temp == "RPIIS") test[i].question.subject = Subject::RPIIS;
                else if (temp == "MATH") test[i].question.subject = Subject::MATH;
                getline(file, temp);
                if (temp == "(1)")test[i].question.difficulty = Difficulty::EASY;
                else if (temp == "(2)")test[i].question.difficulty = Difficulty::MIDDLE;
                else if (temp == "(3)") test[i].question.difficulty = Difficulty::HARD;
                getline(file, temp);
                test[i].question.task.first = temp;
            }
            else if (temp[0] == '(') {

                if (test[i].testquestion.options.size() != 0) {

                    j = -1;
                    i++;
                    test.resize(i + 1);
                    only_pic = true;
                }

                if (temp == "(1)")test[i].question.difficulty = Difficulty::EASY;
                else if (temp == "(2)")test[i].question.difficulty = Difficulty::MIDDLE;
                else if (temp == "(3)") test[i].question.difficulty = Difficulty::HARD;
                getline(file, temp);
                test[i].question.task.first = temp;

            }

            else if (temp == "[") {
                getline(file, temp);
                test[i].question.task.second = temp;
            }
            else if (temp == "*") correct = true;
            else if (temp == "[[") {

                if (only_pic == true) {

                    j++;
                    test[i].testquestion.options.resize(j + 1);

                }
                getline(file, temp);
                test[i].testquestion.options[j].second = temp;



                //Здесь я приваиваю
                if (correct == true) {
                    test[i].testquestion.correctAnswer = test[i].testquestion.options.begin() + j;
                    
                    // DEBUG
                    cout << "Read corrent answer " << (*(test[i].testquestion.correctAnswer)).first << "\n";

                    correct = false;
                }



            }
            else if (temp.empty()) continue;
            else {
                j++;
                test[i].testquestion.options.resize(j + 1);
                test[i].testquestion.options[j].first = temp;
                only_pic = false;



                //Здесь я присваиваю

                if (correct == true) {
                    test[i].testquestion.correctAnswer = test[i].testquestion.options.begin() + j;

                    // DEBUG
                    cout << "Read corrent answer " << (*(test[i].testquestion.correctAnswer)).first << "\n";

                    correct = false;
                }



            }

        }
        file.close();
    }
    else {
        cout << "fuck\n";
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
            default: file << "NONSPECIFIED" << endl; break;
            }

            switch (currentQuestion.question.difficulty) {
            case Difficulty::EASY: file << "(" << 1 << ")" << endl; break;
            case Difficulty::MIDDLE: file << "(" << 2 << ")" << endl; break;
            case Difficulty::HARD: file << "(" << 3 << ")" << endl; break;
            }

            file << currentQuestion.question.task.first << endl;
            if (!currentQuestion.question.task.second.empty()) file << "[" << endl << currentQuestion.question.task.second << endl;

            for (const auto& option : currentQuestion.testquestion.options) {

                cout << option.first << endl;
                if (option == *(currentQuestion.testquestion.correctAnswer)) file << "*" << endl;

               /* if (test[i].testquestion.options[j].first.empty()) file << "[[" << endl << test[i].testquestion.options[j].second << endl;
                else if (test[i].testquestion.options[j].second.empty()) file << test[i].testquestion.options[j].first << endl;
                else file << test[i].testquestion.options[j].first << endl << "[[" << test[i].testquestion.options[j].second << endl;*/

            }

        }
        file.close();
    }
}

int main() {
    setlocale(LC_ALL, "Russian");
    vector<Set> test;
    read(test);



    save(test);
    return 0;
}