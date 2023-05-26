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
#include "userGameHistory.h"

#define TOTAL_SCORE 100

namespace passAndPlay
{   
   class PassAndPlay
    {
    private:

        std::vector <questionMCQ::Question> listOfQuestionPOne;
        std::vector <questionMCQ::Question> listOfQuestionPTwo;

        questionMCQ::fileDoing getFile;
        gameHistory::StudentGameHistory sg;
        
        int playerOneScore{};
        int playerTwoScore{};

        int quesNum { 0 };
        int index { 0 };
        char a{};
        int numQuestions{};
        std::string whoWin{};

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
        void startGame(void (*passMenu)(void));
        void questionsTwo(std::string& pNameTwo, void (*accessReqTwo)(void));
        void questionsOne(std::string& pNameOne, void (*accessReqOne)(void));
        void resultScreen(void (*func)(void), std::string&);

        void displayQuestion(std::string& playerNames, std::vector <questionMCQ::Question> listOfQuestion, void (*menuAccess)(void))
        {   
            auto itOne = listOfQuestionPOne.begin();
            auto itTwo = listOfQuestionPTwo.begin();

            while (true)
            {   
                for (int x { 0 }; x < getFile.askUserQues; ++x)
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
                        SetConsoleTextAttribute(h, 2);
                        std::cout << "Congratulation You selected right option";
                        
                        //this increment the score of the two player depending who are playing
                        (playerNames == playerNameOne) ? playerOneScore += 10 : playerTwoScore += 10;

                        //this line of code erase the question of the player who get the correct answer
                        (playerNames == playerNameOne) ?  listOfQuestionPOne.erase(itOne) : listOfQuestionPTwo.erase(itTwo);
                    } 

                    else 
                    {   
                        essential::gotoXY(55, 17);
                        SetConsoleTextAttribute(h, 4);
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
                        whoWin = "Congrats! Player One you win!!";
                        resultScreen(menuAccess, whoWin);
                        sg.writeStudentData(playerOneScore);
                        std::exit(0);
                    }
                                    
                    else if (playerTwoScore == TOTAL_SCORE)
                    {   
                        system("cls");
                        whoWin = "Congrats! Player Two you win!!";
                        resultScreen(menuAccess, whoWin);
                        sg.writeStudentData(playerTwoScore);
                        std::exit(0);
                    }

                    if ( x == getFile.askUserQues )
                    {
                        if ( playerOneScore > playerTwoScore )
                        {
                            whoWin = "Congrats! Player one you win!!";
                            resultScreen(menuAccess, whoWin);
                            sg.writeStudentData(playerTwoScore);
                            std::exit(0);
                        }

                        else
                        {
                            whoWin = "Congrats! Player Two you win!!";
                            resultScreen(menuAccess, whoWin);
                            sg.writeStudentData(playerTwoScore);
                            std::exit(0);
                        }
                    }
                }
                
                if (playerOneScore == TOTAL_SCORE)
                {   
                    sg.writeStudentData(playerOneScore);
                    break;
                }
                        
                else if (playerTwoScore == TOTAL_SCORE)
                {   
                    sg.writeStudentData(playerTwoScore);
                    break;
                }
            }
        }

        HANDLE h = GetStdHandle(STD_OUTPUT_HANDLE);
    };

    void PassAndPlay::startGame(void (*passMenu)(void))
    {   
        system("cls");
        sg.isPassAndPlay = true;
        askPlayerName();
        makeTurns(passMenu);
    }
    
    //Ask player name
    void PassAndPlay::askPlayerName()
    {   
        essential::gotoXY(23, 10);
        SetConsoleTextAttribute(h, 1);
        std::cout << "Player one name: ";
        std::getline(std::cin >> std::ws, playerNameOne); //Using std::ws to ignore leading whitespaces
        essential::gotoXY(23, 12);
        SetConsoleTextAttribute(h, 9);
        std::cout << "Player two name: ";
        std::getline(std::cin >> std::ws, playerNameTwo);
        
        system("cls");
        essential::gotoXY(23, 5);
        SetConsoleTextAttribute(h, 15);
        std::cout << playerNameOne << " Input your question. . . . .  ";
        Sleep(2000);
        getFile.openFile(questionFileListOne);

        system("cls");
        essential::gotoXY(23, 5);
        SetConsoleTextAttribute(h, 15);
        std::cout << playerNameTwo << " Input your question. . . . .  ";
        Sleep(2000);
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
                SetConsoleTextAttribute(h, 14);
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
                SetConsoleTextAttribute(h, 14);
                std::cout << turnPlayerName << " it's your turn. . . . . ";
                questionsTwo(turnPlayerName, access);
                break;
            }
        }
    }

    //This function hold the questions for player two
    void PassAndPlay::questionsTwo(std::string& pNameTwo, void (*accessReqTwo)(void))
    {    
        getFile.fillVector(listOfQuestionPTwo, questionFileListTwo);
        displayQuestion(pNameTwo, listOfQuestionPTwo, accessReqTwo);
    }    
    
    //this function add question for the player one
    void PassAndPlay::questionsOne(std::string& pNameOne, void (*accessReqOne)(void))
    {   
        getFile.fillVector(listOfQuestionPOne, questionFileListOne);  
        displayQuestion(pNameOne, listOfQuestionPOne, accessReqOne);
    }    

    void PassAndPlay::resultScreen(void (*func)(void), std::string& str)
    {   
        essential::gotoXY(35, 10);
        SetConsoleTextAttribute(h, 15);
        std::cout << "Student Name: " << gameHistory::g_studentName;
        essential::gotoXY(70, 10);
        SetConsoleTextAttribute(h, 15);
        std::cout << "Student No. " << gameHistory::g_studentNumber;
        essential::gotoXY(35, 13);
        SetConsoleTextAttribute(h, 15);
        std::cout << str;
       
        //call result ascii art and also the border
        essential::asciiArtResult(func);
    }
}

#endif