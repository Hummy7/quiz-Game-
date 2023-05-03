//This i s a header guard
#ifndef CLASSICMODE_H
#define CLASSICMODE_H

#include <iostream>
#include <vector>
#include <algorithm>
#include <string_view>
#include <cstdlib>

//Adding namespace to avoid naming collision
namespace classicMode
{
    class ClassicMode
    {
    private:
        int userChoice{};
        int playerScore{};
        std::string userInputtedAns{};

        //For multiple choice
        std::vector <std::string_view> questionsMCQ;
        std::vector <std::string_view> questionAnsMCQ;

        //for identification
        std::vector <std::string_view> questionsID;
        std::vector <std::string_view> questionAnsID;

    public:
        void startGame();
        void askDifficulty();
        void easyDiff();
        void mediumDiff();
        void hardDiff();
        void displayScore();
        
        //for identification
        void addQuestionsID(std::string_view idQues, std::string_view idAns)
        {
            questionsID.push_back(idQues);
            questionAnsID.push_back(idAns);
        }

        void addQuestionsMCQ(std::string_view quesMCQ, std::string_view ansMCQ)
        {
            questionsMCQ.push_back(quesMCQ);
            questionAnsMCQ.push_back(ansMCQ);
        }

        //Displaying the question for multiple choice
        std::string displayQuestion(std::vector <std::string_view> disQues, std::vector <std::string_view> cAns)
        {    
            for ( int x { 0 }; x < 10; ++x )
            {
                std::cout << "\nQuestion #" << (x + 1) << '\n';
                std::cout << disQues[x];

                std::cout << "Select Option (A-B) or Enter to skip the question:";
                std::getline(std::cin >> std::ws, userInputtedAns);

                checkAnswer(userInputtedAns, cAns, x);
            }
        }

        //Check the input of the user 
        void checkAnswer(std::string& userAns, std::vector <std::string_view> correctAns, int index)
        {   
            if (userAns == correctAns[index])
            {
                std::cout << "Great job! you selected the Right Answer.\n";
			    system("pause"); //Pause the progam
            }

            else if (userAns != correctAns[index])
            {
                std::cout << "You selected the wrong answer!!\n";
                std::cout << "The corerct answer is ---> " << correctAns[index] << '\n';
                system("pause");
            }
        }
    };

    void ClassicMode::startGame()
    { 
        askDifficulty();
    }

    void ClassicMode::askDifficulty()
    {
        std::cout << "\n -=-=-=-=- Select Difficulty -=-=-=-=-=\n";
        std::cout << "\n[1] Easy"
                  << "\n[2] Medium"
                  << "\n[3] Hard"
                  << "\n[4] Home\n"
                  << "\nChoice: ";
        std::cin >> userChoice; 

        switch (userChoice)
        {
            case 1:
              easyDiff();
              break;

            case 2:
              mediumDiff();
              break;

            case 3:
              hardDiff();
              break;

            case 4:
              break; 
        
            default:
              break;
        }
    }

    void ClassicMode::easyDiff()
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

        //Pushing back the question on vector
        addQuestionsMCQ(question01, "d");
        addQuestionsMCQ(question02, "b");
        addQuestionsMCQ(question03, "b");
        addQuestionsMCQ(question04, "b");
        addQuestionsMCQ(question05, "a");
        addQuestionsMCQ(question06, "b");
        addQuestionsMCQ(question07, "c");
        addQuestionsMCQ(question08, "c");
        addQuestionsMCQ(question09, "c");
        addQuestionsMCQ(question10, "d");

        srand(static_cast<unsigned int>(time(0)));
		std::random_shuffle(questionsMCQ.begin(), questionsMCQ.end());

        srand(static_cast<unsigned int>(time(0)));
		std::random_shuffle(questionAnsMCQ.begin(), questionAnsMCQ.end());

        displayQuestion(questionsMCQ, questionAnsMCQ);

    }

    void ClassicMode::mediumDiff()
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
        " d) exclamatory\n\n";

        addQuestionsID(question1, "d");
        addQuestionsID(question2, "b");
        addQuestionsID("The ____ keyword is used to indicate that a function does not return a value.", "void");
        addQuestionsID(question3, "b");
        addQuestionsID("What is the world wide web? _____", "WWW");
        addQuestionsID(question4, "c");
        addQuestionsID("Who is mark ghian francis?", "pogi");
        addQuestionsID(question5, "c");
        addQuestionsID("Meaning of ILY?", "i love you");

        srand(static_cast<unsigned int>(time(0)));
		std::random_shuffle(questionsID.begin(), questionsID.end());

        srand(static_cast<unsigned int>(time(0)));
		std::random_shuffle(questionAnsID.begin(), questionAnsID.end());

        displayQuestion(questionsID, questionAnsID);
    }

    void ClassicMode::hardDiff()
    {
        addQuestionsID("The ____ keyword is used to indicate that a function does not return a value.", "void");
        addQuestionsID("A ______ is a variable that holds the memory address of another variable.", "pointer");
        addQuestionsID("The ____ operator is used to obtain the address of a variable.", "address-of operator");
        addQuestionsID("The ___________ is used to access the value of a variable that is pointed to by a pointer.", "dereference");
        addQuestionsID("The _____ function is used to compare two strings and returns an integer that indicates their relationship.", "strcmp");
        addQuestionsID("A ______ is a named section of a program that performs a specific task and can be reused.?", "function");
        addQuestionsID("The ______ keyword is used to allocate memory for a variable or array at runtime.", "new");
        addQuestionsID("To read a line of text from a file using C++ file handling, the function to use is _____", "getline");
        addQuestionsID("A ______ is a function that calls itself, either directly or indirectly.", "recursive");
        addQuestionsID("In C++, a pointer variable holds the ________ of a variable.", "memory address");

        srand(static_cast<unsigned int>(time(0)));
		std::random_shuffle(questionsID.begin(), questionsID.end());

        srand(static_cast<unsigned int>(time(0)));
		std::random_shuffle(questionAnsID.begin(), questionAnsID.end());

        displayQuestion(questionsID, questionAnsID);
    }

    void ClassicMode::displayScore()
    {

    }
}

#endif


