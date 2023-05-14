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

#define TOTAL_SCORE 10

namespace passAndPlay
{   
    class Question 
    {
    public:
        std::string question;
        char answer;
        std::string opOne;
        std::string opTwo;
        std::string opThree;
        std::string opFour;

        Question(std::string questions, std::string opOnes, std::string opTwos, std::string opThrees, std::string opFours, char answers) 
        {
            question = questions;
            opOne = opOnes;
            opTwo = opTwos;
            opThree = opThrees;
            opFour = opFours;
            answer = answers;
        }
    };
    
    class PassAndPlay
    {
    private:
        //This is where variables should go 
        std::string playerNameOne{};
        std::string playerNameTwo{};

        std::vector <Question> listOfQuestionPOne;
        std::vector <Question> listOfQuestionPTwo;
        
        int playerOneScore{};
        int playerTwoScore{};

        int quesNum { 0 };
        int index { 0 };
        char a{};
        int numQuestions{};

        bool gameOver = true;
        bool makeTurn = true;

    public:
        void askPlayerName();
        void makeTurns(void (*pass)(void));
        void performAskingUser(std::string&, void (*access)(void));
        void startGame(void (*passMenu)(void));
        void questionsTwo(std::string& pNameTwo, void (*accessReqTwo)(void));
        void questionsOne(std::string& pNameOne, void (*accessReqOne)(void));

        //add question to the vector for playerone
        void addQuestionOne(Question addQuestionOne)
        {
            listOfQuestionPOne.push_back(addQuestionOne);
        }

        //add question to the vector for playertwo
        void addQuestionTwo(Question addQuestionTwo)
        {
            listOfQuestionPTwo.push_back(addQuestionTwo);
        }

        void displayQuestion(std::string& playerNames, std::vector <Question> listOfQuestion, void (*menuAccess)(void))
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
                    std::cout << listOfQuestion[x].question;
                    essential::gotoXY(23, 9);
                    std::cout << "A. " << listOfQuestion[x].opOne << '\n';
                    essential::gotoXY(23, 10);
                    std::cout << "B. " << listOfQuestion[x].opTwo << '\n';
                    essential::gotoXY(23, 11);
                    std::cout << "C. " << listOfQuestion[x].opThree << '\n';
                    essential::gotoXY(23, 12);
                    std::cout << "D. " << listOfQuestion[x].opFour << '\n';
                    essential::gotoXY(23, 14);
                    std::cout << "Press enter to skip";
                    essential::gotoXY(23, 15);
                    std::cout << "Select choices between (a - d) ";
                    std::cin >> a;

                    if(int(a)==13)
                    {    
                        essential::gotoXY(55, 17);
                        std::cout << "You skipped this Question";
                    } 

                    else 
                    {
                        if( a == listOfQuestion[x].answer)
                        {   
                            essential::gotoXY(55, 17);
                            std::cout << "Congratulation You selected right option";
                            (playerNames == playerNameOne) ?  listOfQuestionPOne.erase(itOne) : listOfQuestionPTwo.erase(itTwo);

                            (playerNames == playerNameOne) ? playerOneScore++ : playerTwoScore++;
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

    void PassAndPlay::startGame(void (*passMenu)(void))
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
        addQuestionTwo(Question("Which of the following is not a fundamental data type in C++?", "bool", "double", "string", "int", 'c'));
        addQuestionTwo(Question("Which of the following is a correct way to declare a pointer to an integer variable in C++?", "int* p;", "int* p;", "int* p;", "all of the above", 'd'));
        addQuestionTwo(Question("Which of the following statements is true about pointers in C++?", "Pointers can only be used with arrays.", "Pointers cannot be passed as arguments to functions.", "Pointers cannot be assigned to NULL.", "Pointers can be used to dynamically allocate memory.", 'd'));
        addQuestionTwo(Question("Which of the following operators is used for dynamic memory allocation in C++?", "new", "delete", "Malloc", "Free", 'c'));
        addQuestionTwo(Question("It is the memory address of a variable", "Arithmetic operator", "Typedef", "Pointers", "Point", 'a'));
        addQuestionTwo(Question("What is a class in C++?", "function", "predefined", "user defined", "varibale", 'a'));
        addQuestionTwo(Question("By default access to members of a C++ class is ____________?", "public", "protected", "privacy", "private", 'd'));
        addQuestionTwo(Question("Variable is just an array of characters. ", "one dimensional", "c string", "two dimensional", "dimensional", 'a'));
        addQuestionTwo(Question("this operator use for conditional operator", "?", "=", "+", "==", 'a'));
        addQuestionTwo(Question("this variable cannot be access outside the file", "static varibale", "variable", "global variable", "local variable", 'a'));

        //TODO:Add more question like 20 or 15 question
        displayQuestion(pNameTwo, listOfQuestionPTwo, accessReqTwo);
    }    

    //this function add question for the player one
    void PassAndPlay::questionsOne(std::string& pNameOne, void (*accessReqOne)(void))
    {        
        addQuestionOne(Question("Which of the following is not a fundamental data type in C++?", "bool", "double", "string", "int", 'c'));
        addQuestionOne(Question("Which of the following is a correct way to declare a pointer to an integer variable in C++?", "int* p;", "int* p;", "int* p;", "all of the above", 'd'));
        addQuestionOne(Question("Which of the following statements is true about pointers in C++?", "Pointers can only be used with arrays.", "Pointers cannot be passed as arguments to functions.", "Pointers cannot be assigned to NULL.", "Pointers can be used to dynamically allocate memory.", 'd'));
        addQuestionOne(Question("Which of the following operators is used for dynamic memory allocation in C++?", "new", "delete", "Malloc", "Free", 'c'));
        addQuestionOne(Question("It is the memory address of a variable", "Arithmetic operator", "Typedef", "Pointers", "Point", 'a'));
        addQuestionOne(Question("What is a class in C++?", "function", "predefined", "user defined", "varibale", 'a'));
        addQuestionOne(Question("By default access to members of a C++ class is ____________?", "public", "protected", "privacy", "private", 'd'));
        addQuestionOne(Question("Variable is just an array of characters. ", "one dimensional", "c string", "two dimensional", "dimensional", 'a'));
        addQuestionOne(Question("this operator use for conditional operator", "?", "=", "+", "==", 'a'));
        addQuestionOne(Question("this variable cannot be access outside the file", "static varibale", "variable", "global variable", "local variable", 'a'));
    
        displayQuestion(pNameOne, listOfQuestionPOne, accessReqOne);
    }    
}

#endif