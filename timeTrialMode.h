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
#include "userGameHistory.h"

namespace timeTrialModes
{   
    class TimeTrialMode
    {
    public:
        std::ifstream questionFile;
        std::vector<questionMCQ::Question> questionList;

        questionMCQ::fileDoing gettingFile;
        gameHistory::StudentGameHistory sg;

        double maxtime { 65 };
        int quesNum { 0 };
        int index { 0 };
        char a;
        int userScore{};
        std::string feedBackLose{};
        int wrongAnswers{};

        void gameOverScreen(void (*func)(void));
        void resultScreen(void (*func)(void));

        void startQuiz(void (*menuAccessed)(void))
        {   
            system("cls");
            time_t startTime, currentTime;
            int remainingTime;

            sg.isTimeTrialMode = true;

            startTime = time(NULL);

            getQuestion();

            do
            {
                currentTime = time(NULL);
                remainingTime = maxtime - difftime(currentTime, startTime);

                essential::gotoXY(69, 3);
                //output the reaming time
                SetConsoleTextAttribute(h, 5);
                std::cout << "Time remaining: " << remainingTime << " seconds\r" << std::flush;
                Sleep(1);

                if (quesNum == index)
                {   
                    quesNum++;

                    //generating the question
                    gettingFile.generateQuestion(quesNum, index, questionList, true);
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
                        essential::color(essential::BLUE);
                        essential::gotoXY(55, 17);
                        SetConsoleTextAttribute(h, 8);
                        std::cout << "You skipped this Question";
                    } 

                    else 
                    {
                        if( a == questionList[index].getAnswer())
                        {
                            essential::gotoXY(55, 17);
                            SetConsoleTextAttribute(h, 2);
                            std::cout << "Congratulation You selected right option";
                            userScore += 10; //incrementing 10 points each correct answers
                        } 

                        else 
                        {
                            essential::gotoXY(55, 17);
                            SetConsoleTextAttribute(h, 4);
                            std::cout << "You selected wrong option.";
                            wrongAnswers++; //geting the wrong answers
                        }
                    }

                    _getch();
                    index++; 
                }

            }while(remainingTime != 0 && index < gettingFile.askUserQues); //if the remainingtime == 0 and the index reach the numeber of question that the user want the program will stop
            
            if (remainingTime == 0) 
            {   
                system("cls");
                sg.writeStudentData(userScore);
                gameOverScreen(menuAccessed);
            } 

            else if (index == gettingFile.askUserQues)
            {
                system("cls");
                sg.writeStudentData(userScore);
                resultScreen(menuAccessed);
            }
        }

        void getQuestion()
        {
            gettingFile.openFile(questionFile);
            
            gettingFile.fillVector(questionList, questionFile);
        }

        HANDLE h = GetStdHandle(STD_OUTPUT_HANDLE);
    };

    void TimeTrialMode::gameOverScreen(void (*func)(void))
    {   
        essential::gotoXY(35, 10);
        SetConsoleTextAttribute(h, 15);
        std::cout << "Student Name: " << gameHistory::g_studentName;
        essential::gotoXY(70, 10);
        SetConsoleTextAttribute(h, 15);
        std::cout << "Student No. " << gameHistory::g_studentNumber;
        essential::gotoXY(35, 13);
        SetConsoleTextAttribute(h, 15);
        std::cout << "Your score ---> " << userScore;
        essential::gotoXY(70, 13);
        SetConsoleTextAttribute(h, 15);
        std::cout << sg.getFeedback(userScore);

        //call game over ascii art and also the border
        essential::asciiArtGameOver(func);
    }

    void TimeTrialMode::resultScreen(void (*func)(void))
    {   
        essential::gotoXY(35, 10);
        SetConsoleTextAttribute(h, 15);
        std::cout << "Student Name: " << gameHistory::g_studentName;
        essential::gotoXY(70, 10);
        SetConsoleTextAttribute(h, 15);
        std::cout << "Student No. " << gameHistory::g_studentNumber;
        essential::gotoXY(35, 13);
        SetConsoleTextAttribute(h, 15);
        std::cout << "Your score ---> " << userScore;
        essential::gotoXY(70, 12);
        SetConsoleTextAttribute(h, 15);
        std::cout << sg.getFeedback(userScore);
        essential::gotoXY(70, 14);
        SetConsoleTextAttribute(h, 15);
        std::cout << wrongAnswers; 
        
        //call result ascii art and also the border
        essential::asciiArtResult(func);
    }
} 

#endif