//Header guards
#ifndef TIMETRIALMODE_H
#define TIMETRIALMODE_H

#include <iostream>
#include <chrono>
#include <ctime>
#include <conio.h>
#include <windows.h> //for gotoxy function
#include <unistd.h> //for sleep function

namespace timeTrialMode
{   
    //for questions
    struct ques
    {
        std::string question;
        std::string optionOne;
        std::string optionTwo;
        std::string optionThree;
        std::string optionFour;
        char answers;
    };

    class TimeTrialMode
    {
    private:
        double maxtime { 60 };
        int quesNum { 0 };
        int index { 0 };
        char answer{};
        int playerScore{};
        char a;
        
    public:
      
        void startQuiz()
        {   
            time_t startTime, currentTime;
            int remainingTime;

            startTime = time(NULL);

            struct ques xyz[6];

            xyz[0] = {"Which of the following is not the characteristic of a class?","Generic","Friend","Inline","Inline",'c'};
            xyz[1] = {"Which of the following statements is most suitable for the C++ language?","Statically typed language.","Dynamically typed language.","All","Type-less language.",'a'};
            xyz[2] = {"Which of the following operators doesn�t allow overloading?","Comparison operator.","Assignment operator.","Scope resolution operator.","Dereference operator.",'c'};
            xyz[3] = {"Which of the following isn�t supported in C++ language?","Namespaces.","Inheritance","Reflection.","Polymorphism.",'c'};
            xyz[4] = {"Which of the following keywords can�t appear inside a class definition?","template","static","virtual","friend",'a'};

            do
            {
                currentTime = time(NULL);
                remainingTime = maxtime - difftime(currentTime, startTime);

                gotoXY(10, 0);
                std::cout << "Time remaining: " << remainingTime << " seconds\r" << std::flush;
                sleep(1);

                if (quesNum == index)
                {
                    system("cls");

                    quesNum++;

                    answer = xyz[index].answers;

                    gotoXY(0, 2);
                    std::cout << "Question # " << quesNum << '\n';
                    std::cout << xyz[index].question;
                    std::cout << "\nA. " << xyz[index].optionOne << '\n';
                    std::cout << "B. " << xyz[index].optionTwo << '\n';
                    std::cout << "C. " << xyz[index].optionThree << '\n';
                    std::cout << "D. " << xyz[index].optionFour << '\n';
                    std::cout << "\nSelect your Option ==> ";
                }

                if ( _kbhit() )
                {
                   a= _getch();

                   gotoXY(0, 10);
                   std::cout << a;

                   if(int(a)==13)
                   {
                        std::cout << "\nYou skipped this Question";
                   } 

                   else 
                   {
                        if(a==answer)
                        {
                            playerScore++;
                            gotoXY(0, 10);
                            std::cout << "\nCongratulation You selected right option";
                        } 
                        else 
                        {
                            gotoXY(0, 10);
                            std::cout << "\nCorrect Option is  ==> "<< answer << '\n';
                            std::cout << "You selected wrong option.";

                        }
                  }

                  _getch();
                  index++; 
                }
            }while(remainingTime != 0 && index < 5);

            if (index < 4) 
            {       
                    system("cls");
		            std::cout << "\nTime is up. You failed to attempt all questions"<< '\n';
	        } 
        }

        void gotoXY(int x, int y) 	//function to decide location of the screem
        {
            //A "handle" is a generic identifier (typically a pointer) used to represent something
            //Retrieves a handle to the specified standard device (standard input, standard output).
            HANDLE console = GetStdHandle(STD_OUTPUT_HANDLE); 		 
            COORD CursorPosition; 
            CursorPosition.X = x; // Locates column
            CursorPosition.Y = y; // Locates Row
            //Sets the cursor position in the specified console screen buffer.
            //A COORD structure that specifies the new cursor position, in characters. The coordinates are 
            //the column and row of a screen buffer character cell. The coordinates must be within the 
            //boundaries of the console screen buffer.
            SetConsoleCursorPosition(console,CursorPosition); // Sets position for next thing to be printed 
        }
    };
} 

#endif