/***************************************************************************
This is to certify that this project is my own work, based on my personal 
efforts in studying and applying the concepts learned. I have constructed 
the functions and their respective algorithms and corresponding code by 
myself. The program was run, tested, and debugged by my own efforts. I 
further certify that I have not copied in part or whole or otherwise 
plagiarized the work of other students and/or persons.
***************************************************************************/

/*
Description: This program generates Energon Cubes weekly by setting the production standards on the first day (Sunday) 
by producing Energon Cubes and then gaining Energon on the next days by using the produced Energon Cubes. The program
shall continue for 10 weeks and its goal is to have 1000000 Energon by the end. 
Programmed by: To iu Mono Ryōshi
Last modified: Nov. 30, 2024; 8:50PM
Version: 4.3
Acknowledgements: 
    1. The <conio.h> library: for the getch() function.
    2. Use of the getch() function: https://www.geeksforgeeks.org/difference-getchar-getch-getc-getche/
    3. Clearing the console using system("cls") (present in <stdlib.h> library): https://www.geeksforgeeks.org/clear-console-c-language/
    4. Generating Random Numbers in a Range using Custom Seed: https://www.geeksforgeeks.org/generating-random-number-range-c/
    5. Values of Integers for True and False: https://www.classes.cs.uchicago.edu/archive/2019/winter/15200-1/lecs/notes/Lec3CondNotes.html#:~:text=C%20does%20not%20have%20boolean,uses%20integers%20for%20boolean%20testing.&text=To%20make%20life%20easier%2C%20C,values%201%20and%200%20respectively.
*/

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <conio.h> //only used for the getch() function

/*  This function displays the first thing you see at the program which are the 
    week number, day number, energon storage, and stacks 
    Precondition: *weekNo = 1; *dayNo = 1; *energonStorage = 10000; *energonStacks = 0;
    @param *weekNo - number of week
    @param *dayNo - number of day
    @param *energonStorage - number of energon available
    @param *energonStacks - initial number of stacks (energon cubes) available
    @return nothing
*/
void firstDisplay(int *weekNo, int *dayNo, int *energonStorage, int *energonStacks) {
    printf("Week %d Day %d\n", *weekNo, *dayNo);
    printf("Energon Storage: %d   Stacks: %d\n\n", *energonStorage, *energonStacks);
}

/*  This function displays like the firstDisplay function but with the recycled stacks
    Precondition: *weekNo = 1; *dayNo = 1; *energonStorage = 10000; *energonStacks = 0; *recycledStacks = 0
    @param *weekNo - number of week
    @param *dayNo - number of day
    @param *energonStorage - number of energon available
    @param *energonStacks - initial number of stacks (energon cubes) available
    @param *recycledStacks - number of recycled stacks
    @return nothing
*/
void displaywithRecycledStacks(int *weekNo, int *dayNo, int *energonStorage, int *energonStacks, int *recycledStacks) {
    printf("Week %d Day %d\n", *weekNo, *dayNo);
    printf("Energon Storage: %d   Stacks: %d   Recycled Stacks: %d\n\n", *energonStorage, *energonStacks, *recycledStacks);
}   

/*  This function computes for the total cost of energon to produce cubes
    Precondition: Range of *energonCost is from 800 - 1200 and *weeklyEnergonStacks must not be less than or equal to 0 
    @param *energonCost - cost of energon to produce 1 stack
    @param *weeklyEnergonStacks - number of stacks (energon cubes) available
    @return computed cost needed to produce energon cubes
*/
int computeCost(int *energonCost, int *weeklyEnergonStacks) {
    int totalCost;
    totalCost = *energonCost * *weeklyEnergonStacks;
    return totalCost;
}

/*  This function displays the entry for the number of stack production for the week
    and the error messages if the entry is less than 0 or a non-integer
    Precondition: *energonCost must be equal to the product of the randomly generated energon (Range: 80-120) times 10
    @param *weeklyEnergonStacks - number of stacks (energon cubes) available
    @param *energonCost - cost of energon to produce 1 stack
    @param *totalCost - cost needed to produce energon cubes
    @return nothing
*/
void stackEntry(int *weeklyEnergonStacks, int *energonCost, int *totalCost) {
    int readEntry; //variable used to return an integer if true or false

    do {    
        printf("How many stacks do you wish to produce for this week? ");
        readEntry = scanf("%d", weeklyEnergonStacks); //stores the return value of the scan statement (1 = true, !1 = false)
        getchar(); 
            
        if (readEntry != 1) 
            printf("Please Enter a Valid Number!\n");
        
        else if (*weeklyEnergonStacks < 0) 
            printf("Please Enter a Positive Number!\n");
            
    } while (readEntry != 1 || *weeklyEnergonStacks < 0); //loops if the user inputs an invalid or a negative number

    *totalCost = computeCost(energonCost, weeklyEnergonStacks); //stores the value of the total cost
}

/*  This function calls the stackEntry function and displays the error message if 
    the total cost is larger than the available energon stored
    Precondition: *energonStorage must always be a number greater than 800
    @param *energonStorage - number of energon available
    @param *energonCost - cost of energon to produce 1 stack
    @param *weeklyEnergonStacks - number of stacks (energon cubes) available
    @param *totalCost - cost needed to produce energon cubes
    @return nothing
*/
void weeklyStackProduction(int *energonStorage, int *energonCost, int *weeklyEnergonStacks, int *totalCost) { 

    do {
        stackEntry(weeklyEnergonStacks, energonCost, totalCost);

        if (*totalCost > *energonStorage)
            printf("The Energon cost exceeds the available Energon stored. Please Try Again.\n");

    } while (*totalCost > *energonStorage); //loops if the user inputs a value higher than the total cost

}

/*  This function displays the decision to proceed with the transaction every Sunday
    Precondition: *totalCost must not be larger than *energonStorage and 
    *weeklyEnergonStacks must not be less than 0.
    @param *energonStorage - number of energon available
    @param *energonCost - cost of energon to produce 1 stack
    @param *weeklyEnergonStacks - number of stacks (energon cubes) available
    @param *totalCost - cost needed to produce energon cubes
    @return nothing
*/
void weeklyConfirmation(int *energonStorage, int *energonCost, int *weeklyEnergonStacks, int *totalCost) {
    char confirmDecision;

    printf("%d stacks will cost %d Energon, proceed?(y/n) ", *weeklyEnergonStacks, *totalCost);
    scanf(" %c", &confirmDecision);
    getchar();

        while (confirmDecision != 'y' && confirmDecision != 'Y') { //loops until the user inputs y or Y
            
            if (confirmDecision == 'n' || confirmDecision == 'N') { //will repeat back to stack production function if the user inputs n or N
                weeklyStackProduction(energonStorage, energonCost, weeklyEnergonStacks, totalCost);
                printf("%d stacks will cost %d Energon, proceed?(y/n) ", *weeklyEnergonStacks, *totalCost);
            }

            else 
                printf("Not a valid option, please enter only y or n. ");           

            scanf(" %c", &confirmDecision);
            getchar();
        } 

    if(*weeklyEnergonStacks > 0) //ensures that the statement below will only be printed if the user did not input a 0
        printf("%d stacks produced. \n\n", *weeklyEnergonStacks);
}

/*  This function randomly generates energon cost to produce cubes
    Precondition: *randomEnergon must have no value 
    @param *randomEnergon - stores the generated random value for energon production
    @return random number which is the cost to make 1 cube
*/
int generateRandomEnergon(int *randomEnergon){
    srand(time(0));
    *randomEnergon = 80 + (rand() % 41);
    return *randomEnergon;
}

/*  This function diplays the production cost and the cost to produce 1 stack for day 1
    Precondition: *randomEnergon should have a random generated number from 80 to 120
    @param *weekNo - number of week
    @param *dayNo - number of day
    @param *energonStacks - initial number of stacks (energon cubes) available
    @param *energonStorage - number of energon available
    @param *randomEnergon - stores the generated random value for energon production
    @param *energonCost - cost of energon to produce 1 stack
    @param *recycledStacks - number of recycled stacks
    @return energon cost to produce 1 stack
*/
void displayDayOne(int *weekNo, int *dayNo, int *energonStacks, int *energonStorage, int *randomEnergon, int *energonCost, int *recycledStacks) {

    if (*recycledStacks == 0) //executes if recycled stacks is equal to 0
        firstDisplay(weekNo, dayNo, energonStorage, energonStacks);

    else //executes if there are available recycled stacks
        displaywithRecycledStacks(weekNo, dayNo, energonStorage, energonStacks, recycledStacks);

    *randomEnergon = generateRandomEnergon(randomEnergon); //stores the randomly generated energon cost
    *energonCost = *randomEnergon * 10; //energoncost is the random energon cost times 10

    printf("Production cost for this week is %d Energon for 1 cube.\n", *randomEnergon);
    printf("It will cost %d Energon to produce 1 stack.\n\n", *energonCost);
}

/*  This function displays the entry for the number of stacks the user wants to sell
    and the error messages if the entry is less than 0, a non-integer or higher than the available stacks
    Precondition: *weeklyEnergonStacks must not be less than or equal to 0.
    @param *sellStacks - number of stacks to sell daily
    @param *weeklyEnergonStacks - number of stacks (energon cubes) available
    @return nothing
*/
void sellEntry(int *sellStacks, int *weeklyEnergonStacks) {
    int readEntry; //variable used to return an integer if true or false

    do {    
        printf("How many stacks do you wish to sell to Swindle? ");
        readEntry = scanf("%d", sellStacks); //stores the return value of the scan statement (1 = true, !1 = false)
        getchar();
            
        if (readEntry != 1) 
            printf("Please Enter a Valid Number!\n");
        
        else if (*sellStacks < 0) 
            printf("Please Enter a Positive Number!\n");

        else if (*sellStacks > *weeklyEnergonStacks) 
            printf("The stacks you wish to sell exceeds the available stacks. Please Try Again.\n");
            
    } while (readEntry != 1 || *sellStacks < 0 || *sellStacks > *weeklyEnergonStacks); //loops if the user inputs an invalid, a negative, or a number higher than the available stacks
}

/*  This function diplays the decision to proceed with the transaction daily
    Precondition: *sellStacks must not be less than 0, a non-integer or higher than the available stacks
    @param *sellStacks - number of stacks to sell daily
    @param *weeklyEnergonStacks - number of stacks (energon cubes) available
    @return nothing
*/
void dailyConfirmation(int *sellStacks, int *weeklyEnergonStacks) {
    char confirmDecision;

    printf("%d stacks are about to be sold, proceed? (y/n) ", *sellStacks);
    scanf(" %c", &confirmDecision);
    getchar();

        while (confirmDecision != 'y' && confirmDecision != 'Y') { //loops until the user inputs y or Y
            
            if (confirmDecision == 'n' || confirmDecision == 'N') { //will repeat back to stack production function if the user inputs n or N
                sellEntry(sellStacks, weeklyEnergonStacks);
                printf("%d stacks are about to be sold, proceed? (y/n) ", *sellStacks);
            }

            else 
                printf("Not a valid option, please enter only y or n. ");       
            
            scanf(" %c", &confirmDecision);
            getchar();
        } 

    printf("%d stacks sold. \n", *sellStacks);
}

/*  This function displays the randomly generated cost that Swindle is willing to buy from your stacks and the amount of energon you can earn per stacks old. 
    Precondition: *randomSwindle should have a random generated number based on the trend for the week
    @param *randomSwindle - stores the generated random value for selling to Swindle
    @param *sellStacks - number of stacks to sell daily
    @param *weeklyEnergonStacks - number of stacks (energon cubes) available
    @return nothing
*/
void displayDayTwotoSeven(int *randomSwindle, int *sellStacks, int *weeklyEnergonStacks) {
    printf("Swindle is buying Energon cubes for %d Energon per cube.\n", *randomSwindle);
    printf("You can earn %d Energon per stack. \n\n", *randomSwindle * 10);

    sellEntry(sellStacks, weeklyEnergonStacks); //executes the entry for selling stacks first
    dailyConfirmation(sellStacks, weeklyEnergonStacks); //executes the confirmation in selling stacks after inputting the number of stacks to sell
}

/*  This function randomly generates 1, 2 or 3 to determine the trend per week
    Precondition: randomTrend must have no value
    @param randomTrend - stores the generated random value for the trend
    @return random trend value
*/
int generateRandomTrend(int randomTrend) {
    srand(time(0));
    randomTrend = 1 + (rand() % 3);
    return randomTrend;
}

/*  This function generates a random value for the scrap trend if randomTrend = 1
    Precondition: *randomEnergon should have a random generated number from 80 to 120
    @param *randomEnergon - stores the generated random value for energon production
    @param *randomSwindle - stores the generated random value for selling to Swindle
    @param *sellStacks - number of stacks to sell daily
    @param *weeklyEnergonStacks - number of stacks (energon cubes) available
    @return generated random value of Swindle is willing to buy from your stacks based on the scrap trend
*/
void scrapTrend(int *randomEnergon, int *randomSwindle, int *sellStacks, int *weeklyEnergonStacks) {
    int maxPrice;
    int setValue;

    maxPrice = *randomEnergon - 10; //sets the maximum value for the scrap trend
    setValue = maxPrice - 20 + 1; //sets the value to scale the number to fit in the range for the scrap trend
    
    srand(time(0));
    *randomSwindle = 20 + (rand() % setValue);

    displayDayTwotoSeven(randomSwindle, sellStacks, weeklyEnergonStacks); //executes the display for days 2-7 for the scrap trend
}

/*  This function generates a random value for the nominal trend if randomTrend = 2
    Precondition: *randomEnergon should have a random generated number from 80 to 120
    @param *randomEnergon - stores the generated random value for energon production
    @param *randomSwindle - stores the generated random value for selling to Swindle
    @param *sellStacks - number of stacks to sell daily
    @param *weeklyEnergonStacks - number of stacks (energon cubes) available
    @return generated random value of Swindle is willing to buy from your stacks based on the nominal trend
*/
void nominalTrend(int *randomEnergon, int *randomSwindle, int *sellStacks, int *weeklyEnergonStacks) {
    int maxPrice;
    int setValue;

    maxPrice = *randomEnergon * 1.05; //sets the maximum value for the nominal trend
    setValue = maxPrice - 80 + 1; //sets the value to scale the number to fit in the range for the nominal trend

    srand(time(0));
    *randomSwindle = 80 + (rand() % setValue);

    displayDayTwotoSeven(randomSwindle, sellStacks, weeklyEnergonStacks); //executes the display for days 2-7 for the nominal trend
}

/*  This function generates a random value for the primus trend if randomTrend = 3
    Precondition: *randomEnergon should have a random generated number from 80 to 120
    @param *randomEnergon - stores the generated random value for energon production
    @param *randomSwindle - stores the generated random value for selling to Swindle
    @param *sellStacks - number of stacks to sell daily
    @param *weeklyEnergonStacks - number of stacks (energon cubes) available
    @return generated random value of Swindle is willing to buy from your stacks based on the primus trend
*/
void primusTrend(int *randomEnergon, int *randomSwindle, int *sellStacks, int *weeklyEnergonStacks) {
    int maxPrice;
    int setValue;

    maxPrice = *randomEnergon * 4; //sets the maximum value for the primus trend
    setValue = maxPrice - *randomEnergon + 1; //sets the value to scale the number to fit in the range for the primus trend

    srand(time(0));
    *randomSwindle = *randomEnergon + (rand() % setValue);

    displayDayTwotoSeven(randomSwindle, sellStacks, weeklyEnergonStacks); //executes the display for days 2-7 for the primus trend
}

/*  This function displays on how much the user is willing to sell from the recycled stacks
    Precondition: *recycledStacks must not be less than or equal to 0 and must not also be less than *sellStacks
                  *energonStorage must not be less than 800
    @param *recycledStacks - number of recycled stacks
    @param *sellStacks - number of stacks to sell daily
    @param *energonStorage - number of energon available
    @return updated value of *energonStorage and *recycledStacks
*/
void bonusFeatureEntry(int *recycledStacks, int *sellStacks, int *energonStorage) {
    int readEntry; //variable used to return an integer if true or false

    do {    
        printf("How many stacks do you wish to sell? ");
        readEntry = scanf("%d", sellStacks); //stores the return value of the scan statement (1 = true, !1 = false)
        getchar();
            
        if (readEntry != 1) 
            printf("Please Enter a Valid Number!\n");
        
        else if (*sellStacks < 0) 
            printf("Please Enter a Positive Number!\n");

        else if (*sellStacks == 0)
            printf("You confirmed to sell the remaining stacks, number cannot be 0.\n");

        else if (*sellStacks > *recycledStacks)
            printf("Number Entered is higher than the available stacks. Please Try Again.\n");
            
    } while (readEntry != 1 || *sellStacks <= 0 || *sellStacks > *recycledStacks); //loops if the user inputs an invalid, a negative, or a number higher than the recycled stacks

    *energonStorage += *sellStacks * 200; //updates the energon storage from the stacks sold by multiplying to 200
    *recycledStacks -= *sellStacks; //updates the value of recycled stacks based on the input to sell stacks
}

/*  This function will display the decision to proceed if there are stacks remaining at the end of the week
    Precondition: *recycledStacks must be a positive number and *dayNo must be greater than 1
    @param *recycledStacks - number of recycled stacks
    @param *dayNo - number of day
    @param *sellStacks - number of stacks to sell daily
    @param *energonStorage - number of energon available
    @param *weekNo - number of week
    @return nothing
*/
void bonusFeatureConfirmation(int *recycledStacks, int *dayNo, int *sellStacks, int *energonStorage, int *weekNo) {
    char sellConfirmation;

    if (*recycledStacks > 0 && *dayNo > 1) { //executes if there are available stacks left (must not execute if it is day 1)
        printf("Do you wish to sell the remaining %d stacks for 200 energon each? (y/n) ", *recycledStacks);
        scanf(" %c", &sellConfirmation);
        getchar();

        while (sellConfirmation != 'y' && sellConfirmation != 'Y' && sellConfirmation != 'n' && sellConfirmation != 'N') { //loops until the user inputs y or n
            printf("Not a valid option, please enter only y or n. "); 
            scanf(" %c", &sellConfirmation);
            getchar();
        }
            
        switch (sellConfirmation) {
            case 'y':
            case 'Y':
                bonusFeatureEntry(recycledStacks, sellStacks, energonStorage); //executes the function display for entry of stacks to sell
                printf("%d stacks are sold, total Energon is now %d, press any key to continue . . . ", *sellStacks, *energonStorage);
                break;

            default: 
                printf("No leftover stacks are sold, press any key to continue . . . ");
        }
        getch(); //pressing any key continues the program   (I did not use getchar because typing other characters causes an infinite loop in the program) 
    }

    else if (*recycledStacks == 0 && *dayNo > 1){ //executes if there are no available stacks left (must not execute if it is day 1)
        printf("This week's production is now finished, press any key to continue . . . ");
        getch(); //pressing any key continues the program    
    }

    if(*energonStorage >= 800 && *weekNo <= 9) { //must only execute if available energon is greater than or equal to 800 and if week number is 9 or below
        system("cls"); //clears the console
        *dayNo -= *dayNo - 1; //resets the current number of day to 1
    }
}

/*  This function will display if 0 is inputted three times on days 2-7
    Precondition: *dayNo value must be only from 2-6
    @param *dayNo - number of day
    @return nothing
*/
void zeroThreeTimes(int *dayNo) {
    char skipDecision;
    
    printf("You have entered 0 three times, do you wish to skip the current week? (y/n) ");
    scanf(" %c", &skipDecision);
    getchar();

    while (skipDecision != 'y' && skipDecision != 'Y' && skipDecision != 'n' && skipDecision != 'N') { //loops until the user inputs y or n
        printf("Not a valid option, please enter only y or n. "); 
        scanf(" %c", &skipDecision);
        getchar();
    }

    switch(skipDecision) {
        case 'y':
        case 'Y':
            *dayNo = 7; //if the user wants to skip the day, number of day is updated to 7 to stop the loop

        default:
            printf("\n");
            printf("---------------------------------------------------------------------------\n\n");
    }
}

/*  This function will display the setting to make the user choose to toggle display trend per week
    Precondition: *trendDisplayDecision must have no value
    @param *trendDisplayDecision - value of choice to toggle display trend per week
    @return nothing
*/
void toggleTrendDisplay (char *trendDisplayDecision) {
    printf("Do you want to toggle trend display per week? (y/n) ");
    scanf(" %c", trendDisplayDecision);
    getchar();

    while (*trendDisplayDecision != 'y' && *trendDisplayDecision != 'Y' && *trendDisplayDecision != 'n' && *trendDisplayDecision != 'N') { //loops until the user inputs y or n
        printf("Not a valid option, please enter only y or n. ");
        scanf(" %c", trendDisplayDecision);
        getchar();
    }
             
    switch (*trendDisplayDecision) {
        case 'y':
        case 'Y':
            printf("Display Trend is On. \n");
            break;

        default:
            printf("Display Trend is Off. \n");
    }
}

/*  This function will display the setting to make the user edit the amount of energon available
    Precondition: *energonStorage must have an initial vallue of 10000
    @param *energonStorage - number of energon available
    @return new value of *energonStorage
*/
void editEnergon (int *energonStorage) {
    int energonStorageEdit;
    int readEntry; //variable used to return an integer if true or false

    do {
        printf("Enter Desired Amount of Energon: ");
        readEntry = scanf("%d", &energonStorageEdit); //stores the return value of the scan statement (1 = true, !1 = false)
        getchar();

        if (readEntry != 1) 
            printf("Please Enter a Valid Number!\n");

        else if (energonStorageEdit < 0) 
            printf("Please Enter a Positive Number!\n");
        
    } while (energonStorageEdit < 0 || readEntry != 1); //loops if the user inputs an invalid or a negative number

    *energonStorage = energonStorageEdit; // updates the value of the stored energon
}

/*  This function will display the setting to make the user edit the number of week
    Precondition: *weekNoEdit must have an initial value of 1
    @param *weekNoEdit - edited number of week 
    @return new value of *weekNoEdit
*/
void editWeekNo (int *weekNoEdit) {
    int readEntry; //variable used to return an integer if true or false

    do {
        printf("Enter Desired Number of Week: ");
        readEntry = scanf("%d", weekNoEdit); //stores the return value of the scan statement (1 = true, !1 = false)
        getchar();

        if (readEntry != 1) 
            printf("Please Enter a Valid Number!\n");

        else if (*weekNoEdit > 10 || *weekNoEdit < 1)
            printf("Invalid Number, Please Try Again. \n");

    } while (*weekNoEdit > 10 || *weekNoEdit < 1 || readEntry != 1); //loops if the user inputs an invalid number
}

/*  This function will display first as the program is compiled to have the user choose to start the game or enter dev mode to configure settings
    Precondition: *energonStorage must have an initial vallue of 10000 and *weekNoEdit must have an initial value of 1
    @param *energonStorage - number of energon available
    @param *weekNoEdit - edited number of week 
    @param *trendDisplayDecision - value of choice to toggle display trend per week
    @return nothing
*/
void devFeature (int *energonStorage, int *weekNoEdit, char *trendDisplayDecision) {
    int devModeChoice;

    printf("==========================================================\n");
    printf("|\t\t\t\t\t\t\t |\n");
    printf("|");
    printf("\tWelcome to Energon Cubes Production Game! \t |\n");
    printf("|\t\t\t\t\t\t\t |\n");
    printf("----------------------------------------------------------\n");     // added a bit of design when the program starts
    printf("|\t\t\t\t\t\t\t |\n");
    printf("|");
    printf("\t1 - Play Game \t 2 - Settings (Dev Mode) \t |\n");
    printf("|\t\t\t\t\t\t\t |\n");
    printf("==========================================================\n\n");
    printf("Please Select an Option: ");
    scanf("%d", &devModeChoice);
    getchar();

    while (devModeChoice < 1 || devModeChoice > 2) { // loops until the user inputs 1 or 2
        printf("Not a valid option, please select only 1 or 2. ");
        scanf("%d", &devModeChoice);
        getchar();
    }
    
    switch (devModeChoice) {
        case 2:     
            editWeekNo (weekNoEdit);
            editEnergon (energonStorage);
            toggleTrendDisplay (trendDisplayDecision);
            
            printf("All settings saved, press any key to continue . . . ");
            getch(); //pressing any key continues the program

        default: 
            system("cls"); //clears the console to start the game   
    }
}

int main() {
    //variables for day 1
    int weekNo;
    int dayNo = 1;
    int energonStacks = 0;
    int energonStorage = 10000;
    int randomEnergon = 0;
    int energonCost;
    int weeklyEnergonStacks;
    int totalCost;

    //variables for days 2-7
    int randomTrend = 0;
    int randomSwindle;
    int sellStacks;
    int newEnergon;

    //variables for bonus and additional features
    int recycledStacks = 0;
    int zeroCounter = 0;

    //variables for dev mode
    int weekNoEdit = 1;
    char trendDisplayDecision;
    
    devFeature (&energonStorage, &weekNoEdit, &trendDisplayDecision); //displays dev mode first

    for (weekNo = weekNoEdit; weekNo <= 10; weekNo++) { // loops until number of week reaches 10 to keep the program running until week 10

        if(energonStorage < 800) { //will only execute if the available energon is less than 800
            firstDisplay(&weekNo, &dayNo, &energonStorage, &energonStacks); //prints the first display
            weekNo = 10; //updates the number of week to stop the loop
            printf("\n");
            printf("---------------------------------------------------------------------------\n\n");
            printf("Available Energon is now insufficient with a total of %d Energon, no more Energon Cubes can be produced. \n", energonStorage);
        }  

        else {
            displayDayOne(&weekNo, &dayNo, &energonStacks, &energonStorage, &randomEnergon, &energonCost, &recycledStacks); //displays the information for day one first
            weeklyStackProduction(&energonStorage, &energonCost, &weeklyEnergonStacks, &totalCost); //displays the entry to produce stack
            weeklyConfirmation(&energonStorage, &energonCost, &weeklyEnergonStacks, &totalCost); //will only execute for confirming the stack entered
        
            if (energonStorage > 0) { // must execute only if energon storage is more than 0

                if(weeklyEnergonStacks == 0 && weekNo <= 9) { 
                    system("cls"); //clears the console if the user inputs 0 on day 1 (must only clear until week 9)
                } else //continues if the user did not input 0
                    printf("---------------------------------------------------------------------------\n\n");
            }
            
            energonStorage -= totalCost; //updates the available energon by subtracting the total cost of production per week
            randomTrend = generateRandomTrend(randomTrend); //stores the value of the randomly generated number from 1 to 3

            if ((trendDisplayDecision == 'y' || trendDisplayDecision == 'Y') && weeklyEnergonStacks > 0) { //executes if the user inputs y from dev mode (only if the user did not input 0 on day 1)
                printf("The Trend for this week is: ");

                if (randomTrend == 1)
                    printf("Scrap Trend\n\n");

                else if (randomTrend == 2)
                    printf("Nominal Trend\n\n");

                else
                    printf("Primus Trend\n\n");

                printf("---------------------------------------------------------------------------\n\n");
            }
            
            while (dayNo < 7 && weeklyEnergonStacks > 0) { //loops to execute codes for days 2-7 (only if the user did not input 0 on day 1)
                dayNo++; //updates the number of day
                firstDisplay(&weekNo, &dayNo, &energonStorage, &weeklyEnergonStacks); //displays the information for days 2-7

                switch (randomTrend) {
                    case 1:
                        scrapTrend(&randomEnergon, &randomSwindle, &sellStacks, &weeklyEnergonStacks); //executes if randomly generated number for trend is 1
                        break;
                    
                    case 2:
                        nominalTrend(&randomEnergon, &randomSwindle, &sellStacks, &weeklyEnergonStacks); //executes if randomly generated number for trend is 2
                        break;

                    case 3:
                        primusTrend(&randomEnergon, &randomSwindle, &sellStacks, &weeklyEnergonStacks); //executes if randomly generated number for trend is 3
                }
                newEnergon = (randomSwindle * 10) * sellStacks; //stores the value of energon gained after selling stacks
                printf("You earned %d Energon. \n\n", newEnergon);

                printf("---------------------------------------------------------------------------\n\n");

                weeklyEnergonStacks -= sellStacks; //updates the value of available stacks from the stacks sold
                energonStorage += newEnergon; //updates the value of stored energon by adding the value of energon gained after selling stacks

                if(sellStacks == 0) //executes if the user inputs 0 on days 2-7
                    zeroCounter++; //updates the value of zeroCounter by 1

                if(zeroCounter == 3 && dayNo < 7) { //executes if zero is inputted three times on days 2-6 (must not execute on day 7)
                    zeroCounter++; //ensures that zeroCounter does not stay at 3 by adding another one
                    zeroThreeTimes(&dayNo);
                }
            }

            zeroCounter = 0; //resets the counter to 0

            if (weeklyEnergonStacks > 0) //must only execute if there are stacks left after day 7
                recycledStacks += weeklyEnergonStacks; //updates the number of recycled stacks from the weekly energon stacks

            bonusFeatureConfirmation(&recycledStacks, &dayNo, &sellStacks, &energonStorage, &weekNo);
        }
    }
    
    if (weeklyEnergonStacks > 0 && energonStorage >= 800) { //will only execute after week 10 and makes sure that this won't be printed when to user inputs 0 on week 10 or if energon is below 800  to avoid blank space
        printf("\n\n");
        printf("---------------------------------------------------------------------------\n\n");
    }
        
    if (energonStorage >= 1000000) //will only execute after week 10
        printf("Congratulations! Soundwave have reached the goal of having 1000000 Energon or higher with a total of %d Energon. \n", energonStorage);

    else if (energonStorage < 1000000 && energonStorage >= 800)
        printf("Unfortunately Soundwave have not reached the goal of having 1000000 Energon or higher having only a total of %d Energon. \n", energonStorage);

    return 0;
}