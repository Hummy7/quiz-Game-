#include <iostream>
#include "classicMode.h"
#include "passAndPlay.h"
#include "timeTrialMode.h"
#include "survivalMode.h"
#include "essential.h"
#include "userGameHistory.h"
#include "addQuestion.h"

//This class is responsible for mainmenu
void selectMenu();
void titleScreen();
HANDLE h = GetStdHandle(STD_OUTPUT_HANDLE);

class MainMenu
{
private:
    int userChoice{};
    int choice{};

public:

    void mainMenu()
    {    
        essential::gotoXY(50, 8);
        SetConsoleTextAttribute(h, 15);
        std::cout << "=-=-=-=- Select -=-=-=-=";
        essential::gotoXY(55, 10);
        SetConsoleTextAttribute(h, 15);
        std::cout << "1--> Start quiz";
        essential::gotoXY(55, 12);
        SetConsoleTextAttribute(h, 15);
        std::cout << "2--> Instruction";
        essential::gotoXY(55, 14);
        SetConsoleTextAttribute(h, 15);
        std::cout << "3--> Game History";
        essential::gotoXY(55, 16);
        SetConsoleTextAttribute(h, 15);
        std::cout << "4--> Custom Question";
        essential::gotoXY(55, 18);
        SetConsoleTextAttribute(h, 15);
        std::cout << "5--> Exit";
        essential::gotoXY(55, 20);
        SetConsoleTextAttribute(h, 15);
        std::cout << "Choice: ";
    }
    
    void selectMode()
    {
        classicMode::ClassicMode classic;
        passAndPlay::PassAndPlay pAndP;
        timeTrialModes::TimeTrialMode timeMode;
        survivalModes::SurvivalMode surMode;

        system("cls");
        titleScreen();
        dogDesign();

        essential::gotoXY(50, 8);
        SetConsoleTextAttribute(h, 15);
        std::cout << "=-=-=-=- Select Mode -=-=-=-=";
        essential::gotoXY(56, 10);
        SetConsoleTextAttribute(h, 15);
        std::cout << "1--> Classic";
        essential::gotoXY(56, 12);
        SetConsoleTextAttribute(h, 15);
        std::cout << "2--> Time Trial";
        essential::gotoXY(56, 14);
        SetConsoleTextAttribute(h, 15);
        std::cout << "3--> Pass and play";
        essential::gotoXY(56, 16);
        SetConsoleTextAttribute(h, 15);
        std::cout << "4--> Survival";
        essential::gotoXY(56, 18);
        SetConsoleTextAttribute(h, 15);
        std::cout << "5--> Menu ";
        essential::gotoXY(56, 20);
        SetConsoleTextAttribute(h, 15);
        std::cout << "choice: ";
        std::cin >> choice;

        switch (choice)
        {
            case 1: 
                classic.startGame(&selectMenu);
                break;

            case 2:
                timeMode.startQuiz(&selectMenu);
                break;
                   
            case 3:
                pAndP.startGame(&selectMenu);
                break;
                
            case 4:
                surMode.startQuiz(&selectMenu);
                break;

            default:
                //if the user select the wrong input it will start in the begining of selecting mode
                selectMode();
                break;
        }
    }

    void gameInstruction()
    {   
        system("cls");
        essential::gotoXY(56,4);	
         SetConsoleTextAttribute(h, 11);
        std::cout << "Game Instructions";
        essential::gotoXY(50,5);	
        
        SetConsoleTextAttribute(h, 10);
    	essential::gotoXY(38,6);	
		std::cout<<"   ________________________________________"<< '\n';
		essential::gotoXY(38,7);
		std::cout <<" / \\                             	         \\."<< '\n';
		essential::gotoXY(38,8);
		std::cout <<"|   |                                         |."<< '\n';
		essential::gotoXY(38,9);
		std::cout <<" \\_ | Select==>                               |."<< '\n';
		essential::gotoXY(38,10);
		std::cout <<"    | Press only Valid Opton--> (a,b,c,d)     |."<< '\n';
		essential::gotoXY(38,11);
		std::cout <<"    | if u Press Other key consider wrong     |."<< '\n';
		essential::gotoXY(38,12);
		std::cout <<"    | answer.                                 |."<< '\n';
		essential::gotoXY(38,13);
		std::cout <<"    |                            	   	       |."<< '\n';
		essential::gotoXY(38,14);
		std::cout <<"    | Skip==>                                 |."<< '\n';
		essential::gotoXY(38,15);
		std::cout <<"    | Press Enter to Skip the Question        |."<< '\n';
		essential::gotoXY(38,16);
		std::cout <<"    |                            	           |."<< '\n';
		essential::gotoXY(38,17);
		std::cout <<"    | Points==>                               |."<< '\n';
		essential::gotoXY(38,18);
		std::cout <<"    | 10 Point will be awarded for each       |."<< '\n';
		essential::gotoXY(38,19);
		std::cout <<"    | correct answer.                         |."<< '\n';
		essential::gotoXY(38,20);
		std::cout <<"    |                                         |."<< '\n';
		essential::gotoXY(38,21);
		std::cout <<"    | Time Trial Mode==>                      |."<< '\n';
		essential::gotoXY(38,22);
		std::cout <<"    | Player will be given 60 seconds for     |."<< '\n';
		essential::gotoXY(38,23);
		std::cout <<"    | each question.                          |."<< '\n';
		essential::gotoXY(38,24);
		std::cout <<"    |                            	           |."<< '\n';
		essential::gotoXY(38,25);
		std::cout <<"    | Survival Mode==>                        |."<< '\n';
		essential::gotoXY(38,26);
		std::cout <<"    | Player will be given 4 lives per game   |."<< '\n';
		essential::gotoXY(38,27);
		std::cout <<"    | save                          	       |."<< '\n';
		essential::gotoXY(38,28);
		std::cout <<"    |   ______________________________________|."<< '\n';
		essential::gotoXY(38,29);
		std::cout <<"    |  /                                      /."<< '\n';
		essential::gotoXY(38,30);
		std::cout <<"    \\_/______________________________________/."<< '\n';

        getch();
        SetConsoleTextAttribute(h, 15);
        std::cout << "Press Enter to Home Menu" << '\n';
        selectMenu();
    }

    void dogDesign()
    {   
        essential::gotoXY(73, 22);
        SetConsoleTextAttribute(h, 5);
        std::cout <<R"(     |\_/|                 )";
        essential::gotoXY(73, 23);
        SetConsoleTextAttribute(h, 5);
        std::cout <<R"(     | @ @   Welcome!!     )";
        essential::gotoXY(73, 24);
        SetConsoleTextAttribute(h, 5);
        std::cout <<R"(     |   <>              _ )";
        essential::gotoXY(73, 25);
        SetConsoleTextAttribute(h, 5);
        std::cout <<R"(     |  _/\------____ ((| |)))";
        essential::gotoXY(73, 26);
        SetConsoleTextAttribute(h, 5);
        std::cout <<R"(     |               `--' |)"; 
        essential::gotoXY(73, 27);
        SetConsoleTextAttribute(h, 5);
        std::cout <<R"( ____|_       ___|   |___.')"; 
        essential::gotoXY(73, 28);
        SetConsoleTextAttribute(h, 5);
        std::cout <<R"(/_/_____/____/_______|)";
    }
};

void selectMenu()
{   
    int userChoice;
    addQuestionFile::addQuestionToFile addQues;
    gameHistory::StudentGameHistory sg;
    titleScreen();
    MainMenu menuAccess;
    menuAccess.dogDesign();

    menuAccess.mainMenu();
    std::cin >> userChoice;
        
    switch (userChoice)
    {
        case 1: 
            menuAccess.selectMode();
            break;
            
        case 2:
            menuAccess.gameInstruction();
            break;

        case 3:
            sg.displayStudentData(&selectMenu);
            break;

        case 4:
            addQues.askTypeOfQues(&selectMenu);
            break;
        
        case 5:
            std::cout << "THANK YOU FOR PLAYING!";
            std::exit(0); //exit the program
            break;

        default:
            selectMenu(); // if the user input the wrong input the program wil ask again
            break;
    }
}

void titleScreen()
{
system("cls");
essential::gotoXY(29, 1);
SetConsoleTextAttribute(h, 1);
std::cout <<R"(________        .__                  __      __.__                                 .___)";
essential::gotoXY(29, 2);
SetConsoleTextAttribute(h, 1);
std::cout <<R"(\_____  \  __ __|__|_______________ /  \    /  \__|____________________ _______  __| _/)";
essential::gotoXY(29, 3);
SetConsoleTextAttribute(h, 1);
std::cout <<R"( /  / \  \|  |  \  \___   /\___   / \   \/\/   /  \___   /\___   /\__  \\_  __ \/ __ | )";
essential::gotoXY(29, 4);
SetConsoleTextAttribute(h, 1);
std::cout <<R"(/   \_/.  \  |  /  |/    /  /    /   \        /|  |/    /  /    /  / __ \|  | \/ /_/ |)";
essential::gotoXY(29, 5);
SetConsoleTextAttribute(h, 1);
std::cout <<R"(\_____\ \_/____/|__/_____ \/_____ \   \__/\  / |__/_____ \/_____ \(____  /__|  \____ |)";
essential::gotoXY(29, 6);
SetConsoleTextAttribute(h, 1);
std::cout <<R"(       \__>              \/      \/        \/           \/      \/     \/           \/)"; 

}

int main()
{   
    essential::loading();
    gameHistory::StudentGameHistory sg;

    MainMenu menu;
    essential::setcolor(essential::WHITE);
    system("cls");
    sg.getStudentInfo();
    selectMenu();
}

//TODO: this is what i should do first
//??Add error handling
//TODO: add limitation in quiz 
        //if quiz is less than 5 then user can't load the file
        //Adding question in file if the use enter the same question in the file user can't add the question
//TODO: fix the position and color of each text
//TODO: finish the unfinish code in tsome of the mode
//TODO: refactor the code
//TODO: make the essential header more organize


//??
//TODO: Need to create an instruction 

//TODO: Need to create an about section

//TODO: add a functionality in each mode in which the program will ask the user what type of question does the user want

//TODO: create feature in which the teacher / user can search for certain student and see result only for that student

//TODO: I need to create a feature in which the student can choose to see his result only and also see all of the result

//TODO:Finish all the design and of course the main menu