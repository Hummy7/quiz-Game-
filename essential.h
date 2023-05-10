//Header guard
#ifndef ESSENTIAL_H
#define ESSENTIAL_H

#include <iostream>
#include <windows.h>
#include <stdio.h>

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

    void ebod()
    {
 			
		for(int x = 20; x < 103; x++)
        {
            setcolor(CYAN);
            gotoXY(x,4);	
            std::cout<<char(205);
		}

		for(int x = 20; x < 103; x++)
        {
			setcolor(PURPLE);
			gotoXY(x,12);	
			std::cout<<char(205);
		}

		for(int x = 5; x < 12; x++)
        {
			setcolor(CYAN);
			gotoXY(20,x);	
		    std::cout<<char(186);
		}

		for(int x = 5; x < 12; x++)
        {
            setcolor(CYAN);
            gotoXY(103,x);	
            std::cout<<char(186);
		}
			setcolor(CYAN);

		gotoXY(20,4);	
		std::cout<<char(201);
		gotoXY(103,4);	
		std::cout<<char(187);
		gotoXY(103,12);	
		std::cout<<char(188);
		gotoXY(20,12);	
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
}

#endif