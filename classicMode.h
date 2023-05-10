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

    public:
        int playerScore{};  
        void startGame();
        void askDifficulty();
        void easyDiff();
        void mediumDiff();
        void hardDiff();
        void displayScore();
        void startQuestion();

        void gotoXY(int x, int y) 	//function to decide location of the screem
        {
            HANDLE console = GetStdHandle(STD_OUTPUT_HANDLE); 		 
            COORD CursorPosition; 
            CursorPosition.X = x; // Locates column
            CursorPosition.Y = y; // Locates Row
                
            SetConsoleCursorPosition(console,CursorPosition); // Sets position for next thing to be printed 
        }

        void askTypeOfQuestion()
        {   
            int userChoice{};

            system("cls");
            gotoXY(23, 4);
            std::cout << "-=-=- Select type of question -=-=-";
            gotoXY(40, 6);
            std::cout << "[1] Multiple Choices Question";
            gotoXY(40, 7);
            std::cout << "[2] Identification";
            gotoXY(40, 10);
            std::cout << "Select: ";
            std::cin >> userChoice;

            switch(userChoice)
            {
                case 1:
                    questionMCQ::main();
                    playerScore = questionMCQ::g_scoreOfPlayer;
                    break;
                case 2:
                    questionIdentification::main();
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
                gotoXY(23, 5);
                std::cout << "Cannot open file!!";
                return false;
            }

            questionMCQ::fillVector(questionListVect, questionFile);

            //closing the file
            questionFile.close();

            return true;
        }
    };

    void ClassicMode::startGame()
    { 
        do 
        {   
            system("cls");
            gotoXY(23, 5);
            std::cout << "Do you want to load your own question? (y/n): ";
            std::cin >> yAndNChoice;

        }while(yAndNChoice != 'y' && yAndNChoice != 'n');

        if (yAndNChoice == 'y')
        {
            startQuestion();
        }

        else
        {
            askDifficulty();
        }

    }

    void ClassicMode::startQuestion()
    {
        askTypeOfQuestion();
    }

    void ClassicMode::askDifficulty()
    {   
        system("cls");
        gotoXY(23, 4);
        std::cout << " -=-=- Select Difficulty -=-=";
        gotoXY(34, 6);
        std::cout << "[1] Easy";
        gotoXY(3, 8);
        std::cout << "[2] Medium";
        gotoXY(34, 10);
        std::cout << "[3] Hard";
        gotoXY(34, 12);
        std::cout << "[4] Home";
        gotoXY(34, 15);
        std::cout << "Choice: ";
        std::cin >> userChoice; 

        switch (userChoice)
        {
            case 1:
              easyDiff();
                break;

            case 2:
              mediumDiff();
                break;

            case 3:
              hardDiff();
                break;

            case 4:
                break; 
        
            default:
                break;
        }
    }

    void ClassicMode::easyDiff()
    {   
        bool result = getFile("easy.txt");

        if (result)
        {
            questionMCQ::printVector(questionListVect);
        }
    }

    void ClassicMode::mediumDiff()
    {
        bool result = getFile("medium.txt");

        if (result)
        {
            questionMCQ::printVector(questionListVect);
        }
    }

    void ClassicMode::hardDiff()
    {
        bool result = getFile("hard.txt");

        if (result)
        {
            questionMCQ::printVector(questionListVect);
        }
    }

    void ClassicMode::displayScore()
    {
        std::cout << playerScore;
    }
    
}

#endif


