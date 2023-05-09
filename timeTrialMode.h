//Header guards
#ifndef TIMETRIALMODE_H
#define TIMETRIALMODE_H

#include <iostream>
#include <chrono>
#include <ctime>
#include <conio.h> 
#include <windows.h> //for gotoxy function
#include <vector>
#include <fstream> //for file handling
#include <string>

namespace timeTrialMode
{   
    //Forward Declration
    void start();
   
    class TimeTrialMode
    {
    private:
        std::string questions;
        std::string optionOne;
        std::string optionTwo;
        std::string optionThree;
        std::string optionFour;
        char answer;
        
    public:
        TimeTrialMode(std::string& ques, std::string& opOne, std::string& opTwo, std::string& opThree, std::string& opFour, char ans);

        std::string getQuestion(){return questions;};
        std::string getOptionOne(){return optionOne;};
        std::string getOptionTwo(){return optionTwo;};
        std::string getOptionThree(){return optionThree;};
        std::string getOptionFour(){return optionFour;};
        char getAnswer(){return answer;};
    };

    std::ifstream g_questionFile;
    std::vector<TimeTrialMode> g_questionList;

    void gotoXY(int x, int y) 	//function to decide location of the screem
    {
        HANDLE console = GetStdHandle(STD_OUTPUT_HANDLE); 		 
        COORD CursorPosition; 
        CursorPosition.X = x; // Locates column
        CursorPosition.Y = y; // Locates Row
            
        SetConsoleCursorPosition(console,CursorPosition); // Sets position for next thing to be printed 
    }

    void startQuiz()
    {   
        time_t startTime, currentTime;
        int remainingTime;

        double maxtime { 60 };
        int quesNum { 0 };
        int index { 0 };
        int playerScore{};
        char a;
        int numOfQuestion;

        startTime = time(NULL);

        //ask the user how many question does the txt file have
        std::cout << "How many questions? ";
        std::cin >> numOfQuestion;

        start();

        do
        {
            currentTime = time(NULL);
            remainingTime = maxtime - difftime(currentTime, startTime);

            gotoXY(10, 0);
            std::cout << "Time remaining: " << remainingTime << " seconds\r" << std::flush;
            Sleep(1);

            if (quesNum == index)
            {
                system("cls");

                quesNum++;

                gotoXY(0, 2);
                    
                std::cout << "Question # " << quesNum << '\n';
                std::cout << g_questionList[index].getQuestion();
                std::cout << "\nA. " << g_questionList[index].getOptionOne() << '\n';
                std::cout << "B. " << g_questionList[index].getOptionTwo() << '\n';
                std::cout << "C. " << g_questionList[index].getOptionThree() << '\n';
                std::cout << "D. " <<g_questionList[index].getOptionFour() << '\n';
                std::cout << "\nSelect your Option ==> ";
            }

            if ( _kbhit() )
            {
                a = _getch();

                gotoXY(0, 10);
                std::cout << a;

                if(int(a)==13)
                {
                    std::cout << "\nYou skipped this Question";
                } 

                else 
                {
                    if( a == g_questionList[index].getAnswer())
                    {
                        gotoXY(0, 10);
                        std::cout << "\nCongratulation You selected right option";
                        playerScore++; //This will increment if the player get the correct answer
                    } 

                    else 
                    {
                        gotoXY(0, 10);
                        std::cout << "\nCorrect Option is  ==> "<< g_questionList[index].getAnswer() << '\n';
                        std::cout << "You selected wrong option.";
                    }
                }

                  _getch();
                  index++; 
            }
        }while(remainingTime != 0 && index < numOfQuestion); //if the remainingtime == 0 and the index reach the numeber of question that the user want the program will stop

        if (index < numOfQuestion - 1) 
        {       
            system("cls");
		    std::cout << "\nTime is up. You failed to attempt all questions"<< '\n';
	    } 
    }

    TimeTrialMode::TimeTrialMode(std::string& ques, std::string& opOne, std::string& opTwo, std::string& opThree, std::string& opFour, char ans)
    {
        questions = ques;
        optionOne = opOne;
        optionTwo = opTwo;
        optionThree = opThree;
        optionFour = opFour;
        answer = ans;
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

    //this function is responsible to fill the vector with the text that get from the file
    void fillVector(std::vector <TimeTrialMode>& newQuestionList, std::ifstream& queFile)
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
    
            TimeTrialMode newQuestion(questions, optionOne, optionTwo, optionThree, optionFour, answer);
            newQuestionList.push_back(newQuestion);
        }
    }

    void start()
    {
        
        while (openFile(g_questionFile))
        {
            openFile(g_questionFile);
        }

        fillVector(g_questionList, g_questionFile);
    }

} 

#endif