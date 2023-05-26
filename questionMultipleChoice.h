//Header Guard

#ifndef QUESTIONMCQ_H
#define QUESTIONMCQ_H

#include <vector>
#include <fstream>
#include <iostream>
#include <string>
#include <windows.h>
#include <conio.h> 
#include "essential.h"
#include <random>
#include <cctype>
#include "userGameHistory.h"

namespace questionMCQ
{   
    int g_scoreOfPlayer{};

    class Question
    {
    private:
        std::string questions;
        std::string optionOne;
        std::string optionTwo;
        std::string optionThree;
        std::string optionFour;
        char answer;
            
    public:
        Question(std::string& ques, std::string& opOne, std::string& opTwo, std::string& opThree, std::string& opFour, char ans);

        std::string getQuestion(){return questions;};
        std::string getOptionOne(){return optionOne;};
        std::string getOptionTwo(){return optionTwo;};
        std::string getOptionThree(){return optionThree;};
        std::string getOptionFour(){return optionFour;};
        char getAnswer(){return answer;};
    };

    Question::Question(std::string& ques, std::string& opOne, std::string& opTwo, std::string& opThree, std::string& opFour, char ans)
    {
        questions = ques;
        optionOne = opOne;
        optionTwo = opTwo;
        optionThree = opThree;
        optionFour = opFour;
        answer = ans;
    }

    class fileDoing
    {
    public:
        int askUserQues{};
        int playerScore{};
        int isTrue {};

        gameHistory::StudentGameHistory sg;

        bool openFile(std::ifstream& quesFile)
        {
            std::string fileName;

            system("cls");
            essential::gotoXY(23, 7);
            SetConsoleTextAttribute(h, 15);
            std::cout << "How many questions does file have: ";
            std::cin >> askUserQues;

            //detect if user input is an integer or not and also validate if user input the right question dami
            while ( !std::cin || askUserQues < 6 )
            {
                system("cls");
                std::cin.clear();
                std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                essential::gotoXY(23, 7);
                SetConsoleTextAttribute(h, 15);
                std::cout << "How many questions does file have: ";
                std::cin >> askUserQues;
            }
        
            do
            {
                system("cls");
                essential::gotoXY(23, 5);
                SetConsoleTextAttribute(h, 15);
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
                SetConsoleTextAttribute(h, 15);
                std::cout << "Could not find database. . . " << '\n';
                return true;
            }
                    
            else
            {   
                essential::gotoXY(23, 6); 
                Sleep(1000);
                SetConsoleTextAttribute(h, 15);
                std::cout << "Database sucessfully accessed!" << '\n';
                return false;
            }
        }

        void fillVector(std::vector <Question>& newQuestionList, std::ifstream& queFile)
        {
            std::string questions;
            std::string optionOne;
            std::string optionTwo;
            std::string optionThree;
            std::string optionFour;
            char answer;
            
            for (int i = 0; i < askUserQues; i++)
            {
                std::getline(queFile >> std::ws, questions);
                std::getline(queFile >> std::ws, optionOne);
                std::getline(queFile >> std::ws, optionTwo);
                std::getline(queFile >> std::ws, optionThree);
                std::getline(queFile >> std::ws, optionFour);
                queFile >> answer; 
                queFile.ignore(1000, '\n');

                Question newQuestion(questions, optionOne, optionTwo, optionThree, optionFour, answer);
                newQuestionList.push_back(newQuestion);

                //random questions
                std::shuffle(newQuestionList.begin(), newQuestionList.end(), essential::randomingQuestion());
            }
        }

        void printVectorOne(std::vector <Question>& newQuestionList, void (*menu)(void))
        {   
            char choice;
 
            int questionNumber{};
            int i{};
            char a;
            
            do 
            {
                if ( questionNumber == i )
                {
                    system("cls");

                    questionNumber++;

                    generateQuestion(questionNumber, i, newQuestionList, true);
                }

                if ( _kbhit() )
                {
                    a = _getch();

                    // essential::gotoXY(56, 17);
                    // std::cout << a;

                    if(int(a)==13)
                    {   
                        essential::gotoXY(55, 17);
                        SetConsoleTextAttribute(h, 7);
                        std::cout << "You skipped this Question";
                    } 

                    else 
                    {
                        if( a == newQuestionList[i].getAnswer())
                        {
                            essential::gotoXY(55, 17);
                            SetConsoleTextAttribute(h, 4);
                            std::cout << "Congratulation You selected right option";
                            g_scoreOfPlayer++;
                        } 

                        else 
                        {
                            essential::gotoXY(55, 17);
                            SetConsoleTextAttribute(h, 2);
                            std::cout << "You selected wrong option.";
                        }
                    }
                    _getch();
                    i++; 
                }
            }while( i < askUserQues );

            if ( i == askUserQues )
            {   
                system("cls");
                sg.writeStudentData(g_scoreOfPlayer);
                resultScreen(menu);
                system("cls");
            }
        }

        void start(void (*menu)(void))
        {   
            std::ifstream questionFile;
            std::vector <Question> questionList; //vector to tore the text from the file
            sg.isClassicMode = true;
            //If openfile return true it means the user input is wrong if return false then it was write
            openFile(questionFile);

            fillVector(questionList, questionFile);
            printVectorOne(questionList, menu);
        }
    
        void generateQuestion(int ques, int in, std::vector <Question>& v, bool isTrue)
        {
            system("cls");

            essential::ebod();
            essential::borderTwo();

            SetConsoleTextAttribute(h, 15);
            essential::gotoXY(23, 5);
            std::cout << "Question # " << ques << '\n';
            SetConsoleTextAttribute(h, 1);
            essential::gotoXY(23, 7);
            std::cout << v[in].getQuestion();
            SetConsoleTextAttribute(h, 7);
            essential::gotoXY(23, 9);
            std::cout << "A. " << v[in].getOptionOne() << '\n';
            essential::gotoXY(23, 10);
             SetConsoleTextAttribute(h, 7);
            std::cout << "B. " << v[in].getOptionTwo() << '\n';
            SetConsoleTextAttribute(h, 7);
            essential::gotoXY(23, 11);
            std::cout << "C. " << v[in].getOptionThree() << '\n';
            SetConsoleTextAttribute(h, 7);
            essential::gotoXY(23, 12);
            std::cout << "D. " <<v[in].getOptionFour() << '\n';
            SetConsoleTextAttribute(h, 14);
            essential::gotoXY(23, 14);
            std::cout << "Select choices between (a - d): ";

            if (isTrue)
            {   
                essential::color(essential::YELLOW);
                SetConsoleTextAttribute(h, 14);
                essential::gotoXY(23, 15);
                std::cout << "Press enter to skip";
            }
            
            else
            {
               //empty 
            }
        }

        HANDLE h = GetStdHandle(STD_OUTPUT_HANDLE);

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

            //call result ascii art and also the border
            essential::asciiArtResult(func);
        }
    };
}

#endif