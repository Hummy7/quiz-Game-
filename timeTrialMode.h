//Header guards
#ifndef TIMETRIALMODE_H
#define TIMETRIALMODE_H

#include <iostream>
#include <chrono>
#include <ctime>
#include <conio.h> 
#include <windows.h> //for gotoxy function
#include <vector>
#include <fstream> //for file handling
#include <string>
#include "questionMultipleChoice.h"

namespace timeTrialModes
{   
    class TimeTrialMode
    {
    public:
        std::ifstream questionFile;
        std::vector<questionMCQ::Question> questionList;

        int numOfQuestion;
        double maxtime { 60 };
        int quesNum { 0 };
        int index { 0 };
        int playerScore{};
        char a;

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
            system("cls");
            time_t startTime, currentTime;
            int remainingTime;

            startTime = time(NULL);

            //ask the user how many question does the txt file have
            gotoXY(23, 5);
            std::cout << "How many questions does file have: ";
            std::cin >> numOfQuestion;

            getQuestion();

            do
            {
                currentTime = time(NULL);
                remainingTime = maxtime - difftime(currentTime, startTime);

                gotoXY(69, 3);
                //output the reaming time
                std::cout << "Time remaining: " << remainingTime << " seconds\r" << std::flush;
                Sleep(1);

                if (quesNum == index)
                {
                    system("cls");

                    quesNum++;

                    gotoXY(23, 5);
                    std::cout << "Question # " << quesNum << '\n';
                    gotoXY(23, 7);
                    std::cout << questionList[index].getQuestion();
                    gotoXY(23, 9);
                    std::cout << "A. " << questionList[index].getOptionOne() << '\n';
                    gotoXY(23, 10);
                    std::cout << "B. " << questionList[index].getOptionTwo() << '\n';
                    gotoXY(23, 11);
                    std::cout << "C. " << questionList[index].getOptionThree() << '\n';
                    gotoXY(23, 12);
                    std::cout << "D. " <<questionList[index].getOptionFour() << '\n';
                    gotoXY(23, 14);
                    std::cout << "Selecdt choices between (a -d): ";
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
                    } 

                    else 
                    {
                        if( a == questionList[index].getAnswer())
                        {
                            gotoXY(23, 16);
                            std::cout << "Congratulation You selected right option";
                            playerScore++; //This will increment if the player get the correct answer
                        } 

                        else 
                        {
                            gotoXY(23, 16);
                            std::cout << "You selected wrong option.";
                        }
                    }

                    _getch();
                    index++; 
                }

            }while(remainingTime != 0 && index < numOfQuestion); //if the remainingtime == 0 and the index reach the numeber of question that the user want the program will stop

            if (index < numOfQuestion - 1) 
            {       
                std::cout << "Time is up. You failed to attempt all questions"<< '\n';
            } 
            //TODO: Add a gameover screen for this
        }

        void getQuestion()
        {
            
            while (questionMCQ::openFile(questionFile))
            {
                questionMCQ::openFile(questionFile);
            }
            questionMCQ::fillVector(questionList, questionFile);
        }
    };
} 

#endif