//add header guard
#ifndef ADDQUESTION_H
#define ADDQUESTION_H

#include <iostream>
#include <fstream>  
#include <string>
#include <conio.h>

namespace addQuestionFile
{   
    class addQuestionToFile
    {
    private:
        std::ofstream outFile; 
        std::string fileName;
        std::string question;
        std::string option;
        char answer;
        int questionNumber{};
        int typeQues{};
 
        std::ofstream oFile;

    public:
        bool openTheFile();
        void askTypeOfQues(void (*func)(void));
        void addMultipleChoiceQues(void (*func)(void));
        void addIdentificationQues(void (*func)(void));

        HANDLE h = GetStdHandle(STD_OUTPUT_HANDLE);
    };

    bool addQuestionToFile::openTheFile()
    {   
        system("cls");
        essential::gotoXY(50, 5);
        std::cout << "Add File Name: ";
        std::cin >> fileName;

        //increment the .txt
        fileName += ".txt";

        oFile.open(fileName.c_str(), std::ios::out | std::ios::app);
        
        if (!oFile.is_open()) 
        {
            std::cout << "ERROR: we can't open file:" << fileName << '\n';
            return false;
        }

        else 
        {
            std::cout << "File " << oFile.is_open() << " is successfully open!\n";
            return true;
        }
    
    }   

    void addQuestionToFile::askTypeOfQues(void (*func)(void))
    {   
        system("cls");
        essential::gotoXY(50, 5);
        SetConsoleTextAttribute(h, 15);
        std::cout << "-=-=-=-= Choose type of Question =-=-=-=-";
        essential::gotoXY(50, 7);
        SetConsoleTextAttribute(h, 15);
        std::cout << "1--> Multiple Choices Questions";
        essential::gotoXY(50, 9);
        SetConsoleTextAttribute(h, 15);
        std::cout << "2--> Identification";
        essential::gotoXY(50, 11);
        SetConsoleTextAttribute(h, 15);
        std::cout << "Choice: ";
        std::cin >> typeQues;

        switch(typeQues)
        {
            case 1:
                addMultipleChoiceQues(func);
                break;
            case 2:
                addIdentificationQues(func);
                break;
        }
    }

    void addQuestionToFile::addMultipleChoiceQues(void (*func)(void))
    {   
        openTheFile();
        system("cls");
        essential::gotoXY(50, 5);
        SetConsoleTextAttribute(h, 15);
        std::cout << "Number of questions: ";
        std::cin >> questionNumber;  

        while ( !std::cin || questionNumber < 6 )
        {   
            system("cls");
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            essential::gotoXY(50, 5);
            std::cout << "Number of questions: ";
            std::cin >> questionNumber;  
        }
        
        essential::gotoXY(50, 7);
        SetConsoleTextAttribute(h, 15);
        std::cout << "Consider the following format";
        essential::gotoXY(50, 9);
        SetConsoleTextAttribute(h, 1);
        std::cout << "Question: ";
        essential::gotoXY(50, 11);
        SetConsoleTextAttribute(h, 7);
        std::cout << "Choice1:";
        essential::gotoXY(50, 12);
        SetConsoleTextAttribute(h, 7);
        std::cout << "Choice2: "; 
        essential::gotoXY(50, 13);
        SetConsoleTextAttribute(h, 7);
        std::cout << "Choice3: ";
        essential::gotoXY(50, 14);
        SetConsoleTextAttribute(h, 7);
        std::cout << "Choice4: ";
        essential::gotoXY(50, 16);
        SetConsoleTextAttribute(h, 7);
        std::cout << "Answer:";

        for (int i { 0 }; i < questionNumber; ++i)
        {   
            SetConsoleTextAttribute(h, 7);
            essential::gotoXY(50, 17);
            std::cout << "Press any key to next";  
            getch();
            system("cls");
            SetConsoleTextAttribute(h, 15);
            std::cout << "Please Enter The Question and Answer: \n";
            SetConsoleTextAttribute(h, 15);
            std::cout << "Queston #" << i + 1 << '\n';
            std::cin.get();
            std::getline(std::cin >> std::ws, question);
            oFile << question << std::endl;

            for (int x { 0 }; x < 4; ++x)
            {
                std::cin.get();
                std::getline(std::cin >> std::ws, option);
                oFile << option << std::endl;
            }
            
            std::cin >> answer;
            oFile << answer << std::endl;
        }

        essential::askToMenu(func);
        oFile.close();
    }

    void addQuestionToFile::addIdentificationQues(void (*func)(void))
    {   
        openTheFile();

        system("cls");
        std::cout << "Number of questions: ";
        std::cin >> questionNumber;  

        while ( !std::cin || questionNumber < 6 )
        {   
            system("cls");
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            essential::gotoXY(50, 5);
            SetConsoleTextAttribute(h, 15);
            std::cout << "Number of questions: ";
            std::cin >> questionNumber;  
        }

        essential::gotoXY(50, 5);
        SetConsoleTextAttribute(h, 15);
        std::cout << "Consider the following format" << '\n';
        essential::gotoXY(50, 7);
        SetConsoleTextAttribute(h, 1);
        std::cout << "\nQuestion: \n";
        essential::gotoXY(50, 9);
        SetConsoleTextAttribute(h, 7);
        std::cout << "\nAnswer:\n";

        for (int i { 0 }; i < questionNumber; ++i)
        {   
            SetConsoleTextAttribute(h, 1);
            essential::gotoXY(50, 10);
            std::cout << "Press any key to next";  
            getch();
            system("cls");
            SetConsoleTextAttribute(h, 15);
            std::cout << "Please Enter The Question and Choices: \n";
            SetConsoleTextAttribute(h, 15);
            std::cout << "Queston #" << i + 1 << '\n';
            std::cin.get();
            std::getline(std::cin >> std::ws, question);
            oFile << question << std::endl;
            //getting the answer
            std::cin >> answer;
            oFile << answer << std::endl;
        }

        essential::askToMenu(func);
       
        oFile.close();
    }
}

#endif