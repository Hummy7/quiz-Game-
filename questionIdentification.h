//Header Guard

#ifndef QUESTIONIDENTIFICATION_H
#define QUESTIONIDENTIFICATION_H

#include <vector>
#include <fstream>
#include <iostream>
#include <string>

namespace questionIdentification
{   
    int g_scoreOfPlayer{};

    class Question
    {
        private:
            std::string questions;
            std::string answer;
            
        public:
            Question(std::string& ques, std::string& ans);
            
            std::string getQuestion(){return questions;};
            std::string getAnswer(){return answer;};
    };

    Question::Question(std::string& ques, std::string& ans)
    {
        questions = ques;
        answer = ans;
    }

    bool openFile(std::ifstream& quesFile)
    {
        std::string fileName;

        std::cout << "\nAdd .txt at the end of your filename.\n";
        std::cout << "Filename: ";
        std::getline(std::cin >> std::ws, fileName);
        
        //ifstream QuestionData;
        quesFile.open(fileName);
        
        if (!quesFile.is_open())
        {
             std::cout << "Could not find database." << '\n';
             return true;
        }
           
        else
        {
            std::cout << "Database sucessfully accessed!" << '\n';
            return false;
        }
            
    }

    void fillVector(std::vector <Question>& newQuestionList, std::ifstream& queFile, int numQues)
    {
        std::string questions;
        std::string answer;
        
        for (int i = 0; i < numQues; i++)
        {
            std::getline(queFile >> std::ws, questions);
            std::getline(queFile >> std::ws, answer);
    
            Question newQuestion(questions, answer);
            newQuestionList.push_back(newQuestion);
        }
    }

    void printVector(std::vector <Question>& newQuestionList, int questionNum)
    {
        std::string choice;

        for(int i = 0; i < questionNum; i++)
        {
            std::cout << "\nQuestion #" << i+1 << '\n';
            std::cout <<  newQuestionList[i].getQuestion() << '\n';
            std::cout << "Choose answer: ";
            std::getline(std::cin >> std::ws, choice);

            if (choice == newQuestionList[i].getAnswer())
            {
                std::cout << "\nYou get the right answer";
                g_scoreOfPlayer++;
            }

            else
            {
                std::cout << "\nYou get the wrong answer";
            }
        }
    }

    int main()
    {
        std::ifstream questionFile;
        std::vector<Question> questionList;
        int numberOfQuestion{}; //responsible to hold the value that the user input on how many question does the text file had
        
        std::cout << "Number of Questions: ";
        std::cin >> numberOfQuestion;

        //If openfile return true it means the user input is wrong if return false then it was write
        while (openFile(questionFile))
        {
            openFile(questionFile);
        }

        fillVector(questionList, questionFile, numberOfQuestion);
        printVector(questionList, numberOfQuestion);
    }
}

#endif