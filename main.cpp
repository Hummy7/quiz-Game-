#include <iostream>
// #include "passAndPlay.h"
#include "classicMode.h"

//This class is responsible for mainmenu
class MainMenu
{
private:
    int userChoice{};

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
        classicMode::ClassicMode classic;
        mainMenu();
        std::cin >> userChoice;
    
        switch (userChoice)
        {
            case 1: 
                classic.startGame();
                break;
        
            default:
                break;
        }
    }

    void selectMode()
    {
        std::cout << "\n=-=-=-=- Select -=-=-=-=\n"
                  << "\n[1] Classic"
                  << "\n[2] Time Trial"
                  << "\n[3] Pass and play"
                  << "\n[4] Survival\n"
                  << "\nChoice: ";
    }
};

int main()
{
    MainMenu menu;

    menu.selectMenu();

    return 0;
}