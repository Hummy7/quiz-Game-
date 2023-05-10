//Header guard
#ifndef PASSANDPLAY_H
#define PASSANDPLAY_H

#include <iostream>
#include <vector>
#include <algorithm> 
#include <string> //To use getline function
#include <windows.h> // for sleep function
#include <conio.h>

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

        bool gameOver = false;
        bool makeTurn = true;

    public:
        void askPlayerName();
        void makeTurns();
        void performAskingUser(std::string&);
        void startGame();
        void questionsTwo(std::string& pNameTwo);
        void questionsOne(std::string& pNameOne);

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

        void gotoXY(int x, int y) 	//function to decide location of the screem
        {
            HANDLE console = GetStdHandle(STD_OUTPUT_HANDLE); 		 
            COORD CursorPosition; 
            CursorPosition.X = x; // Locates column
            CursorPosition.Y = y; // Locates Row
                
            SetConsoleCursorPosition(console,CursorPosition); // Sets position for next thing to be printed 
        }

        void displayQuestion(std::string& playerNames, std::vector <Question> listOfQuestion)
        {   
            auto itOne = listOfQuestionPOne.begin();
            auto itTwo = listOfQuestionPTwo.begin();
            
            while (!gameOver)
            {   
                Sleep(1000);
                system("cls");
                for (int x { 0 }; x < 6; ++x)
                {
                    gotoXY(23, 5);
                    std::cout << "Question # " << x + 1<< '\n';
                    gotoXY(23, 7);
                    std::cout << listOfQuestion[x].question;
                    gotoXY(23, 9);
                    std::cout << "A. " << listOfQuestion[x].opOne << '\n';
                    gotoXY(23, 10);
                    std::cout << "B. " << listOfQuestion[x].opTwo << '\n';
                    gotoXY(23, 11);
                    std::cout << "C. " << listOfQuestion[x].opThree << '\n';
                    gotoXY(23, 12);
                    std::cout << "D. " << listOfQuestion[x].opFour << '\n';
                    gotoXY(23, 14);
                    std::cout << "Select your Option ==> ";
                    std::cin >> a;

                    if(int(a)==13)
                    {    
                        gotoXY(23, 16);
                        std::cout << "You skipped this Question";
                    } 

                    else 
                    {
                        if( a == listOfQuestion[x].answer)
                        {   
                            gotoXY(23, 16);
                            std::cout << "Congratulation You selected right option";
                            (playerNames == playerNameOne) ?  listOfQuestionPOne.erase(itOne) : listOfQuestionPTwo.erase(itTwo);

                            (playerNames == playerNameOne) ? playerOneScore++ : playerTwoScore++;
                        } 

                        else 
                        {   
                            gotoXY(23, 16);
                            std::cout << "You selected wrong option.";
                            
                            if (playerNames == playerNameOne)
                            {
                                if (makeTurn)
                                {
                                    makeTurn = false;
                                    makeTurns();
                                }
                                        
                                else
                                {
                                    makeTurn = true;
                                    makeTurns();
                                }  
                            }

                            else
                            {
                                if (makeTurn) 
                                {
                                    makeTurn = false;
                                    makeTurns();
                                }
                                        
                                else
                                {
                                    makeTurn = true;
                                    makeTurns();
                                }
                            }
                        }
                    }
                }
            
                if (playerOneScore == TOTAL_SCORE)
                {
                    std::cout << playerNameOne << " You win!!!!";
                    gameOver = true;
                }
                    
                else if (playerTwoScore == TOTAL_SCORE)
                {
                    std::cout << playerNameOne << " You win!!!!";
                    gameOver = true;
                }
                //TODO:Add winner screen
            }
        }
    };

    void PassAndPlay::startGame()
    {   
        system("cls");
        askPlayerName();
        makeTurns();
    }
    
    //Ask player name
    void PassAndPlay::askPlayerName()
    {   
        gotoXY(23, 5);
        std::cout << "Player one name: ";
        std::getline(std::cin >> std::ws, playerNameOne); //Using std::ws to ignore leading whitespaces
        gotoXY(23, 7);
        std::cout << "Player two name: ";
        std::getline(std::cin >> std::ws, playerNameTwo);

    }
    
    //this function allow us to maketurn for the players
    void PassAndPlay::makeTurns()
    {   
        if (makeTurn)
        {   
            system("cls");
            performAskingUser(playerNameOne);
        }

        else
        {   
            system("cls");
            performAskingUser(playerNameTwo);
        }
    }

    void PassAndPlay::performAskingUser(std::string& turnPlayerName)
    {   
        std::string userChoice{};

        if (turnPlayerName == playerNameOne)
        {
            while (true)
            {   
                gotoXY(23, 5);
                std::cout << turnPlayerName << " it's your turn. . . . . ";
                questionsOne(turnPlayerName);
                break;
            }
        }

        else
        {
             while (true)
            {   
                gotoXY(23, 5);
                std::cout << turnPlayerName << " it's your turn. . . . . ";
                questionsTwo(turnPlayerName);
                break;
            }
        }
    }

    //This function hold the questions for player two
    void PassAndPlay::questionsTwo(std::string& pNameTwo)
    {        
        addQuestionTwo(Question("who is me", "World wide web", "Wob web wb", "Wo WO Wo", "We we we", 'a'));
        addQuestionTwo(Question("who is you?", "World wide web", "Wob web wb", "Wo WO Wo", "We we we", 'a'));
        addQuestionTwo(Question("tang ina mo", "World wide web", "Wob web wb", "Wo WO Wo", "We we we", 'a'));
        addQuestionTwo(Question("tang ina nya", "World wide web", "Wob web wb", "Wo WO Wo", "We we we", 'a'));
        addQuestionTwo(Question("tang ina nyong lahat", "World wide web", "Wob web wb", "Wo WO Wo", "We we we", 'a'));
        addQuestionTwo(Question("hala sya", "World wide web", "Wob web wb", "Wo WO Wo", "We we we", 'a'));

        displayQuestion(pNameTwo, listOfQuestionPTwo);
    }    

    //this function add question for the player one
    void PassAndPlay::questionsOne(std::string& pNameOne)
    {        
       addQuestionOne(Question("who is me", "World wide web", "Wob web wb", "Wo WO Wo", "We we we", 'a'));
        addQuestionOne(Question("who is you?", "World wide web", "Wob web wb", "Wo WO Wo", "We we we", 'a'));
        addQuestionOne(Question("tang ina mo", "World wide web", "Wob web wb", "Wo WO Wo", "We we we", 'a'));
        addQuestionOne(Question("tang ina nya", "World wide web", "Wob web wb", "Wo WO Wo", "We we we", 'a'));
        addQuestionOne(Question("tang ina nyong lahat", "World wide web", "Wob web wb", "Wo WO Wo", "We we we", 'a'));
        addQuestionOne(Question("hala sya", "World wide web", "Wob web wb", "Wo WO Wo", "We we we", 'a'));

        displayQuestion(pNameOne, listOfQuestionPOne);
    }    
}

#endif