#include <iostream>
#include <vector>
#include <string>
#include <QString>

#pragma once

//#include "comparison.h"

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

enum class Questions {
    TEST,
    OPEN
};

class Question
{
    public:
    Difficulty difficulty = Difficulty::MIDDLE;
    Subject subject = Subject::NONSPECIFIED;

    pair<QString, QString> task{ "Empty question", "" };

    Question(Difficulty difficulty, Subject subject, QString task, QString photoPath) {
        this->difficulty = difficulty;
        this->subject = subject;
        this->task.first = task;
        this->task.second = photoPath;
    }
    Question(){}
};


class TestQuestion : public Question
{
public:
    vector<pair<QString, QString>> options{ { "Empty answer 1", "" }, { "Empty answer 2", "" } };
    size_t correctAnswer = 0;

    TestQuestion(){}
    TestQuestion(Difficulty difficulty, Subject subject, QString task, QString photoPath, vector<pair<QString, QString>> options, size_t correctAnswer): Question(difficulty, subject, task, photoPath) {
        this->options = options;
        this->correctAnswer = correctAnswer;
    }

    
    bool isAnswerRight(const size_t& selectedAnswer) {
        return selectedAnswer == correctAnswer;
    }
};

class OpenQuestion : public Question
{
public:
    OpenQuestion(){}
    string correctAnswer = "Empty correct answer";
    
    float getAnswerCorrentness(string answer) {
        //return meaningSimilarity(answer, correctAnswer);
        return 0.5;
    }
};

class TestElement
{
public:
    OpenQuestion openQuestion;
    TestQuestion testQuestion;

    Questions questions = Questions::TEST;
};
