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
        void askDifficulty(void (*menu)(void));
        void easyDiff(void (*menuAcess)(void));
        void mediumDiff(void (*menus)(void));
        void hardDiff(void (*menuss)(void));
        void displayScore();

        void askTypeOfQuestion(void (*menu)(void))
        {   
            int userChoice{};
            
            system("cls");
            essential::gotoXY(50, 5);
            std::cout << "-=-=- Select type of question -=-=-";
            essential::gotoXY(50, 7);
            std::cout << "[1] Multiple Choices Question";
            essential::gotoXY(50, 9);
            std::cout << "[2] Identification";
            essential::gotoXY(50, 11);
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

        bool getFile(std::string fileName)
        {   
            //opening the file
            questionFile.open(fileName, std::ios::in);

            if (!questionFile)
            {   
                essential::gotoXY(23, 5);
                std::cout << "Cannot open file!!";
                return false;
            }

            gettingFiles.fillVectorSecond(questionListVect, questionFile);

            //closing the file
            questionFile.close();

            return true;
        }
    };

    void ClassicMode::startGame(void (*mainMenuAccess)(void))
    { 
        do 
        {   
            system("cls");
            essential::gotoXY(23, 5);
            std::cout << "Do you want to load your own question? (y/n): ";
            std::cin >> yAndNChoice;

        }while(yAndNChoice != 'y' && yAndNChoice != 'n');

        if (yAndNChoice == 'y')
        {
            askTypeOfQuestion(mainMenuAccess);
        }

        else
        {
            askDifficulty(mainMenuAccess);
        }

    }

    void ClassicMode::askDifficulty(void (*menu)(void))
    {   
        system("cls");
        essential::gotoXY(23, 4);
        std::cout << " -=-=- Select Difficulty -=-=";
        essential::gotoXY(34, 6);
        std::cout << "[1] Easy";
        essential::gotoXY(34, 8);
        std::cout << "[2] Medium";
        essential::gotoXY(34, 10);
        std::cout << "[3] Hard";
        essential::gotoXY(34, 12);
        std::cout << "[4] Home";
        essential::gotoXY(34, 15);
        std::cout << "Choice: ";
        std::cin >> userChoice; 

        switch (userChoice)
        {
            case 1:
              easyDiff(menu);
                break;

            case 2:
              mediumDiff(menu);
                break;

            case 3:
              hardDiff(menu);
                break;

            case 4:
                break; 
        
            default:
                break;
        }
    }

    void ClassicMode::easyDiff(void (*menuAcess)(void))
    {   
        bool result = getFile("easy.txt");

        if (result)
        {
            gettingFiles.printVectorTwo(questionListVect, menuAcess);
        }
    }

    void ClassicMode::mediumDiff(void (*menus)(void))
    {
        bool result = getFile("medium.txt");

        if (result)
        {
            gettingFiles.printVectorTwo(questionListVect, menus);
        }
    }

    void ClassicMode::hardDiff(void (*menuss)(void))
    {
        bool result = getFile("hard.txt");

        if (result)
        {
            gettingFiles.printVectorTwo(questionListVect, menuss);
        }
    }
}

#endif


