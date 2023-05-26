//Header Guard
#ifndef QUESTIONIDENTIFICATION_H
#define QUESTIONIDENTIFICATION_H

#include <vector>
#include <fstream>
#include <iostream>
#include <string>
#include "essential.h"
#include "userGameHistory.h"

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

    class gettingQuesFile
    {
    public:
        int questionNum;
        int inCorrectAns;

        gameHistory::StudentGameHistory sg;
        
        bool openFile(std::ifstream& quesFile)
        {
            std::string fileName;

            system("cls");
            essential::gotoXY(23, 7);
            std::cout << "How many questions does file haves: ";
            std::cin >> questionNum;

            //detect if user input is an integer or not and also validate if user input the right question dami
            while ( !std::cin || questionNum < 6 )
            {
                system("cls");
                std::cin.clear();
                std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                essential::gotoXY(23, 7);
                std::cout << "How many questions does file haves: ";
                std::cin >> questionNum;
            }
        
            do
            {
                system("cls");
                essential::gotoXY(23, 5);
                std::cout << "Add .txt at the end of your filename.";
                essential::gotoXY(23, 6);
                std::cout << "Filename: ";
                std::getline(std::cin >> std::ws, fileName);

                quesFile.open(fileName);
                
            }while( !quesFile.is_open() ); //this detect if the user input the write file name or not

            if (!quesFile.is_open())
            {   
                essential::gotoXY(23, 6); 
                Sleep(1000);
                std::cout << "Could not find database. . . " << '\n';
                return true;
            }
                    
            else
            {   
                essential::gotoXY(23, 6); 
                Sleep(1000);
                std::cout << "Database sucessfully accessed!" << '\n';
                return false;
            }
        }

        void fillVector(std::vector <Question>& newQuestionList, std::ifstream& queFile)
        {
            std::string questions;
            std::string answer;
            
            for (int i = 0; i < questionNum; i++)
            {
                std::getline(queFile >> std::ws, questions);
                std::getline(queFile >> std::ws, answer);
        
                Question newQuestion(questions, answer);
                newQuestionList.push_back(newQuestion);

                std::shuffle(newQuestionList.begin(), newQuestionList.end(), essential::randomingQuestion());
            }
        }

        void printVector(std::vector <Question>& newQuestionList, void (*menu)(void))
        {
            std::string choice;
            system("cls");
            int i;

            for(i = 0; i < questionNum; i++)
            {   
                essential::gotoXY(55, 18);
                std::cout << "Press any key to next. . . .";
                essential::gotoXY(55, 17);
                getch();
                system("cls");

                essential::ebod();
                essential::borderTwo();

                essential::gotoXY(23, 5);
                SetConsoleTextAttribute(h, 15);
                std::cout << "Question # " << i + 1;
                essential::gotoXY(23, 8);
                SetConsoleTextAttribute(h, 1);
                std::cout <<  newQuestionList[i].getQuestion();
                essential::gotoXY(23, 14);
                SetConsoleTextAttribute(h, 7);
                std::cout << "Fill Answer: ";
                std::getline(std::cin >> std::ws, choice);

                if (choice == newQuestionList[i].getAnswer())
                {   
                    essential::gotoXY(55, 17);
                    SetConsoleTextAttribute(h, 2);
                    std::cout << "Congratulation You selected right option";
                    g_scoreOfPlayer++;
                }

                else
                {   
                    essential::gotoXY(55, 17);
                    SetConsoleTextAttribute(h, 4);
                    std::cout << "You selected wrong option.";
                }
            }

            if (i == questionNum)
            {
                system("cls");
                sg.writeStudentData(g_scoreOfPlayer);
                resultScreen(menu);
            }
        }

        void start(void (*menu)(void))
        {
            std::ifstream questionFile;
            std::vector<Question> questionList;

            sg.isClassicMode = true;
            //If openfile return true it means the user input is wrong if return false then it was write
    
            openFile(questionFile);
            
            fillVector(questionList, questionFile);
            printVector(questionList, menu);
        }

        void resultScreen(void (*func)(void))
        {   
            essential::gotoXY(35, 10);
            SetConsoleTextAttribute(h, 15);
            std::cout << "Student Name: " << gameHistory::g_studentName;
            essential::gotoXY(70, 10);
            SetConsoleTextAttribute(h, 15);
            std::cout << "Student No. " << gameHistory::g_studentNumber;
            essential::gotoXY(35, 13);
            SetConsoleTextAttribute(h, 15);
            std::cout << "Your score ---> " << g_scoreOfPlayer;
            essential::gotoXY(70, 12);
            SetConsoleTextAttribute(h, 15);
            std::cout << sg.getFeedback(g_scoreOfPlayer);
            essential::gotoXY(70, 14);
            SetConsoleTextAttribute(h, 15);
            std::cout << inCorrectAns; 
            
            //call result ascii art and also the border
            essential::asciiArtResult(func);
        }
        
        HANDLE h = GetStdHandle(STD_OUTPUT_HANDLE);
    };
}

#endif