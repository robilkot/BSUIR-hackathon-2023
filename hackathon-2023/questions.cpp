#include <iostream>
#include <vector>
#include <string>

using namespace std;

enum class Difficulty {
    EASY,
    MIDDLE,
    HARD
};

enum class Subject {
    NONSPECIFIED,
    CALCULUS,
    HISTORY
};

class Question
{
    public:
    Difficulty difficulty = Difficulty::MIDDLE;
    Subject subject = Subject::NONSPECIFIED;

    pair<string, string> task{ "Empty question", "" };

    Question(Difficulty difficulty, Subject subject, string task, string photoPath) {
        this->difficulty = difficulty;
        this->subject = subject;
        this->task.first = task;
        this->task.second = photoPath;
    }
};


class TestQuestion : Question
{
    vector<pair<string, string>> options{ { "Empty answer 1", "" }, { "Empty answer 2", "" } };
    vector<pair<string, string>>::iterator correctAnswer = options.begin();

public:
    TestQuestion(Difficulty difficulty, Subject subject, string task, string photoPath, vector<pair<string, string>> options, vector<pair<string, string>>::iterator correctAnswer): Question(difficulty, subject, task, photoPath) {
        this->options = options;
        this->correctAnswer = correctAnswer;
    }
    
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
//
//
//int main() {
//    vector<pair<string, string>> options = { {"No u", "C:\\photo2.png"} , {"Ur mom", "C:\\photo3.png"} };
//
//    TestQuestion que(Difficulty::EASY, Subject::CALCULUS, "Fuck ur mom", "C:\\photo.png", options, options.begin() + 1);
//
//    cout << que.isAnswerRight(options.begin());
//    cout << que.isAnswerRight(options.begin() + 1);
//}