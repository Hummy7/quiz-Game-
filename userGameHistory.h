//Adding header guard
#ifndef USERGAMEHISTORY_H
#define USERGAMEHISTORY_H

#include <iostream>
#include <fstream>
#include <string>
#include "essential.h"
#include <vector>
#include <iomanip> // for setw function
#include <conio.h>
#include <cctype> //detect if the input is not number
#include <algorithm> 

namespace gameHistory
{   
    int g_studentNumber;
    std::string g_studentName;

    class StudentGameHistory
    {
    private:
        std::ofstream outFile;
        std::ifstream inFile;

    public:
        bool isTimeTrialMode { false };
        bool isSurvivalMode { false };
        bool isPassAndPlay { false };
        bool isClassicMode { false };
        bool hasEnterAMode  { false };

        std::string timeTrialMode { "Time Trial" };
        std::string survivalMode { "Survival" };
        std::string passAndPlayMode { "Pass & Play" };
        std::string classicMode { "Classic" };

        std::string gameMode{};
        std::string feedback{};

        //member functions
        void getStudentInfo();
        // void showStudentData();
        void writeStudentData(int score);
        void displayStudentData(void (*menu)(void));
        std::string  detectingWhatMode();  
        double calculatePercent(int playerScore);
        std::string calculateGrade (int per);
        void openFilling();
        void showData(const std::vector <std::string>& v);
        std::string getFeedback(int score);

        bool openingFile()
        {
            if (!outFile.is_open()) 
            {
                std::cout << "ERROR: we can't open\n"; 
                return false;
            }

            else 
            {
                return true;
            }
        }

        bool check_number(std::string& str) 
        {
            for (int i = 0; i < str.length(); i++)
            {
                if (isdigit(str[i]) == false)
                    return false;
                    return true;
            }
            
        }

        //validate the name of the user 
        bool isValidName(std::string& name)
        {
            return all_of(name.begin(), name.end(), [](char ch) {
                return (isalpha(ch) || isspace(ch));
            });
        }

        HANDLE h = GetStdHandle(STD_OUTPUT_HANDLE);
    };

    //ask the student information like name and student no.
    void StudentGameHistory::getStudentInfo()
    {   
        essential::gotoXY(50, 5);
        std::cout << "Enter your student number: ";
        std::cin >> g_studentNumber;

        while ( !std::cin )
        {   
            system("cls");
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            essential::gotoXY(50, 5);
            std::cout << "Enter your student number: ";
            std::cin >> g_studentNumber;
        }
        
        do 
        {   
            essential::gotoXY(50, 7);
            std::cout << "Enter student name: ";
            //We use getline to be able to get all of the next character
            std::getline(std::cin >> std::ws, g_studentName); //using std::ws to ignore leading whitespaces
        }while(!isValidName(g_studentName));
    }

    std::string StudentGameHistory::detectingWhatMode()
    {
        if ( isTimeTrialMode )
        {
            gameMode = timeTrialMode;
        }

        else if ( isSurvivalMode )
        {
            gameMode = survivalMode;
        }

        else if ( isPassAndPlay )
        {
            gameMode = passAndPlayMode;
        }

        else if ( isClassicMode )
        {
            gameMode = classicMode;
        }

        return gameMode;
    }

    void StudentGameHistory::writeStudentData(int score)
    {
        outFile.open("studentRecord.txt", std::ios::out | std::ios::app);

        while ( !openingFile() )
        {
            openingFile();
        }
        
        outFile << g_studentNumber << std::endl;
        outFile << g_studentName << std::endl;
        outFile << score << std::endl;
        outFile << detectingWhatMode() << std::endl;
        outFile << calculatePercent(score) << std::endl;
        outFile << calculateGrade(score) << std::endl;
    }

    void StudentGameHistory::displayStudentData(void (*menu)(void))
    {   
        system("cls");
        
        SetConsoleTextAttribute(h, 6);
        std::cout << "ALL STUDENT RECORDS\n";
        SetConsoleTextAttribute(h, 2);
        std::cout<< "========================================================================================\n";
        std::cout<<"StudentNo        Name             Score           quizMode              %               grade " << '\n';
        std::cout<<"===============================================================================================\n";

        openFilling();

        std::cout << "Press any key to menu. . . ";
        getch();
        system("cls");
        menu(); // go back to menu
    }   

    double StudentGameHistory::calculatePercent(int playerScore)
    {   
        //calculating the percentage of the score of the student
        double percent = playerScore * 10.0 / 100.0;

        return percent;
    }

    std::string StudentGameHistory::calculateGrade (int per)
    {
        if ( per >= 80 )
        {
            return "A";
        }

        else if ( per >= 60 )
        {
            return "B";
        }

        else if ( per >= 40 )
        {
            return "C";
        }

        else
        {
            return "F";
        }
    }

    std::string StudentGameHistory::getFeedback(int score)
    {
        if ( score >= 80 )
        {
            return "Explendid!";
        }

        else if ( score >= 60 )
        {
            return "Great Job!";
        }

        else if ( score >= 40 )
        {
            return "Superb!";
        }

        else
        {
            return "Better Luck Next Time!";
        }
    }

    void StudentGameHistory::openFilling()
    {
        std::string filename("studentRecord.txt") ;
        std::ifstream in(filename.c_str()) ;

        if ( !in.is_open() )
        {
            std::cerr << "Unable to open " << filename << '\n' ;
        }

        std::vector <std::string> recordFiles;
        std::string records;
        
        //Filling the vector and using push back to allow that
        while ( std::getline(in, records) )
            recordFiles.push_back(records) ;

        showData(recordFiles);
    }

    void StudentGameHistory::showData(const std::vector <std::string>& v)
    {
         for ( unsigned i { 0 }; i < v.size(); ++i )
        {   
            std::cout << v[i] << std::setw(20);
            
            //if the line reach 6 row then the program will add new line 
            if ((i + 1) % 6 == 0)
            {
                std::cout << '\n';
            }
        }
    }
}

#endif