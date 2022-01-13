#include <stdio.h>
#include <ctype.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>
#define MAX 100
#define MAXD 10

void readInput(char str[MAX]);

void findStats(char str[MAX], int *countSpecialChars, int *countUpperCase, int *countLowerCase, int *countNumbers);

int findTotalChancesGiven(char str[MAX]);

int extractDigits (char str[MAX], int digitsInInputString[MAX]);

int checkPlayerMove(int playersGuess, int digitsInInputString[MAX], int totalDigits);

void updateDigits(int playerGuess, int remainingDigits[MAXD]);

void displayDigits (int remainingDigits [MAXD]);

void displayXs(char exes[MAX], int totalDigits);

void updateXs (char exes[MAX], int digitsInInputString[MAX], int playerGuess, int totalDigits);

bool validInput(char str[MAX]);


int main (void)
{
    bool fudu;
    fudu = true;
    char userInput[MAX];
  //  int userNums[MAX];
    int specialChars, upperLetters, lowerLetters, userNumbers;
    int i;
    
    specialChars = 0;
    upperLetters = 0;
    lowerLetters = 0;
    userNumbers = 0;
   
   //Step 1: Get string input from user
        bool validEntry = false;

    while(!validEntry) {
        printf("\nEnter a string: ");
        readInput(userInput);
        validEntry = validInput(userInput);
    }
    
    findStats(userInput, &specialChars, &upperLetters, &lowerLetters, &userNumbers);
    //Step 2: Display Stats
    printf("\n\nCount of special characters = %d\n" , specialChars);
    printf("Count of uppercase characters= %d\n" , upperLetters);
    printf("Count of lowercase characters = %d\n" , lowerLetters);
    printf("Count of single-digit integers = %d\n" , userNumbers);
    //Step 3: press a key to continue
    printf("\n\nPress a key to continue");
    //Step 4: Explain rules and print chances
    printf("\n\nNow the computer plays hangman with numbers - you get %d chances", findTotalChancesGiven(userInput));
    printf("\n\nEach X depicts a digit in the same order as it occurs in the given string\n\n");
    //Print X's
    char arrayXs[MAX];
    for (i = 0; i < userNumbers; i++)
    {
        arrayXs[i] = 'X';
    }
    for (i = 0; i < userNumbers; i++)
    {
        printf("%c ", arrayXs[i]);
    }
    printf("\n\n");
    
    int playerChoice;
    int digitsRemaining[MAXD] = { 0, 1 , 2, 3, 4, 5, 6, 7, 8, 9 };
    
    printf("Choose a digit among these: 0 1 2 3 4 5 6 7 8 9\n\n");
    printf("Player's choice #1 is ");
    scanf("%d", &playerChoice);
    int digitsInInput[MAX];
    extractDigits(userInput, digitsInInput);
    int totalChances = findTotalChancesGiven(userInput);
    //Step 6: Check if choice is correct
    
    int y = checkPlayerMove(playerChoice, digitsInInput, userNumbers);

    //Step 7: Keep looping for the amount of guesses
    if (y == 1)
    {
        printf("\nYour choice is correct this time. Well done!");
      //  updateDigits(playerChoice, digitsRemaining);
      //  updateXs(arrayXs,digitsInInput, playerChoice, userNumbers);
      //  displayDigits(digitsRemaining);
        printf("\n\n");
       // displayXs(arrayXs, userNumbers);
        totalChances--;
    }
    else
    {
        printf("Incorrect.");
        exit(0);
    }
    
    for (i = 2; totalChances != 0; i++)
    {
        printf("\n\nCurrent hangman scenario is as follows:\n\n");
        updateXs(arrayXs,digitsInInput, playerChoice, userNumbers);
        displayXs(arrayXs, userNumbers);
        printf("\n\nYou have %d guesses left\n\n", totalChances);
        updateDigits(playerChoice, digitsRemaining);
        printf("Digits remaining are as follows - player chooses among these: ");
        displayDigits(digitsRemaining);
        printf("\n\nPress a key to continue\n\n");
        printf("Players choice # %d is ", i);
        scanf("%d", &playerChoice);
        
        if (checkPlayerMove(playerChoice, digitsInInput, userNumbers) == 1)
        {
            totalChances = totalChances - 1;
             printf("\nYour choice is correct this time. Well Done!");
        }
        else
        {
            --totalChances;
            
            if(totalChances > 0)
            {
                printf("\nSorry, your choice is incorrect this time.");
            }
            else
            {
                printf("\nSorry, your choice is incorrect this time. Better luck next time.");
                exit(0);
            }
        }
    }
    printf("\n\n");
    printf("Final number: ");
    updateXs(arrayXs,digitsInInput, playerChoice, userNumbers);
    displayXs(arrayXs, userNumbers);
    printf("\n");
    
}

void readInput(char str[MAX])
{
    fgets(str, MAX, stdin);
}

void findStats(char str[MAX], int *countSpecialChars, int *countUpperCase, int *countLowerCase, int *countNumbers)
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

int findTotalChancesGiven (char str[MAX])
{
    int freq [MAXD] = {0}; //Initializing Array representing digits 0-9, initially all set to 0 and are going to be incremented based on how frequently each digit appears in the str
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
    for (i = 0; i < MAXD; i++) //incrementing through the digits 0-9
    {
        if(freq[i] > 0) //if the frequency of the number appearing is greater than 0
        {
            totalUnique++; //increment number of unique nums.
        }
    }
    
    return totalUnique;
}

int extractDigits(char str[MAX] , int digitsInInputString[MAX])
{
    int i;
    int digitsAmnt = 0; //Count for #of digits in the string
    
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
    
    return  digitsAmnt;
  
}

int checkPlayerMove (int playersGuess, int digitsInInputString[MAX], int totalDigits)
{
    int i;
    
    for (i = 0; i < totalDigits; i++)
    {
        if (playersGuess == digitsInInputString[i])
        {
            return 1;
        }
    }
    
    return 0;
}

void updateDigits (int playerGuess, int remainingDigits[MAXD])
{
        remainingDigits[playerGuess] = -1;
}

void displayDigits (int remainingDigits[MAXD])
{
    int i;
    
    for (i = 0; i < MAXD; i++)
    {
        if (remainingDigits[i] == -1)
        {
            printf(" ");
        }
        else
        {
            printf("%d " , remainingDigits[i]);
        }
    }
}

void displayXs (char exes[MAX], int totalDigits)
{
    int i;
    
    for (i = 0; i < totalDigits; i++)
    {
        printf("%c ", exes[i]);
    }
}


void updateXs (char exes[MAX], int digitsInInputString[MAX], int playerGuess, int totalDigits)
{
   int i;
   
   for (i = 0; i < totalDigits; i++)
   {
       if(digitsInInputString[i] == playerGuess)
       {
           exes[i] = playerGuess + '0';
       }
   }
    
}

bool validInput(char str[MAX])
{
    for(int i = 0; str[i] != '\0'; i++)
    {
        if(isdigit(str[i]))
        {
            return true;
        }
    }
    return false;
}
