//This i s a header guard
#ifndef CLASSICMODE_H
#define CLASSICMODE_H

#include <iostream>
#include <vector>
#include <algorithm>
#include <string>
#include <cstdlib>
#include "questionMultipleChoice.h"
#include "questionIdentification.h"
#include <fstream>

// Adding namespace to avoid naming collision
namespace classicMode
{   
    class ClassicMode
    {
    private:
        int userChoice{};
        std::string userInputtedAns{};

        std::ifstream questionFile;
        std::vector <questionMCQ::Question> questionListVect;
        char yAndNChoice{};

        questionMCQ::fileDoing gettingFiles;
        questionIdentification::gettingQuesFile fileGathering;
        
    public:
        int playerScore{}; 
        void startGame(void (*mainMenuAccess)(void));

        void askTypeOfQuestion(void (*menu)(void))
        {   
            int userChoice{};
            
            system("cls");
            essential::gotoXY(50, 5);
            SetConsoleTextAttribute(h, 15);
            std::cout << "-=-=- Select type of question -=-=-";
            essential::gotoXY(50, 7);
            SetConsoleTextAttribute(h, 15);
            std::cout << "[1] Multiple Choices Question";
            essential::gotoXY(50, 9);
            SetConsoleTextAttribute(h, 15);
            std::cout << "[2] Identification";
            essential::gotoXY(50, 11);
            SetConsoleTextAttribute(h, 15);
            std::cout << "Select: ";
            std::cin >> userChoice;

            switch(userChoice)
            {
                case 1:
                    gettingFiles.start(menu);
                    playerScore = questionMCQ::g_scoreOfPlayer;
                    break;

                case 2:
                    fileGathering.start(menu);
                    playerScore = questionIdentification::g_scoreOfPlayer;
                    break;
            }
        }

        HANDLE h = GetStdHandle(STD_OUTPUT_HANDLE);
    };

    void ClassicMode::startGame(void (*mainMenuAccess)(void))
    { 
         askTypeOfQuestion(mainMenuAccess);
    }
}

#endif


