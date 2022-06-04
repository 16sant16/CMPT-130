#include <iostream>
#include <cmath>
#include <ctime>
#include <cstdlib>
#include <iomanip>
#include <ctime>
#include <string>
using namespace std;

//Function Prototypes
void printOnes (int num);
void printFives (int num);
void printOnesAndFives (int num);
int placeValueInMayan(int num);
void printMayanNumber(int num);
int randNum(int min, int max);
int randIncorrectAns(int answer);
bool compareValues(int valueOne, int valueTwo, int valueThree);
char presentOptions(int ans, int wrongAnsOne, int wrongAnsTwo);
int readNumberInput();
char readLetterInput();
void checkAnswer(char userLetter, char correctLetter, int correctAns);
void mayaNumberGame();

// Global constants
const char* ZERO_SHELL = "00";
const char* ONE_DOT = "o";
const char* FIVE_LINE = "\u2580";
const char* SEPARATING_LINE = "______";
const int ALIGN_NUMBER = 6;
const int ALIGN_SHELL = 4;
const int BASE_TWENTY = 20;
const double LOWER_BOUND = 0.5;
const double UPPER_BOUND = 1.5;
const int ARR_SIZE = 3;
const int UPPER_TO_LOWER = 32;
const int MIN_VALUE_FOUR = 4;
const int MIN_INPUT_TEN = 10;


// Main function
int main() {
    cout << " The Mayan repersentation of 5212:" << endl;
    printMayanNumber(5212);
    cout << endl << endl;
    mayaNumberGame();
    cout << endl;
    return 0;
}

// Prints the Mayan representation of one
void printOnes (int num){
    cout << ONE_DOT;
}

// Prints the Mayan representation of five
void printFives (int num){
    for (int i = 0; i < 4 ; i++){
        cout << FIVE_LINE;
    }
    cout << endl;
}

// Splits a number into groups of ones and fives, and prints the integer as a Mayan number using earlier functions
void printOnesAndFives (int num){
    int numFives = num / 5;
    int numOnes = num % 5;
 //
    cout << setw(ALIGN_NUMBER - numOnes);
    for (int i = numOnes; i > 0; i--){
        printOnes(num);
    }
    cout << endl;
    for (int i = numFives; i > 0; i--){
        cout << setw(4);
        printFives(num);
    }
}

// Finds place value of a number in Mayan based on how many times the number is divisible by base 20
// If the number is less than 20, it is considered to not be divisible by 20
int placeValueInMayan(int num){
    int placeValue = 0;
    for (int i = 0; num >= BASE_TWENTY; i++){
        num /= BASE_TWENTY;
        placeValue++;
    }
    return placeValue;
}

// Prints the mayan representation of a positive integer
void printMayanNumber(int num){
    // Multiple is the number of 1's, 20's 400's ... that a number has
    int multiple = 0;
    for (int i = placeValueInMayan(num); i >= 0; i--){
        multiple = num / pow(BASE_TWENTY,i);
        // Prints the shell representing 0 when multiple is zero
        if (multiple == 0){
            cout << endl;
            cout << setw(ALIGN_SHELL) << ZERO_SHELL << endl;
        }
        else{
            cout << endl;
            printOnesAndFives(multiple);
        }
        // Prints lines to separate each place value as long is it is not the first place value
        if (i > 0){
            cout << SEPARATING_LINE;
        }
        // Decrements number based on what is printed so far
        num -= multiple * pow(BASE_TWENTY,i);
    }
}

// Prints a random number between the minimum and maximum value
int randNum(int min, int max){
    srand(time(0));
    int randCorrectAns = rand() % (max - min + 1) + min;
    return randCorrectAns;
}

// Prints a random number between 0.5 to 1.5 times the correct answer
int randIncorrectAns(int answer){
    int incorrectNum = randNum(answer * LOWER_BOUND , answer * UPPER_BOUND);
    return incorrectNum;
}

// Compares three values to check if they are the same
bool compareValues(int valueOne, int valueTwo, int valueThree){
    if((valueOne == valueTwo) || (valueOne == valueThree) || (valueTwo == valueThree)){
        return true;
    }
    else{
        return false;
    }
}

// Starts the Mayan game and handles user input
int readNumberInput(){
    int input = 0;
    cout << "Welcome to the Mayan Number Game!" << endl << endl;
    cout << "Enter a number greater than 10. The game will choose a number less than or equal to what you entered. You will then have to match the decimal number to its Mayan equivalent." << endl;
    cout << "Or, enter a number less than 10 to exit: ";
    cin >> input;
    // Clears the infinite loop and returns 0 if the input is the wrong data type
    while (cin.fail()) {
        cin.clear();
        cin.ignore(10000, '\n');
        return 0;
    }
    cin.ignore(10000, '\n');
    return input;
}

// PRE: ans corresponds with zero
// wrongAnsOne corresponds with one
// wrongAnsTwo corresponds with two

// Presents three options to the user
// Answers will be random each time since the elements of the array will be assigned random values from 0 to 2 each time
char presentOptions(int ans, int wrongAnsOne, int wrongAnsTwo){
    //Generates random numbers between 0 and 2
    srand(time(0));
    int elemOne = rand() % 3;
    int elemTwo = rand() % 3;
    int elemThree = rand() % 3;
    // Changes the three numbers until they are different
    bool same = compareValues(elemOne, elemTwo, elemThree);
    while (same){
        srand(time(0));
        elemOne = rand() % 3;
        elemTwo = rand() % 3;
        elemThree = rand() % 3;
        same = compareValues(elemOne, elemTwo, elemThree);
    }
    int optionsArr[ARR_SIZE] = {elemOne, elemTwo, elemThree};
    char option = 'a';
    char correctOption = ' ';
    // Loop starts from option a to c
    // Based on the corresponding values stated above, option 'a' will be whichever if / else statement is true
    for(int i = 0; i < ARR_SIZE; i++){
        cout << option << "." << endl;
        if(optionsArr[i] == 0){
            printMayanNumber(ans);
            correctOption = option;
        }
        else if(optionsArr[i] == 1){
            printMayanNumber(wrongAnsOne);
        }
        else if(optionsArr[i] == 2) {
            printMayanNumber(wrongAnsTwo);
        }
        option++;
        cout << endl;
    }
    return correctOption;
}

// Gets and handles user input for the answer they choose
// Input must be lower or upper case a, b, c
char readLetterInput(){
    char input = ' ';
    while (!(input == 'a' || input == 'A' || input == 'b' || input == 'B' || input == 'c' || input == 'C')){
        cout << "Enter a, b or c: ";
        cin >> input;
        while (cin.fail()){
            cin.clear();
            cin.ignore(10000, '\n');
            cout << "Enter a, b or c: ";
            cin >> input;
        }
        cin.ignore(10000, '\n');
    }
    return input;
}

// Compares the letter the user picked with the corect letter to determine the correct answer
// Accepts upper or lower case a, b, or c
void checkAnswer(char userLetter, char correctLetter, int correctAns){
    if(userLetter == correctLetter || userLetter + UPPER_TO_LOWER == correctLetter ){
        cout << "CORRECT! The Mayan representation of " << correctAns << " is " << endl;
        printMayanNumber(correctAns);
    }
    else{
        cout << "INCORRECT! The Mayan representation of " << correctAns << " is " << endl;
        printMayanNumber(correctAns);
    }
}

// Runs the game
void mayaNumberGame(){
    int input = readNumberInput();
    // Game will run until the input is less than ten
    while(input >= MIN_INPUT_TEN){
        // Generates three answers for the game
        int correctAns = randNum(MIN_VALUE_FOUR,input);
        int incorrectAnsOne = randIncorrectAns(correctAns);
        int incorrectAnsTwo = randIncorrectAns(correctAns);
        // If any of the answers are the same, the incorrect answers are changed until each answer is different
        bool sameAns = compareValues(correctAns, incorrectAnsOne, incorrectAnsTwo);
        while (sameAns == true){
            incorrectAnsOne = randIncorrectAns(correctAns);
            incorrectAnsTwo = randIncorrectAns(correctAns);
            sameAns = compareValues(correctAns, incorrectAnsOne, incorrectAnsTwo);
        }
        cout << "Which of these Mayan numbers is equal to " << correctAns << "?" << endl << endl;
        // Retrieves the return value of presentOptions
        char correctLetter = presentOptions(correctAns, incorrectAnsOne, incorrectAnsTwo);
        char userLetter = readLetterInput();
        cout << endl;
        checkAnswer(userLetter, correctLetter, correctAns);
        cout << endl;
        // Asks user to repeat if they wish
        cout << "Enter another number, or less than 10 to exit: ";
        cin >> input;
        cout << endl;
    }
}


