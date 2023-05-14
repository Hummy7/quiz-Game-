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

namespace survivalModes
{   
    class SurvivalMode
    {
    public:
        std::ifstream g_questionFile;
        std::vector<questionMCQ::Question> g_questionList;

        questionMCQ::fileDoing getFile;

        int quesNum { 0 };
        int index { 0 };
        char a{};
        int playerScore{};
        int isGameOver = true;
        int life = 4;

        std::vector <std::string> lives = {"X", "X", "X", "X"};

        void startQuiz(void (*funcs)(void))
        {   
            start();

            do
            {
                if (quesNum == index)
                {
                    system("cls");

                    quesNum++;

                    essential::ebod();
                    essential::borderTwo();

                    essential::gotoXY(69, 3);
                    //This output the reaming lives of the player
                    std::cout << "Lives: " << lives[0] << lives[1] << lives[2] << lives[3];
                    
                    essential::gotoXY(23, 5);
                    std::cout << "Question # " << quesNum << '\n';
                    essential::gotoXY(23, 7);
                    std::cout << g_questionList[index].getQuestion();
                    essential::gotoXY(23, 9);
                    std::cout << "A. " << g_questionList[index].getOptionOne() << '\n';
                    essential::gotoXY(23, 10);
                    std::cout << "B. " << g_questionList[index].getOptionTwo() << '\n';
                    essential::gotoXY(23, 11);
                    std::cout << "C. " << g_questionList[index].getOptionThree() << '\n';
                    essential::gotoXY(23, 12);
                    std::cout << "D. " <<g_questionList[index].getOptionFour() << '\n';
                    essential::gotoXY(23, 14);
                    std::cout << "Select choices between (a -d): ";
                }

                //kbhit function detect if the user input something
                if ( _kbhit() )
                {
                    a = _getch();

                    essential::gotoXY(56, 14);
                    std::cout << a;
                    
                    if( a == g_questionList[index].getAnswer())
                    {
                        essential::gotoXY(23, 16);
                        std::cout << "Congratulation You selected right option";
                        playerScore++; //This will increment if the player get the correct answer
                    } 

                    else 
                    {
                        essential::gotoXY(23, 16);
                        std::cout << "You selected wrong option.";
                        lives[index].erase(); //if the player choose the wrong answer the lives will be erase
                        --life;
                    }

                    _getch();
                    index++; 
                }
            }while(life != 0); //if the remainingtime == 0 and the index reach the numeber of question that the user want the program will stop

            if (life == 0)
            {   
                system("cls");
                essential::gameOverScreen(funcs);
            }
            //TODO: need to fix problem not doing what i want
        }

        void start()
        {   
            while (getFile.openFile(g_questionFile))
            {
                getFile.openFile(g_questionFile);
            }
            getFile.fillVector(g_questionList, g_questionFile);
        }
    };
} 

#endif