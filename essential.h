//Header guard
#ifndef ESSENTIAL_H
#define ESSENTIAL_H

#include <iostream>
#include <windows.h>
#include <stdio.h>
#include <random>
#include <vector>

namespace essential
{
    enum color
    { //enumeration is a user-defined data type
        NONE,
        DARK_BLUE,
        GREEN,
        DARK_CYAN,
        DARK_RED,
        PURPLE,
        DARK_YELLOW,
        NORMAL,
        GRAY,
        BLUE,
        LIME,
        CYAN,
        RED,
        PINK,
        YELLOW,
        WHITE
    };

    void ebod();
    void setcolor(color newColor);
    void gotoXY(int x, int y);
    void borderTwo();
    void ebodTwo();
    void border();
    void asciiArtResult(void (*mainMenu)(void));
    void askToMenu(void (*menu)(void));
    void asciiArtGameOver(void (*func)(void));

    void ebodTwo()
    {
 			
		for(int x = 20; x < 103; x++)
        {
            setcolor(DARK_CYAN);
            gotoXY(x,7);	
            std::cout<<char(205);
		}

		for(int x = 8; x < 13; x++)
        {
			setcolor(DARK_CYAN);
			gotoXY(20,x);	
		    std::cout<<char(186);
		}

		for(int x = 8; x < 13; x++)
        {
            setcolor(DARK_CYAN);
            gotoXY(103,x);	
            std::cout<<char(186);
		}
			setcolor(DARK_CYAN);

		gotoXY(20,7);	
		std::cout<<char(201);
		gotoXY(103,7);	
		std::cout<<char(187);
		gotoXY(103,13);	
		std::cout<<char(188);
		gotoXY(20,13);	
		std::cout<<char(200);
    }

    void ebod()
    {
 			
		for(int x = 20; x < 103; x++)
        {
            setcolor(DARK_CYAN);
            gotoXY(x,4);	
            std::cout<<char(205);
		}

		for(int x = 20; x < 103; x++)
        {
			setcolor(PURPLE);
			gotoXY(x,13);	
			std::cout<<char(205);
		}

		for(int x = 5; x < 13; x++)
        {
			setcolor(DARK_CYAN);
			gotoXY(20,x);	
		    std::cout<<char(186);
		}

		for(int x = 5; x < 13; x++)
        {
            setcolor(DARK_CYAN);
            gotoXY(103,x);	
            std::cout<<char(186);
		}
			setcolor(DARK_CYAN);

		gotoXY(20,4);	
		std::cout<<char(201);
		gotoXY(103,4);	
		std::cout<<char(187);
		gotoXY(103,13);	
		std::cout<<char(188);
		gotoXY(20,13);	
		std::cout<<char(200);
    }

    void borderTwo()
    {
        for(int x = 13; x < 16; x++)
        {
            setcolor(DARK_CYAN);
            gotoXY(20,x);	
            std::cout<<char(186);
        }

        for(int x = 20; x < 103; x++)
        {
            setcolor(DARK_CYAN);
            gotoXY(x,16);	
            std::cout<<char(205);
        }

        for(int x = 13; x < 16; x++)
        {
            setcolor(DARK_CYAN);
            gotoXY(103,x);	
            std::cout<<char(186);
        }

        essential::setcolor(essential::DARK_CYAN);
        gotoXY(103,16);	
        std::cout<<char(188);
        gotoXY(20,16);	
        std::cout<<char(200);

    }

    void border()
    {
        for(int x = 13; x < 16; x++)
        {
            setcolor(DARK_CYAN);
            gotoXY(20,x);	
            std::cout<<char(186);
        }

        for(int x = 20; x < 103; x++)
        {
            setcolor(DARK_CYAN);
            gotoXY(x,16);	
            std::cout<<char(205);
        }

        for(int x = 13; x < 16; x++)
        {
            setcolor(DARK_CYAN);
            gotoXY(103,x);	
            std::cout<<char(186);
        }

        essential::setcolor(essential::DARK_CYAN);
        gotoXY(103,16);	
        std::cout<<char(188);
        gotoXY(20,16);	
        std::cout<<char(200);

    }


    void setcolor(color newColor) 
    {
        //A "handle" is a generic identifier (typically a pointer) used to represent something.
        SetConsoleTextAttribute( GetStdHandle(STD_OUTPUT_HANDLE), (newColor ) );
    }

    void gotoXY(int x, int y) 	//function to decide location of the screem
    {
        HANDLE console = GetStdHandle(STD_OUTPUT_HANDLE); 		 
        COORD CursorPosition; 
        CursorPosition.X = x; // Locates column
        CursorPosition.Y = y; // Locates Row
            
        SetConsoleCursorPosition(console,CursorPosition); // Sets position for next thing to be printed 
    }

    void loading()
    {
        
        // Clear the console screen
        system("cls");

        // Enable VT100 terminal emulation to support special characters
        printf("\e[?251]");

        // Set ASCII to print special character.
        // Code page 437
        SetConsoleCP(437);
        SetConsoleOutputCP(437);

        // Define the characters for the loading bar
        int bar1 = 176, bar2 = 219;

        // Print the loading message
        gotoXY(50, 12);
        setcolor(BLUE);
        std::cout << "Loading. . . . .";

        // Print the empty loading bar
        gotoXY(50,  10);
        setcolor(BLUE);
        for(int i = 0; i < 25; i++)
            std::cout << (char)bar1;

        // Move the cursor back to the beginning of the loading bar
        std::cout << "\r";
        std::cout << "\t\t";

        // Print the filled loading bar
        gotoXY(50, 10);
        setcolor(BLUE);
        for(int i = 0; i < 25; i++)
        {
            std::cout << (char)bar2;
            // Wait for a short period of time to simulate the loading process
            Sleep(150);
        }
    }

    void asciiArtGameOver(void (*func)(void))
    {  
        ebodTwo();
        border();

        gotoXY(29,1);
        essential::setcolor(essential::RED);
        std::cout <<R"( _____                        _____                )";
        gotoXY(29,2);
        essential::setcolor(essential::RED);
        std::cout <<R"(|  __ \                      |  _  |               )";
        gotoXY(29,3);
        essential::setcolor(essential::RED);
        std::cout <<R"(| |  \/ __ _ _ __ ___   ___  | | | |_   _____ _ __ )";
        gotoXY(29,4);
        essential::setcolor(essential::RED);
        std::cout <<R"(| | __ / _` | '_ ` _ \ / _ \ | | | \ \ / / _ \ '__|)";
        gotoXY(29,5);
        essential::setcolor(essential::RED);
        std::cout <<R"(| |_\ \ |_| | | | | | |  __/ \ \_/ /\ V /  __/ |)";
        gotoXY(29,6);
        essential::setcolor(essential::RED);
        std::cout <<R"(\____/\__,_|_| |_| |_|\___|   \___/  \_/ \___|_|)";

        askToMenu(func);
    }

    void askToMenu(void (*menu)(void)) //passing the function as parameter using pointers
    {   
        char choiceUser{};

        do 
        {   
            gotoXY(55, 17);
            std::cout << "Do you want to continue (y/n): ";
            std::cin >> choiceUser;

        }while(choiceUser != 'y' && choiceUser != 'n');

        if (choiceUser == 'y')
        {   
            menu();
        }

        else
        {
            std::exit(0);
        }
    }

    void asciiArtResult(void (*mainMenu)(void))
    {
        ebodTwo();
        border();

        gotoXY(29,1);
        essential::setcolor(essential::GREEN);
        std::cout <<R"(______ _____ _____ _   _ _    _____ )";
        gotoXY(29,2);
        essential::setcolor(essential::GREEN);
        std::cout <<R"(| ___ \  ___/  ___| | | | |  |_   _|)";
        gotoXY(29,3);
        essential::setcolor(essential::GREEN);
        std::cout <<R"(| |_/ / |__ \ `--.| | | | |    | |)"; 
        gotoXY(29,4);
        essential::setcolor(essential::GREEN);
        std::cout <<R"(|    /|  __| `--. \ | | | |    | |)";
        gotoXY(29,5);
        essential::setcolor(essential::GREEN);
        std::cout <<R"(| |\ \| |___/\__/ / |_| | |____| |)";
        gotoXY(29,6);
        essential::setcolor(essential::GREEN);
        std::cout <<R"(\_| \_\____/\____/ \___/\_____/\_/)";

        askToMenu(mainMenu); 
    }

    //this function is responsible for randoming the quetsion
    std::mt19937 randomingQuestion() 
    {
        std::random_device rd;
	    std::seed_seq ss{ rd(), rd(), rd(), rd(), rd(), rd(), rd(), rd() }; 
        std::mt19937 mt{ ss };

        return mt;
    }
}

#endif