//Header guards
#ifndef SURVIVALMODE_H
#define SURVIVALMODE_H

#include <iostream>
#include <chrono>
#include <ctime>
#include <conio.h> 
#include <windows.h> //for gotoxy function
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

        int quesNum { 0 };
        int index { 0 };
        char a{};
        int playerScore{};
        int isGameOver = false;

        std::vector <std::string> lives = {"X", "X", "X", "X"};

        void gotoXY(int x, int y) 	//function to decide location of the screem
        {
            HANDLE console = GetStdHandle(STD_OUTPUT_HANDLE); 		 
            COORD CursorPosition; 
            CursorPosition.X = x; // Locates column
            CursorPosition.Y = y; // Locates Row
                
            SetConsoleCursorPosition(console,CursorPosition); // Sets position for next thing to be printed 
        }

        void startQuiz()
        {   
            start();

            do
            {
                if (quesNum == index)
                {
                    system("cls");

                    quesNum++;
                    
                    for (int x { 0 }; x < 4; ++x)
                    {
                        gotoXY(69, 3);
                        //This output the reaming lives of the player
                        std::cout << "Lives: " << lives[0] << lives[1] << lives[2] << lives[3];
                    }
                    
                    gotoXY(23, 5);
                    std::cout << "Question # " << quesNum << '\n';
                    gotoXY(23, 7);
                    std::cout << g_questionList[index].getQuestion();
                    gotoXY(23, 9);
                    std::cout << "A. " << g_questionList[index].getOptionOne() << '\n';
                    gotoXY(23, 10);
                    std::cout << "B. " << g_questionList[index].getOptionTwo() << '\n';
                    gotoXY(23, 11);
                    std::cout << "C. " << g_questionList[index].getOptionThree() << '\n';
                    gotoXY(23, 12);
                    std::cout << "D. " <<g_questionList[index].getOptionFour() << '\n';
                    gotoXY(23, 14);
                    std::cout << "Select choices between (a -d): ";
                }

                //kbhit function detect if the user input something
                if ( _kbhit() )
                {
                    a = _getch();

                    gotoXY(56, 14);
                    std::cout << a;

                    //if the user press enter the program will consider it as skipped questioned
                    if(int(a)==13)
                    {
                        gotoXY(23, 16);
                        std::cout << "You skipped this Question";
                        lives[index].erase();
                    } 

                    else 
                    {
                        if( a == g_questionList[index].getAnswer())
                        {
                            gotoXY(23, 16);
                            std::cout << "Congratulation You selected right option";
                            playerScore++; //This will increment if the player get the correct answer
                        } 

                        else 
                        {
                            gotoXY(23, 16);
                            std::cout << "You selected wrong option.";
                            lives[index].erase(); //if the player choose the wrong answer the lives will be erase
                        }
                    }

                    if (lives.empty())
                    {   
                        gotoXY(23, 17);
                        std::cout << "You have no lives sorry you lost";
                        isGameOver = true;
                        break;
                    }
                    //TODO: add gameover screen

                    _getch();
                    index++; 
                }
            }while(!isGameOver); //if the remainingtime == 0 and the index reach the numeber of question that the user want the program will stop

        }

        void start()
        {   
            while (questionMCQ::openFile(g_questionFile))
            {
                questionMCQ::openFile(g_questionFile);
            }
            questionMCQ::fillVector(g_questionList, g_questionFile);
        }
    };
} 

#endif