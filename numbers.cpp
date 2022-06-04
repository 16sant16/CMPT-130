#include <iostream>
#include <string>

using namespace std;

// Function prototypes
string ones(int num);
string teens(int num);
string tens(int num);
string hundreds(int num);
string thousands(int num);
int placeValueThousands(int numThousands);
int placeValueHundreds(int numHundreds);
int placeValueTens(int numTens);
int placeValueOnes(int numOnes);
string intToString(int number);
void printIntStrings(int start, int end, int interval);

//Main function
//int main(){
//    printIntStrings(150,100,11);
//    return 0;
//}

// Value of a number at place value of thousands
int placeValueThousands(int numThousands){
    numThousands /= 1000;
    return numThousands;
}

// Value of a number at place value of hundreds
int placeValueHundreds(int numHundreds){
    if (numHundreds >= 1000){
        numHundreds %= 1000;
        numHundreds /= 100;
        return numHundreds;
    }
    else{
        numHundreds /= 100;
        return numHundreds;
    }
}

// Value of a number at place value of tens
int placeValueTens(int numTens){
    if (numTens >= 100){
        numTens %= 100;
        numTens /= 10;
        return numTens;
    }
    else{
        numTens /= 10;
        return numTens;
    }
}

// Value of a number at place value of ones
int placeValueOnes(int numOnes){
    if (numOnes >= 10){
        numOnes %= 10;
        return numOnes;
    }
    else{
        return numOnes;
    }
}

// Returns string representation of numbers 0 to 9
string ones(int num){
    string stringOnes = "";
    if (placeValueOnes(num) == 9){
        stringOnes += "nine";
    }
    else if ( placeValueOnes(num) == 8){
        stringOnes += "eight";
    }
    else if ( placeValueOnes(num) == 7){
        stringOnes += "seven";
    }
    else if ( placeValueOnes(num) == 6){
        stringOnes += "six";
    }
    else if ( placeValueOnes(num) == 5){
        stringOnes += "five";
    }
    else if ( placeValueOnes(num) == 4){
        stringOnes += "four";
    }
    else if ( placeValueOnes(num) == 3){
        stringOnes += "three";
    }
    else if ( placeValueOnes(num) == 2){
        stringOnes += "two";
    }
    else if ( placeValueOnes(num) == 1){
        stringOnes += "one";
    }
    else if ( placeValueOnes(num) == 0){
        stringOnes += "zero";
    }
return stringOnes;
}

// Returns string representation of numbers 10 to 19
string teens(int num){
    string stringTeens = "";
        if ( placeValueOnes(num) == 9){
            stringTeens += "nineteen";
        }
        else if ( placeValueOnes(num) == 8){
            stringTeens += "eighteen";
        }
        else if ( placeValueOnes(num) == 7){
            stringTeens += "seventeen";
        }
        else if ( placeValueOnes(num) == 6){
            stringTeens += "sixteen";
        }
        else if ( placeValueOnes(num) == 5){
            stringTeens += "fifteen";
        }
        else if ( placeValueOnes(num) == 4){
            stringTeens += "fourteen";
        }
        else if ( placeValueOnes(num) == 3){
            stringTeens += "thirteen";
        }
        else if ( placeValueOnes(num) == 2){
            stringTeens += "twelve";
        }
        else if ( placeValueOnes(num) == 1){
            stringTeens += "eleven";
        }
        else if ( placeValueOnes(num) == 0){
            stringTeens += "ten";
        }
return stringTeens;
}

// Returns string representation of numbers 20 to 99
string tens(int num){
    string stringTens = "";
    if ( placeValueTens(num) == 9){
        stringTens += "ninety";
    }
    else if ( placeValueTens(num) == 8){
        stringTens += "eighty";
    }
    else if ( placeValueTens(num) == 7){
        stringTens += "seventy";
    }
    else if ( placeValueTens(num) == 6){
        stringTens += "sixty";
    }
    else if ( placeValueTens(num) == 5){
        stringTens += "fifty";
    }
    else if ( placeValueTens(num) == 4){
        stringTens += "fourty";
    }
    else if ( placeValueTens(num) == 3){
        stringTens += "thirty";
    }
    else if ( placeValueTens(num) == 2){
        stringTens += "twenty";
    }
    else if ( placeValueTens(num) == 1){
        stringTens += "ten";
    }
    
    // Concatenates dash between tens and ones if the number is not a teen number and doesn't end with 0
    if (placeValueTens(num) >= 2 && placeValueOnes(num) != 0){
        stringTens += "-";
    }
    
    // Concatenates string representation of the digit at ones if it is not 0
    if (placeValueOnes(num)!= 0){
        stringTens += ones(num);
    }
return stringTens;
}

// Returns string representation of numbers 0 to 999
string hundreds(int num){
    string stringHundreds = "";
    if ( placeValueHundreds(num) == 9){
        stringHundreds += "nine ";
    }
    else if ( placeValueHundreds(num) == 8){
        stringHundreds += "eight ";
    }
    else if ( placeValueHundreds(num) == 7){
        stringHundreds += "seven ";
    }
    else if ( placeValueHundreds(num) == 6){
        stringHundreds += "six ";
    }
    else if ( placeValueHundreds(num) == 5){
        stringHundreds += "five ";
    }
    else if ( placeValueHundreds(num) == 4){
        stringHundreds += "four ";
    }
    else if ( placeValueHundreds(num) == 3){
        stringHundreds += "three ";
    }
    else if ( placeValueHundreds(num) == 2){
        stringHundreds += "two ";
    }
    else if ( placeValueHundreds(num) == 1){
        stringHundreds += "one ";
    }
    
    // Concatenates 'hundred' if the value at hundreds is not 0
    if (placeValueHundreds(num)!= 0){
        stringHundreds += "hundred";
    }
    // Concatenate 'and' if the number is not divisible by 100
    if (num % 100 != 0){
        stringHundreds += " and ";
    }
    
    // Concatenate corresponding teen value if the value at tens is one, else concatentates based on tens function
    if (placeValueTens(num) == 1){
        stringHundreds += teens(num);
    }
    else{
        stringHundreds += tens(num);
    }
return stringHundreds;
}

// Returns string representation of numbers 0 to 99999
string thousands(int num){
    string stringThousands = "";
    // Calls on ones, teens or tens function based on if the quotient of the number divided by thousand is greater or less than 10
    if ( num / 1000 < 10){
        stringThousands += ones(num / 1000);
    }
    else if ( num / 1000 >= 10 && num / 1000 <= 19){
        stringThousands += teens(num / 1000);
    }
    else if ( num / 1000 >= 20){
        stringThousands += tens(num / 1000);
    }
    // Concatenate the string thousand and calls on hundreds function
    stringThousands += " thousand";
    // Concatenates comma if the digit at place value of hundreds is not 0
    if( placeValueHundreds(num)!= 0){
        stringThousands += ", ";
        stringThousands += hundreds(num);
    }
    else{
        stringThousands += hundreds(num);
    }
    return stringThousands;
}

// Converts integer parameter into string
// Calls on ones, tens, hundreds, or thousands function depending on the number to convert to string
string intToString(int number){
    string numberAsString = "";
    
    // Returns error if the numberis not in the range of 0 to 99999
    if (number < 0 || number > 99999){
        numberAsString += "error";
    }
    else{
        if (number > 999){
            numberAsString = thousands(number);
        }
        else if (number > 99){
            numberAsString = hundreds(number);
        }
        else if (number > 19){
            numberAsString = tens(number);
        }
        else if (number > 9){
            numberAsString = teens(number);
        }
        else if (number >= 0){
            numberAsString = ones(number);
        }
    }
    return numberAsString;
}

// Prints converted numbers in a given sequence based on starting, ending values, and interval
void printIntStrings(int start, int end, int interval){
    if ( start < end){
        for (int i = start ; i <= end ; i += interval ){
            cout << intToString(i) << endl;
        }
    }
    else{
        for (int i = start ; i >= end ; i -= interval ){
            cout << intToString(i) << endl;
        }
    }
}

int main(){
    printIntStrings(0,100,2);
}