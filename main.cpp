#include <iostream>
#include "classicMode.h"
#include "passAndPlay.h"
#include "timeTrialMode.h"
#include "survivalMode.h"
#include "essential.h"

//This class is responsible for mainmenu
class MainMenu
{
private:
    int userChoice{};
    int choice{};

public:
    void mainMenu()
    {
        std::cout << "\n=-=-=-=- Select -=-=-=-=\n"
                  << "\n[1] Start quiz"
                  << "\n[2] Exit\n"
                  << "\nChoice: ";
    }

    void selectMenu()
    {   
        mainMenu();
        std::cin >> userChoice;
    
        switch (userChoice)
        {
            case 1: 
                selectMode();
                break;
            case 2:
                break;

            default:
                break;
        }
    }

    void selectMode()
    {
        classicMode::ClassicMode classic;
        passAndPlay::PassAndPlay pAndP;
        timeTrialModes::TimeTrialMode timeMode;
        survivalModes::SurvivalMode surMode;
        
        std::cout << "\n=-=-=-=- Select -=-=-=-=\n"
                  << "\n[1] Classic"
                  << "\n[2] Time Trial"
                  << "\n[3] Pass and play"
                  << "\n[4] Survival\n"
                  << "\nChoice: ";

        std::cin >> choice;
        switch (choice)
        {
            case 1: 
                classic.startGame();
                break;

            case 2:
                 timeMode.startQuiz();
                 break;
                
                break;
            case 3:
                pAndP.startGame();
                break;
            
            case 4:
                surMode.startQuiz();

            default:
                break;
        }
    }
};

int main()
{
    MainMenu menu;
    
    essential::loading();
    essential::setcolor(essential::WHITE);
    system("cls");
    menu.selectMenu();

    return 0;
}