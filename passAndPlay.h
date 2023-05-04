//Header guard
#ifndef PASSANDPLAY_H
#define PASSANDPLAY_H

#include <iostream>
#include <string_view> //Using std::string_View instead of std::string to avoid expensive copy
#include <vector>
#include <algorithm> 
#include <string> //To use getline function
#include <windows.h> // for sleep function

#define TOTAL_SCORE 10

namespace passAndPlay
{
    class PassAndPlay
    {
    private:
        //This is where variables should go 
        std::string playerNameOne{};
        std::string playerNameTwo{};
        
        int playerOneScore{};
        int playerTwoScore{};

        bool makeTurn = true;

        std::string userInputtedAns{};

        //PlayerOne
        //This is where the question for player one store
        std::vector <std::string_view> ques;
        std::vector <std::string_view> quesAns;
        
        //PlayerTwo
        //This is where the question for player two store
        std::vector <std::string_view> questions;
        std::vector <std::string_view> questionsAnswer;

    public:
        void askPlayerName();
        void makeTurns();
        void performAskingUser(std::string_view);
        void startGame();
        void questionsOne(std::string_view);
        void questionsTwo(std::string_view);

        void addQuestionPOne(std::string_view idQues, std::string_view idAns)
        {
            ques.push_back(idQues);
            quesAns.push_back(idAns);
        }

        void addQuestionPTwo(std::string_view idQuesTwo, std::string_view idAnsTwo)
        {
            questions.push_back(idQuesTwo);
            questionsAnswer.push_back(idAnsTwo);
        }

        void displayQuestion(std::vector <std::string_view> correctAns, std::string_view playerNames, std::vector <std::string_view> quesToDis)
        {   
            for ( int x { 0 }; x < 10; ++x )
            {   
                // system("cls"); //Clear the screen before going to the next question
                
                std::cout << "\nQuestion #" << (x + 1) << '\n';
                std::cout << quesToDis[x];

                std::cout << "Select Option (A-B) or Enter to skip the question:";
                std::getline(std::cin >> std::ws, userInputtedAns);

                checkAnswer(userInputtedAns, correctAns, x, playerNames);
            }
        }

        void checkAnswer(std::string& choice, std::vector <std::string_view> correctAns, int index, std::string_view name)
        {   
            auto itOne = ques.begin();
            auto itTwo = questions.begin();

            auto itOneAns = quesAns.begin();
            auto itTwoAns = questionsAnswer.begin();

            if (choice == correctAns[index])
            {
                //erase question if the player pick the right answer
                (name == playerNameOne) ?  ques.erase(itOne) : questions.erase(itTwo);

                //erase the correct ans if the player pik the right answer
                (name == playerNameOne) ?  quesAns.erase(itOneAns) : questionsAnswer.erase(itTwoAns);
                
                //Increment score
                (name == playerNameOne) ? playerOneScore++ : playerTwoScore++;
            }

            //If the players choose the wrong answer the player will switch to another player
            else
            {
                if (name == playerNameOne)
                {
                    if (makeTurn)
                    {
                        makeTurn = false;
                        makeTurns();
                    }
                        
                    else
                    {
                        makeTurn = true;
                        makeTurns();
                    }  
                }

                else
                {
                    if (makeTurn) 
                    {
                        makeTurn = false;
                        makeTurns();
                    }
                        
                    else
                    {
                        makeTurn = true;
                        makeTurns();
                    }
                }
            }
        }

        void checkWinner()
        {
            if (playerOneScore == TOTAL_SCORE)
            {
                std::cout << playerNameOne << " You win!!!!";
            }
            
            else if (playerTwoScore == TOTAL_SCORE)
            {
                std::cout << playerNameOne << " You win!!!!";
            }
        }
    };

    void PassAndPlay::startGame()
    {
        askPlayerName();
        makeTurns();
    }
    
    //Ask player name
    void PassAndPlay::askPlayerName()
    {
        std::cout << "\nPlayer one name: ";
        std::getline(std::cin >> std::ws, playerNameOne); //Using std::ws to ignore leading whitespaces

        std::cout << "Player two name: ";
        std::getline(std::cin >> std::ws, playerNameTwo);

    }
    
    //this function allow us to maketurn for the players
    void PassAndPlay::makeTurns()
    {   
        if (makeTurn)
        {   
            performAskingUser(playerNameOne);
            checkWinner();
        }

        else
        {  
            performAskingUser(playerNameTwo);
            checkWinner();
        }
    }

    void PassAndPlay::performAskingUser(std::string_view turnPlayerName)
    {   
        std::string userChoice{};

        if (turnPlayerName == playerNameOne)
        {
            while (true)
            {
                std::cout << turnPlayerName << " it's your turn\n";
                questionsOne(turnPlayerName);
                break;
            }
        }

        else
        {
             while (true)
            {
                std::cout << turnPlayerName << "it's your turn\n";
                questionsTwo(turnPlayerName);
                break;
            }
        }
    }

    //this function hold the questions for player one
    void PassAndPlay::questionsOne(std::string_view pName)
    {        
        std::string
        question01 = "\nThis is a part of speech that shows the relationship of a noun or pronoun to another word. They can indicate time, place, or relationship.\n"
        " a) noun\n"
        " b) pronoun\n"
        " c) adjective\n"
        " d) preposition\n\n",
        question02 = "\nWhich word indicates correct spelling?\n"
        " a) belive\n"
        " b) believe \n"
        " c) bilieve\n"
        " d) beleive\n\n",
        question03 = "\n'The wind whisper to the trees as it creeps in the night' this is an example of what figure of speech?\n" 
        " a) smile\n" 
        " b) personification\n" 
        " c) metaphor\n" 
        " d) hyperbole\n\n",
        question04 = "\nThis is en element of poetry that pertain to the series of lines grouped together and separated by an empty line from other stanzas. They are the equivalent of a paragraph in an essay.\n"
        " a) rhyme\n"
        " b) stanza\n"
        " c) form\n"
        " d) meter\n\n",
        question05 = "\nA kind of sentence that makes a statement\n"
        " a) declarative\n" 
        " b) interrogative\n" 
        " c) imperative\n" 
        " d) exclamatory\n\n",
        question06 = "\nThis pertains to the prosodic feature of speech that is the relative emphasis or prominence given to a certain syllable in a word, or to a certain word in a phrase or sentence\n" 
        " a) pause\n" 
        " b) stress\n" 
        " c) intonation\n" 
        " d) pitch\n\n",
        question07 = "\nthe most important element of a story; they were the ones who play certain roles and acts in the story itself.\n" 
        " a) plot\n" 
        " b) settings\n" 
        " c) characters\n" 
        " d) theme\n\n",
        question08 = "\nWhat _______ when I called?\n"
        " a) Was you doing\n"
        " b) Was you do\n"
        " c) Were you doing\n"
        " d) You were doing\n\n",
        question09 = "\nWhat is the study of languages?\n"
        " a) Phonetics\n" 
        " b) Syntax\n"   
        " c) Linguistics\n" 
        " d) Semantics\n\n",
        question10 = "\nPhonetics is the study of the sounds of language. What do we call these sounds?\n" 
        " a) Morphemes\n" 
        " b) Syntax\n" 
        " c) Lexicology\n" 
        " d) Phonemes\n\n";

       addQuestionPOne(question01, "d");
       addQuestionPOne(question02, "b");
       addQuestionPOne(question03, "b");
       addQuestionPOne(question04, "b");
       addQuestionPOne(question05, "a");
       addQuestionPOne(question06, "b");
       addQuestionPOne(question07, "c");
       addQuestionPOne(question08, "c");
       addQuestionPOne(question09, "c");
       addQuestionPOne(question10, "d");

    //     //Randomizing the questions
    //    srand(static_cast<unsigned int>(time(0)));
	//    std::random_shuffle(ques.begin(), ques.end());

       displayQuestion(quesAns, pName, ques);
    }    

    //This function hold the questions for player two
    void PassAndPlay::questionsTwo(std::string_view pNames)
    {        
        std::string
        question1 = "\nThis is a part of speech that shows the relationship of a noun or pronoun to another word. They can indicate time, place, or relationship.\n"
        " a) noun\n"
        " b) pronoun\n"
        " c) adjective\n"
        " d) preposition\n\n",
        question2 = "\nWhich word indicates correct spelling?\n"
        " a) belive\n"
        " b) believe \n"
        " c) bilieve\n"
        " d) beleive\n\n",
        question3 = "\n'The wind whisper to the trees as it creeps in the night' this is an example of what figure of speech?\n" 
        " a) smile\n" 
        " b) personification\n" 
        " c) metaphor\n" 
        " d) hyperbole\n\n",
        question4 = "\nThis is en element of poetry that pertain to the series of lines grouped together and separated by an empty line from other stanzas. They are the equivalent of a paragraph in an essay.\n"
        " a) rhyme\n"
        " b) stanza\n"
        " c) form\n"
        " d) meter\n\n",
        question5 = "\nA kind of sentence that makes a statement\n"
        " a) declarative\n" 
        " b) interrogative\n" 
        " c) imperative\n" 
        " d) exclamatory\n\n",
        question6 = "\nThis pertains to the prosodic feature of speech that is the relative emphasis or prominence given to a certain syllable in a word, or to a certain word in a phrase or sentence\n" 
        " a) pause\n" 
        " b) stress\n" 
        " c) intonation\n" 
        " d) pitch\n\n",
        question7 = "\nthe most important element of a story; they were the ones who play certain roles and acts in the story itself.\n" 
        " a) plot\n" 
        " b) settings\n" 
        " c) characters\n" 
        " d) theme\n\n",
        question8 = "\nWhat _______ when I called?\n"
        " a) Was you doing\n"
        " b) Was you do\n"
        " c) Were you doing\n"
        " d) You were doing\n\n",
        question9 = "\nWhat is the study of languages?\n"
        " a) Phonetics\n" 
        " b) Syntax\n"   
        " c) Linguistics\n" 
        " d) Semantics\n\n",
        questionI0 = "\nPhonetics is the study of the sounds of language. What do we call these sounds?\n" 
        " a) Morphemes\n" 
        " b) Syntax\n" 
        " c) Lexicology\n" 
        " d) Phonemes\n\n";

       addQuestionPTwo(question1, "d");
       addQuestionPTwo(question2, "b");
       addQuestionPTwo(question3, "b");
       addQuestionPTwo(question4, "b");
       addQuestionPTwo(question5, "a");
       addQuestionPTwo(question6, "b");
       addQuestionPTwo(question7, "c");
       addQuestionPTwo(question8, "c");
       addQuestionPTwo(question9, "c");
       addQuestionPTwo(questionI0, "d");

    //     //Randomizing the questions
    //    srand(static_cast<unsigned int>(time(0)));
	//    std::random_shuffle(ques.begin(), ques.end());

       displayQuestion(questionsAnswer, pNames, questions);
    }    
}

#endif