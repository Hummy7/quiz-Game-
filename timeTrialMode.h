//Header guards
#ifndef TIMETRIALMODE_H
#define TIMETRIALMODE_H

#include <iostream>
#include <chrono>
#include <ctime>
#include <conio.h> 
#include <windows.h> //for essential::gotoXY function
#include <vector>
#include <fstream> //for file handling
#include <string>
#include "questionMultipleChoice.h"
#include "essential.h"
#include <random>

namespace timeTrialModes
{   
    class TimeTrialMode
    {
    public:
        std::ifstream questionFile;
        std::vector<questionMCQ::Question> questionList;

        questionMCQ::fileDoing gettingFile;

        double maxtime { 65 };
        int quesNum { 0 };
        int index { 0 };
        int playerScore{};
        char a;

        void startQuiz(void (*menuAccessed)(void))
        {   
            system("cls");
            time_t startTime, currentTime;
            int remainingTime;

            startTime = time(NULL);

            getQuestion();

            do
            {
                currentTime = time(NULL);
                remainingTime = maxtime - difftime(currentTime, startTime);

                essential::gotoXY(69, 3);
                //output the reaming time
                std::cout << "Time remaining: " << remainingTime << " seconds\r" << std::flush;
                Sleep(1);

                if (quesNum == index)
                {
                    system("cls");

                    quesNum++;

                    essential::ebod();
                    essential::borderTwo();

                    essential::gotoXY(23, 5);
                    std::cout << "Question # " << quesNum << '\n';
                    essential::gotoXY(23, 7);
                    std::cout << questionList[index].getQuestion();
                    essential::gotoXY(23, 9);
                    std::cout << "A. " << questionList[index].getOptionOne() << '\n';
                    essential::gotoXY(23, 10);
                    std::cout << "B. " << questionList[index].getOptionTwo() << '\n';
                    essential::gotoXY(23, 11);
                    std::cout << "C. " << questionList[index].getOptionThree() << '\n';
                    essential::gotoXY(23, 12);
                    std::cout << "D. " <<questionList[index].getOptionFour() << '\n';
                    essential::gotoXY(23, 14);
                    std::cout << "Selecdt choices between (a - d): ";
                    essential::gotoXY(23, 15);
                    std::cout << "Press enter to skip";
                }

                //kbhit function detect if the user input something
                if ( _kbhit() )
                {
                    a = _getch();

                    essential::gotoXY(56, 17);
                    std::cout << a;

                    //if the user press enter the program will consider it as skipped questioned
                    if(int(a)==13)
                    {
                        essential::gotoXY(55, 17);
                        std::cout << "You skipped this Question";
                    } 

                    else 
                    {
                        if( a == questionList[index].getAnswer())
                        {
                            essential::gotoXY(55, 17);
                            std::cout << "Congratulation You selected right option";
                            playerScore++; //This will increment if the player get the correct answer
                        } 

                        else 
                        {
                            essential::gotoXY(55, 17);
                            std::cout << "You selected wrong option.";
                        }
                    }

                    _getch();
                    index++; 
                }

            }while(remainingTime != 0 && index < gettingFile.askUserQues); //if the remainingtime == 0 and the index reach the numeber of question that the user want the program will stop

            if (remainingTime == 0) 
            {   
                system("cls");
                essential::gameOverScreen(menuAccessed);
            } 

            else if (index == gettingFile.askUserQues)
            {
                system("cls");
                essential::resultScreen(menuAccessed);
            }
        }

        void getQuestion()
        {
            while (gettingFile.openFile(questionFile))
            {
                gettingFile.openFile(questionFile);
            }
            gettingFile.fillVector(questionList, questionFile);
        }
    };
} 

#endif