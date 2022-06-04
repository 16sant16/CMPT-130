#include <iostream>
#include <iomanip>
using namespace std;

// Function prototypes
int factor_check(int numerator, int denominator);
void factor_list(int num);
int factor_count(int num);
string square_or_prime(int num);
void swap( int& x, int& y);
int sum_digits(int value);
int product_digits(int value);
string interesting_num(int value);

// Main function
int main() {
    
    int value_1 = 0;
    int value_2 = 0;
    
    // Asks user for two values between 1 and 999
    cout << "Enter a value between 1 and 999: ";
    cin >> value_1;
    
    while (value_1 < 1 || value_1 > 999){
        cout << "The value must be greater than 0 and less than 1000: ";
        cin >> value_1;
    }
    
    cout << "Enter another value between 1 and 999: ";
    cin >> value_2;
    
    while (value_2 < 1 || value_2 > 999){
        cout << "The value must be greater than 0 and less than 1000: ";
        cin >> value_2;
    }
    cout << endl;
    
    // Prints list of values from the smallest to the largest number given by the user and lists their factors
    if (value_1 > value_2){
        swap(value_1, value_2);
    }
    
    for (int i = value_1; i <= value_2; i++){
        cout << setw(3) << i;
        factor_list(i);
        cout << setw(3) << "(" << factor_count(i) << ")" << square_or_prime(i);
        cout << endl;
    }
    cout << endl;
    
    // Print sum of digits and if the values are interesting numbers or not
    cout << value_1 << ":" << " sum of digits = " << sum_digits(value_1) << interesting_num(value_1) << endl;
    cout << value_2 << ":" << " sum of digits = " << sum_digits(value_2) << interesting_num(value_2) << endl;
    
    return 0;
}

// Checks if a number is a factor of the input or not
int factor_check(int numerator,int denominator){
    int factor = 0;
    if (numerator % denominator == 0 && denominator > 0)
    {
        factor = denominator;
    }
    return factor;
}

// Lists out all possible factors of a number
void factor_list(int num){
    for (int i = 1; i <= num; i++)
    {
        if(factor_check(num,i) != 0)
        {
        cout << setw(4) <<  factor_check(num,i);
        }
    }
}

// Counts number of factors
int factor_count(int num){
    int count = 0;
    for (int i = 1; i <= num; i++)
    {
        if(factor_check(num,i) != 0)
        {
        count++;
        }
    }
    return count;
}

// Determines if a number is prime or a perfect square
string square_or_prime(int num){
    if ( factor_count(num) == 2){
        return " ** prime ** ";
    }
    else if ( factor_count(num) % 2 == 1){
        return " ** perfect square ** ";
    }
    else{
        return " ";
    }
}

// Swaps the value stored between two variables
void swap( int& x, int& y){
    int temp = x;
    x = y;
    y = temp;
}

// Split value into ones, tens, and/or hundreds and adds/multiplies the digits
// If sum + product = value, value = interesting number
int sum_digits(int value){
    
    int ones = 0;
    int tens = 0;
    int hundreds = 0;
    int sum = 0;

    if (value >= 100){
        hundreds = value / 100;
        tens = (value % 100) / 10;
        ones = (value % 100) % 10;
        sum = hundreds + tens + ones;
        return sum;
    }
    else if (value >= 10){
        tens = value / 10;
        ones = value % 10;
        sum = tens + ones;
        return sum;
    }
    else{
        sum = value;
        return sum;
    }
}

int product_digits(int value){
    
    int ones = 0;
    int tens = 0;
    int hundreds = 0;
    int product = 0;

    if (value >= 100){
        hundreds = value / 100;
        tens = (value % 100) / 10;
        ones = (value % 100) % 10;
        product = hundreds * tens * ones;
        return product;
    }
    else if (value >= 10){
        tens = value / 10;
        ones = value % 10;
        product = tens * ones;
        return product;
    }
    else{
        product = value;
        return product;
    }
}

string interesting_num(int value){
    if (sum_digits(value) + product_digits(value) == value){
        return " -- interesting --";
    }
    else{
        return " ";
    }
}

