//Header Guard

#ifndef QUESTIONMCQ_H
#define QUESTIONMCQ_H

#include <vector>
#include <fstream>
#include <iostream>
#include <string>
#include <windows.h>
#include <conio.h> 

namespace questionMCQ
{   
   
    int g_scoreOfPlayer{};

    class Question
    {
        private:
            std::string questions;
            std::string optionOne;
            std::string optionTwo;
            std::string optionThree;
            std::string optionFour;
            char answer;
            
        public:
            Question(std::string& ques, std::string& opOne, std::string& opTwo, std::string& opThree, std::string& opFour, char ans);
            std::string getQuestion(){return questions;};
            std::string getOptionOne(){return optionOne;};
            std::string getOptionTwo(){return optionTwo;};
            std::string getOptionThree(){return optionThree;};
            std::string getOptionFour(){return optionFour;};
            char getAnswer(){return answer;};
    };

    Question::Question(std::string& ques, std::string& opOne, std::string& opTwo, std::string& opThree, std::string& opFour, char ans)
    {
        questions = ques;
        optionOne = opOne;
        optionTwo = opTwo;
        optionThree = opThree;
        optionFour = opFour;
        answer = ans;
    }

    void gotoXY(int x, int y) 	//function to decide location of the screem
    {
        HANDLE console = GetStdHandle(STD_OUTPUT_HANDLE); 		 
        COORD CursorPosition; 
        CursorPosition.X = x; // Locates column
        CursorPosition.Y = y; // Locates Row
            
        SetConsoleCursorPosition(console,CursorPosition); // Sets position for next thing to be printed 
    }

    bool openFile(std::ifstream& quesFile)
    {
        std::string fileName;
        
        std::cout << "\nAdd .txt at the end of your filename.\n";
        std::cout << "Filename: ";
        std::getline(std::cin >> std::ws, fileName);
            
        //ifstream QuestionData;
        quesFile.open(fileName);
            
        if (!quesFile.is_open())
        {
            std::cout << "Could not find database." << '\n';
            return true;
        }
            
        else
        {
            std::cout << "Database sucessfully accessed!" << '\n';
            return false;
        }
    }

    void fillVector(std::vector <Question>& newQuestionList, std::ifstream& queFile)
    {
        std::string questions;
        std::string optionOne;
        std::string optionTwo;
        std::string optionThree;
        std::string optionFour;
        char answer;
        
        for (int i = 0; i < 10; i++)
        {
            std::getline(queFile >> std::ws, questions);
            std::getline(queFile >> std::ws, optionOne);
            std::getline(queFile >> std::ws, optionTwo);
            std::getline(queFile >> std::ws, optionThree);
            std::getline(queFile >> std::ws, optionFour);
            // std::getline(queFile >> std::ws, answer);
            queFile >> answer; queFile.ignore(1000, '\n');
    
            Question newQuestion(questions, optionOne, optionTwo, optionThree, optionFour, answer);
            newQuestionList.push_back(newQuestion);
        }
    }

    void printVector(std::vector <Question>& newQuestionList)
    {   
        char choice;

        int questionNumber{};
        int i{};
        char a;
        char askUserQues{};

        std::cout << "How many questions? ";
        std::cin >> askUserQues;

        do 
        {
            if (questionNumber == i)
            {
                system("cls");

                questionNumber++;

                gotoXY(23, 5);
                std::cout << "Question #" << i+1 << '\n';
                gotoXY(23, 6);
                std::cout <<  newQuestionList[i].getQuestion() << '\n';
                gotoXY(23, 8);
                std::cout << "A. " << newQuestionList[i].getOptionOne() << '\n';
                gotoXY(23, 9);
                std::cout << "B. " << newQuestionList[i].getOptionTwo() << '\n';
                gotoXY(23, 10);
                std::cout << "C. " << newQuestionList[i].getOptionThree() << '\n';
                gotoXY(23, 11);
                std::cout << "D. " << newQuestionList[i].getOptionFour() << '\n';
                gotoXY(23, 13);
                std::cout << "Selecdt choices between (a -d): ";
            }

        
            if ( _kbhit() )
            {
                a = _getch();

                gotoXY(56, 13);
                std::cout << a;

                if(int(a)==13)
                {   
                    gotoXY(23, 15);
                    std::cout << "You skipped this Question";
                } 

                else 
                {
                    if( a == newQuestionList[i].getAnswer())
                    {
                        gotoXY(23, 15);
                        std::cout << "Congratulation You selected right option";
                    
                    } 

                    else 
                    {
                        gotoXY(23, 15);
                        std::cout << "Correct Option is  ==> "<< newQuestionList[i].getAnswer() << '\n';
                        gotoXY(23, 16);
                        std::cout << "You selected wrong option.";
                    }
                }

                  _getch();
                  i++; 
            }
        }while(i < askUserQues);
    }

    int main()
    {
        std::ifstream questionFile;
        std::vector<Question> questionList; //vector to tore the text from the file

        //If openfile return true it means the user input is wrong if return false then it was write
        while (openFile(questionFile))
        {
            openFile(questionFile);
        }

        fillVector(questionList, questionFile);
        printVector(questionList);
    }
}

#endif