//Header guard
#ifndef PASSANDPLAY_H
#define PASSANDPLAY_H

#include <iostream>
#include <string>
#include <vector>

namespace passAndPlay
{

    class Question
    {
    private:
        std::vector <std::string> ques;
        std::vector <std::string> quesAns;

    public:
        void addQuestions(std::string& question)
        {
            ques.push_back(question);
        }

        //for MCQ getting the correct answer
        void correctAnswer(std::string correctAns)
        {
            quesAns.push_back(correctAns);
        }

        //Randomizing the question 
        void randomizeQuestions(std::vector <std::string> randomQues)
        {
            srand(static_cast<unsigned int>(time(0)));
		        std::random_shuffle(randomQues.begin(), randomQues.end());
        }

        //Randomizing the question (//The option are not getting random i only randomize if to because if i did not the correct option will not work)
        void randomizeOption(std::vector <std::string> randOpt)
        {
            srand(static_cast<unsigned int>(time(0)));
		        std::random_shuffle(randOpt.begin(), randOpt.end());
        }
        
    };

    class PassAndPlay
    {
    private:
        //This is where variables should go 
        std::string playerNameOne{};
        std::string playerNameTwo{};
        
        int playerOneScore{};
        int playerTwoScore{};

        bool makeTurn = true;
        bool gameIsOver = true;

    public:
        void askPlayerName();
        void makeTurn();
        void performAskingUser(std::string&);
        void checkWinner();
        void CheckAnswers();
        void startGame();
        void questions();
    };
    
    //Ask player name
    void PassAndPlay::askPlayerName()
    {
        std::cout << "\nPlayer one name: ";
        std::getline(std::cin >> std::ws, playerNameOne); //Using std::ws to ignore leading whitespaces

        std::cout << "\nPlayer two name: ";
        std::getline(std::cin >> std::ws, playerNameTwo);
    }

    void PassAndPlay::makeTurn()
    {
        if (makeTurn)
        {
            performAskingUser(playerNameOne);
        }
    }

    void PassAndPlay::performAskingUser(std::string& turnPlayerName)
    {   
        char userChoice{};

        while (!gameIsOver)
        {
            std::cout << turnPlayerName << "it's your turn";
            questions();
            std::cout << "Select Option (A-B) or Enter to skip the question: ";
            std::cin >> userChoice;

            CheckAnswers(usechoice);
        }
    }

    void PassAndPlay::questions()
    {
        Question quessy;
        
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

        quessy.addQuestions(question01);
        quessy.addQuestions(question02);
        quessy.addQuestions(question03);
        quessy.addQuestions(question04);
        quessy.addQuestions(question05);
        quessy.addQuestions(question06);
        quessy.addQuestions(question07);
        quessy.addQuestions(question08);
        quessy.addQuestions(question09);
        quessy.addQuestions(question10);

        quessy.correctAnswer("d");
        quessy.correctAnswer("b");
        quessy.correctAnswer("b");
        quessy.correctAnswer("b");
        quessy.correctAnswer("a");
        quessy.correctAnswer("b");
        quessy.correctAnswer("c");
        quessy.correctAnswer("c");
        quessy.correctAnswer("c");
        quessy.correctAnswer("d");
    }

    void PassAndPlay::CheckAnswers(char ansChoice)
    {   
        Question quess;

        if ()
    }

    

}

#endif