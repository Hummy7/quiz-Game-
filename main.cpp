#include <iostream>
#include "classicMode.h"
#include "passAndPlay.h"
#include "timeTrialMode.h"

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
        timeTrialMode::TimeTrialMode timeMode;

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
            case 3:
                pAndP.startGame();

            default:
                break;
        }
    
    }
};

int main()
{
    MainMenu menu;

    menu.selectMenu();

    return 0;
}