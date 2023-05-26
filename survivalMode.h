//Header guards
#ifndef SURVIVALMODE_H
#define SURVIVALMODE_H

#include <iostream>
#include <chrono>
#include <ctime>
#include <conio.h> 
#include <windows.h> //for essential::gotoXY function
#include <vector>
#include <fstream> //for file handling
#include <string>
#include "questionMultipleChoice.h"
#include "userGameHistory.h"

namespace survivalModes
{   
    class SurvivalMode
    {
    public:
        std::ifstream questionFile;
        std::vector<questionMCQ::Question> questionList;

        questionMCQ::fileDoing getFile;

        gameHistory::StudentGameHistory sg;

        int quesNum { 0 };
        int index { 0 };
        char a{};
        int playerScore{};
        int isGameOver = true;
        int life = 4;

        std::vector <std::string> lives = {"X", "X", "X", "X"};

        void gameOVerScreen(void (*func)(void));
        void resultScreen(void (*func)(void));

        void startQuiz(void (*funcs)(void))
        {   
            start();

            sg.isSurvivalMode = true;

            do
            {
                if (quesNum == index)
                {
                    system("cls");

                    quesNum++;

                   essential::ebod();
                    essential::borderTwo();

                    essential::gotoXY(69, 3);
                    SetConsoleTextAttribute(h, 5);
                    //This output the reaming lives of the player
                    std::cout << "Lives: " << lives[0] << lives[1] << lives[2] << lives[3];
                    
                    essential::gotoXY(23, 5);
                    SetConsoleTextAttribute(h, 15);
                    std::cout << "Question # " << quesNum << '\n';
                    essential::gotoXY(23, 7);
                    SetConsoleTextAttribute(h, 1);
                    std::cout << questionList[index].getQuestion();
                    essential::gotoXY(23, 9);
                    SetConsoleTextAttribute(h, 7);
                    std::cout << "A. " << questionList[index].getOptionOne() << '\n';
                    essential::gotoXY(23, 10);
                    SetConsoleTextAttribute(h, 7);
                    std::cout << "B. " << questionList[index].getOptionTwo() << '\n';
                    essential::gotoXY(23, 11);
                    SetConsoleTextAttribute(h, 7);
                    std::cout << "C. " << questionList[index].getOptionThree() << '\n';
                    essential::gotoXY(23, 12);
                    SetConsoleTextAttribute(h, 7);
                    std::cout << "D. " <<questionList[index].getOptionFour() << '\n';
                    essential::gotoXY(23, 14);
                    SetConsoleTextAttribute(h, 14);
                    std::cout << "Select choices between (a -d): ";
                }

                //kbhit function detect if the user input something
                if ( _kbhit() )
                {
                    a = _getch();

                    essential::gotoXY(56, 14);
                    std::cout << a;
                    
                    if( a == questionList[index].getAnswer())
                    {
                        essential::gotoXY(55, 17);
                        SetConsoleTextAttribute(h, 2);
                        std::cout << "Congratulation You selected right option";
                        playerScore += 10; //This will increment if the player get the correct answer
                    } 

                    else 
                    {
                        essential::gotoXY(55, 17);
                        SetConsoleTextAttribute(h, 4);
                        std::cout << "You selected wrong option.";
                        lives[index].erase(); //if the player choose the wrong answer the lives will be erase
                        --life;
                    }

                    _getch();
                    index++; 
                }
            }while(life != 0 && index < getFile.askUserQues); //if the remainingtime == 0 and the index reach the numeber of question that the user want the program will stop

            if (life == 0)
            {   
                system("cls");
                sg.writeStudentData(playerScore);
                gameOVerScreen(funcs);
                
            }

            else if (index == getFile.askUserQues)
            {
                system("cls");
                sg.writeStudentData(playerScore);
                resultScreen(funcs);
            }
        }

        void start()
        {   
            getFile.openFile(questionFile);
            
            getFile.fillVector(questionList, questionFile);
        }

        HANDLE h = GetStdHandle(STD_OUTPUT_HANDLE);
    };

    void SurvivalMode::gameOVerScreen(void (*func)(void))
    {
        essential::gotoXY(35, 10);
        SetConsoleTextAttribute(h, 15);
        std::cout << "Student Name: " << gameHistory::g_studentName;
        essential::gotoXY(70, 10);
        SetConsoleTextAttribute(h, 15);
        std::cout << "Student No. " << gameHistory::g_studentNumber;
        essential::gotoXY(35, 13);
        SetConsoleTextAttribute(h, 15);
        std::cout << "Your score ---> " << playerScore;
        essential::gotoXY(70, 13);
        SetConsoleTextAttribute(h, 15);
        std::cout << sg.getFeedback(playerScore);

        //call game over ascii art and also the border
        essential::asciiArtGameOver(func);
    }

    void SurvivalMode::resultScreen(void (*func)(void))
    {   
        essential::gotoXY(35, 10);
        SetConsoleTextAttribute(h, 15);
        std::cout << "Student Name: " << gameHistory::g_studentName;
        essential::gotoXY(70, 10);
        SetConsoleTextAttribute(h, 15);
        std::cout << "Student No. " << gameHistory::g_studentNumber;
        essential::gotoXY(35, 13);
        SetConsoleTextAttribute(h, 15);
        std::cout << "Your score ---> " << playerScore;
        essential::gotoXY(70, 12);
        SetConsoleTextAttribute(h, 15);
        std::cout << sg.getFeedback(playerScore);
        essential::gotoXY(70, 14);
        SetConsoleTextAttribute(h, 15);
        std::cout << "Remaining Life: " << life; 

        //call result ascii art and also the border
        essential::asciiArtResult(func);
    }
} 

#endif