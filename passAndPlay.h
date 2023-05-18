//Header guard
#ifndef PASSANDPLAY_H
#define PASSANDPLAY_H

#include <iostream>
#include <vector>
#include <algorithm> 
#include <string> //To use getline function
#include <windows.h> // for sleep function
#include <conio.h>
#include "essential.h"
#include "questionMultipleChoice.h"

#define TOTAL_SCORE 10

namespace passAndPlay
{   

   class PassAndPlay
    {
    private:

        std::vector <questionMCQ::Question> listOfQuestionPOne;
        std::vector <questionMCQ::Question> listOfQuestionPTwo;

        questionMCQ::fileDoing getFile;
        
        int playerOneScore{};
        int playerTwoScore{};

        int quesNum { 0 };
        int index { 0 };
        char a{};
        int numQuestions{};

        bool makeTurn = true;

        std::ifstream questionFileListOne;
        std::ifstream questionFileListTwo;
        
    public:
     //This is where variables should go 
        std::string playerNameOne{};
        std::string playerNameTwo{};

        void askPlayerName();
        void makeTurns(void (*pass)(void));
        void performAskingUser(std::string&, void (*access)(void));
        void startGame(void (*passMenu)(void), std::string pNamed);
        void questionsTwo(std::string& pNameTwo, void (*accessReqTwo)(void));
        void questionsOne(std::string& pNameOne, void (*accessReqOne)(void));

        void fillVect(std::vector <questionMCQ::Question>& newQuestionList, std::ifstream& queFile, char correctAnswer, std::string name)
        {
            std::string questions;
            std::string optionOne;
            std::string optionTwo;
            std::string optionThree;
            std::string optionFour;
            char answer;
            
            for (int i = 0; i < getFile.askUserQues; i++)
            {
                std::getline(queFile >> std::ws, questions);
                std::getline(queFile >> std::ws, optionOne);
                std::getline(queFile >> std::ws, optionTwo);
                std::getline(queFile >> std::ws, optionThree);
                std::getline(queFile >> std::ws, optionFour);
                queFile >> answer; queFile.ignore(1000, '\n');
        
                questionMCQ::Question newQuestion(questions, optionOne, optionTwo, optionThree, optionFour, answer);
                newQuestionList.push_back(newQuestion);

                // std::shuffle(newQuestioinList.begin(), newQuestionList.end(), essential::randomingQuestion());
                if (correctAnswer == newQuestionList[i].getAnswer())
                {
                    if (name == playerNameOne)
                    {
                        
                    }
                }
            }
        }

        void displayQuestion(std::string& playerNames, std::vector <questionMCQ::Question> listOfQuestion, void (*menuAccess)(void))
        {   
            auto itOne = listOfQuestionPOne.begin();
            auto itTwo = listOfQuestionPTwo.begin();
            
            while (true)
            {   
                for (int x { 0 }; x < 6; ++x)
                {   
                    Sleep(1000);
                    system("cls");
                    essential::ebod();
                    essential::borderTwo();
                    
                    essential::gotoXY(23, 5);
                    std::cout << "Question # " << x + 1<< '\n';
                    essential::gotoXY(23, 7);
                    std::cout << listOfQuestion[x].getQuestion();
                    essential::gotoXY(23, 9);
                    std::cout << "A. " << listOfQuestion[x].getOptionOne() << '\n';
                    essential::gotoXY(23, 10);
                    std::cout << "B. " << listOfQuestion[x].getOptionTwo() << '\n';
                    essential::gotoXY(23, 11);
                    std::cout << "C. " << listOfQuestion[x].getOptionThree() << '\n';
                    essential::gotoXY(23, 12);
                    std::cout << "D. " << listOfQuestion[x].getOptionFour() << '\n';
                    essential::gotoXY(23, 14);
                    std::cout << "Press enter to skip";
                    essential::gotoXY(23, 15);
                    std::cout << "Select choices between (a - d) ";
                    std::cin >> a;
                  
                    if( a == listOfQuestion[x].getAnswer())
                    {   
                        essential::gotoXY(55, 17);
                        std::cout << "Congratulation You selected right option";
                            
                        (playerNames == playerNameOne) ? playerOneScore++ : playerTwoScore++;

                        (playerNames == playerNameOne) ?  listOfQuestionPOne.erase(itOne) : listOfQuestionPTwo.erase(itTwo);
                    } 

                    else 
                    {   
                        essential::gotoXY(55, 17);
                        std::cout << "You selected wrong option.";
                            
                        if (playerNames == playerNameOne)
                        {
                            if (makeTurn)
                            {
                                makeTurn = false;
                                 makeTurns(menuAccess);
                            }
                                        
                            else
                            {
                                makeTurn = true;
                                makeTurns(menuAccess);
                            }  
                        }

                        else
                        {
                            if (makeTurn) 
                            {
                                makeTurn = false;
                                makeTurns(menuAccess);
                            }
                                        
                            else
                            {
                                makeTurn = true;
                                makeTurns(menuAccess);
                            }
                        }
                    }

                    if (playerOneScore == TOTAL_SCORE)
                    {   
                        system("cls");
                        essential::resultScreen(menuAccess);
                        std::exit(0);
                    }
                                    
                    else if (playerTwoScore == TOTAL_SCORE)
                    {   
                        system("cls");
                        essential::resultScreen(menuAccess);
                        std::exit(0);
                    }
                }
                
                if (playerOneScore == TOTAL_SCORE)
                {   
                    break;
                }
                        
                else if (playerTwoScore == TOTAL_SCORE)
                {   
                    break;
                }
            }
        }
    };

    void PassAndPlay::startGame(void (*passMenu)(void), std::string pNamed)
    {   
        system("cls");
        askPlayerName();
        makeTurns(passMenu);
    }
    
    //Ask player name
    void PassAndPlay::askPlayerName()
    {   
        essential::gotoXY(23, 5);
        std::cout << "Player one name: ";
        std::getline(std::cin >> std::ws, playerNameOne); //Using std::ws to ignore leading whitespaces
        essential::gotoXY(23, 7);
        std::cout << "Player two name: ";
        std::getline(std::cin >> std::ws, playerNameTwo);

        getFile.openFile(questionFileListOne);
        getFile.openFile(questionFileListTwo);
    }
    
    //this function allow us to maketurn for the players
    void PassAndPlay::makeTurns(void (*menuAccess)(void))
    {   
        if (makeTurn)
        {   
            system("cls");
            performAskingUser(playerNameOne, menuAccess);
        }

        else
        {   
            system("cls");
            performAskingUser(playerNameTwo, menuAccess);
        }
    }

    void PassAndPlay::performAskingUser(std::string& turnPlayerName, void (*access)(void))
    {   
        std::string userChoice{};

        if (turnPlayerName == playerNameOne)
        {
            while (true)
            {   
                essential::gotoXY(23, 5);
                std::cout << turnPlayerName << " it's your turn. . . . . ";
                questionsOne(turnPlayerName, access);
                break;
            }
        }

        else
        {
             while (true)
            {   
                essential::gotoXY(23, 5);
                std::cout << turnPlayerName << " it's your turn. . . . . ";
                questionsTwo(turnPlayerName, access);
                break;
            }
        }
    }

    //This function hold the questions for player two
    void PassAndPlay::questionsTwo(std::string& pNameTwo, void (*accessReqTwo)(void))
    {    
        fillVect(listOfQuestionPTwo, questionFileListTwo, a, pNameTwo);
        displayQuestion(pNameTwo, listOfQuestionPTwo, accessReqTwo);
    }    
    
    //this function add question for the player one
    void PassAndPlay::questionsOne(std::string& pNameOne, void (*accessReqOne)(void))
    {   
        fillVect(listOfQuestionPOne, questionFileListOne, a, pNameOne);  
        displayQuestion(pNameOne, listOfQuestionPOne, accessReqOne);
    }    
}

#endif