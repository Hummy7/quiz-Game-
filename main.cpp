#include <iostream>
#include "classicMode.h"
#include "passAndPlay.h"
#include "timeTrialMode.h"
#include "survivalMode.h"
#include "essential.h"

//This class is responsible for mainmenu
void selectMenu();

class MainMenu
{
private:
    int userChoice{};
    int choice{};

public:
    void mainMenu()
    {   
        system("cls");
        essential::gotoXY(50, 5);
        std::cout << "=-=-=-=- Select -=-=-=-=";
        essential::gotoXY(55, 7);
        std::cout << "[1] Start quiz";
        essential::gotoXY(55, 9);
        std::cout << "[2] Exit";
        essential::gotoXY(55, 11);
        std::cout << "Choice: ";
    }
    
    void selectMode()
    {
        classicMode::ClassicMode classic;
        passAndPlay::PassAndPlay pAndP;
        timeTrialModes::TimeTrialMode timeMode;
        survivalModes::SurvivalMode surMode;
            
        system("cls");
        essential::gotoXY(50, 5);
        std::cout << "=-=-=-=- Select -=-=-=-=";
        essential::gotoXY(55, 7);
        std::cout << "[1] Classic";
        essential::gotoXY(55, 9);
        std::cout << "[2] Time Trial";
        essential::gotoXY(55, 11);
        std::cout << "[3] Pass and play";
        essential::gotoXY(55, 13);
        std::cout << "[4] Survival";
        essential::gotoXY(55, 15);
        std::cout << "Choice: ";
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
                break;
        }
    }
};

void selectMenu()
{   
    int userChoice;

    MainMenu menuAccess;

    menuAccess.mainMenu();
    std::cin >> userChoice;
        
    switch (userChoice)
    {
        case 1: 
            menuAccess.selectMode();
            break;
        case 2:
            break;

        default:
            break;
    }
}

int main()
{
    // essential::loading();

    MainMenu menu;
    essential::setcolor(essential::WHITE);
    system("cls");
    selectMenu();
}
