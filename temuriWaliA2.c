/******************************temuriWaliA2.c*******************************************

Student Name: Wali Temuri  Email Id: wtemuri@uoguelph.ca

Due Date: October 28th  Course Name: CIS 1300

I have exclusive control over this submission via my password.
By including this statement in this header comment, I certify that:
1) I have read and understood the University policy on academic integrity.
2) I have completed the Computing with Integrity Tutorial on Moodle; and
3) I have achieved at least 80% in the Computing with Integrity Self Test.
I assert that this work is my own. I have appropriately acknowledged any and all
material that I have used, whether directly quoted or paraphrased. Furthermore,
I certify that this assignment was prepared by me specifically for this course.
    
*****************************************************************************************/
/*********************************************************
Compiling the program
The program should be compiled using the following flags: -std=c99 -Wall

compiling:
gcc -std=c99 -Wall temuriWaliA2.c

Running: ./a.out
*********************************************************/
#include <stdio.h>
#include <ctype.h> // IMPORTANT: These headers/constants are all needed for the program to work
#define MAX 100
#define MAXD 10


void readInput(char str [MAX])
{
    printf("Enter string: ");
    fgets(str, MAX, stdin); //gets string input from user and stores it in str
}

void findStats(char str [MAX], int *countSpecialChars, int *countUpperCase, int *countLowerCase, int *countNumbers)
{
    //For loop iterates through the string inputted by the user, str
    for (int i = 0; str[i] != '\0'; ++i)
    {
        if (isalpha(str[i])) //if str[i] is an alpha letter
        {
            if (islower(str[i])) //and it is lower case
            {
                ++*countLowerCase; //increment num of lower case letters
            }
            else // its an upper case letter
            {
                ++*countUpperCase; //incremenent upper case letter count
            }
        }
        else if (isdigit(str[i])) //if str[i] is a digit
        {
            ++*countNumbers; //increment count of nums
        }
        else if(str[i] == ' ' || str[i] == ',') //if str[i] is a special character
        {
            ++*countSpecialChars; //increment count for special chars
        }
    }
}

int findTotalChancesGiven (char str [MAX])
{
    int freq [10] = {0}; //Initializing Array representing digits 0-9, initially all set to 0 and are going to be incremented based on how frequently each digit appears in the str
    int totalUnique; //total Unique values
    totalUnique = 0; //Initialize to 0 to start with
    int i;

//For loop iterating through the string to find digits
    for (i = 0; str[i] != '\0'; i++)
    {
        if (str[i] >= '0' && str[i] <= '9') //if str[i] is a digit
        {
            freq[str[i] - '0']++; //increment the value representing the digit in the array freq for example, if the digit is 2 freq[2] becomes 1
        }
    }
    for (i = 0; i < 10; i++) //incrementing through the digits 0-9
    {
        if(freq[i] > 0) //if the frequency of the number appearing is greater than 0
        {
            totalUnique++; //increment number of unique nums.
        }
    }
    
    return totalUnique; //returns total unique digits
}

int extractDigits(char str [MAX] , int digitsInInputString [MAX])
{
    int i;
    int digitsAmnt;
    
    digitsAmnt = 0; //Count for #of digits in the string, initializing the count to 0
    
    for (i = 0; str[i] != '\0'; i++) //iterating through the string passed in for digits 0-9
    {
        if (str[i] >= '0' && str[i] <= '9') //if str[i] is a digit
        {
            digitsAmnt++; //increment number of digits
        }
    }
    
    int numsIndex = -1; //Starts at -1 because array starts at 0 need it to go 0 - num of digits
    
     for (i = 0; str[i] != '\0'; i++) //iterating through string again
    {
        if (str[i] >= '0' && str[i] <= '9') //checks if str[i] is a digit 0-9
        {
            numsIndex++; //if str[i] is a digit it increments the index number, used in digits array
            digitsInInputString[numsIndex] = str[i] - '0'; //sets to str[i] for all digits
        }
    }
    
    return  digitsAmnt; //returns total number of digits
  
}

int checkPlayerMove (int playersGuess, int digitsInInputString [MAX], int totalDigits)
{
    int i;
    
    for (i = 0; i < totalDigits; i++) //iterates through digits in Input string
    {
        if (playersGuess == digitsInInputString[i]) //if players guess matches one of the digits in Input string
        {
            return 1; //returns 1 if passes condition
        }
    }
    
    return 0; //if none of the digits in input string match the players guess the function returns 0
}

void updateDigits (int playerGuess, int remainingDigits [MAXD])
{
    remainingDigits[playerGuess] = -1; //puts -1 at the index of the array containing the remainining digits
}

void displayDigits (int remainingDigits [MAXD])
{
    int i;
    
    for (i = 0; i < 10; i++) //iterates through the array containing the remaining digtits
    {
        if (remainingDigits[i] == -1) //if there is a -1 in array index remainingDigits[i] because its been used
        {
            printf(" "); //print a blank space
        }
        else
        {
            printf("%d " , remainingDigits[i]); //if the digit has not been used, print the digit in remainingDigits[i]
        }
    }
}

void displayXs (char exes [MAX], int totalDigits)
{
    int i;
    
    for (i = 0; i < totalDigits; i++) //iterates through total digits because total digits = number of exes
    {
        printf("%c ", exes[i]); //prints out the element contained in exes[i] whether its an X or a digit
    }
}

int countXs (char exes [MAX], int totalDigits)
{
    int i;
    int exCount; //keeps track of number of exes or X's in the array
    exCount = 0; //count is initialized to 0 to begin with
    
    for (i = 0; i < totalDigits; i++) //iterates throught the array of exes
    {
        if (exes[i] == 'X') //if 'X' is an element of exes[i]
        {
            exCount++; //increment the count of exes
        }
    }
    
    return exCount; //return total ex count
}

