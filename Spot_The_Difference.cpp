/*****************************************
** File: Spot_The_Difference
** Author: Mosi Farquharson
** Date: 9/23/24
** E-mail: mosif1@umbc.edu
**
** 
** This program creates a spot the difference simulation using ASCII characters as the difference
**
**
***********************************************/



#include <iostream>
#include <string>
#include <fstream>
#include <ctime>
#include <iomanip>
#include <cstdlib>


using namespace std;

const int ROWS = 10;
const int COLS = 21;

// function protoypes
void LoadFile(char pics[ROWS][COLS]);
void displayArt(char pics[ROWS][COLS]);
void clearArray(char pics[ROWS][COLS]);
void playGame(char pics[ROWS][COLS]);
void guessChange(int row, int col);
int conversion(int num);
bool picloaded(char pics[ROWS][COLS]);
int mainMenu();



//-------------------------------------------------------
// Name:Loadfile
// Description: Takes pieces of a picture from a text file and puts them into an array
// PreCondition: 
//   - the file name is the correct path needed to load
//   - the file should be seperated into 3 lines for rows, cols, character to load correctly
// PostCondition: 
//   - multidimensional array created
//   - if open the file chosen is closed correctly
//---------------------------------------------------------
void LoadFile(char pics[ROWS][COLS]){

    string file;
    string lines;
    int row;
    int col;
    char symbol;


    cout << "what file would you like to open? " << endl;
    cin >> file;

    fstream inputStream;

    inputStream.open(file);
    //cgecks if file is not open of it isnt then it continues
    if (!inputStream.is_open()){
        cout << "file not found" << endl;

    }else{
        cout << "Done" << endl;
    }


    for (int i = 0; i < ROWS; i++){ // creates the multidimensional array

        for (int j = 0; j < COLS; j++){

            pics[i][j] = ' ';
        }
    }

    //clearArray(pics); //clears the array and make sure theres nothing in it before it loads a new file

    

    while (inputStream >> row >> col >> symbol){ //getlines every line ignoring space

        if (row >= 0 && row < ROWS && col >= 0 && col < COLS){

            pics[row][col] = symbol;
        }

    }

    inputStream.close();

    
}


//-------------------------------------------------------
// Name: displayArt
// Description: displays current picture used for the game
// PreCondition: 
//   - multidimensional array must be made containing rows and columns
//   - the array must be occupied with the pieces
// PostCondition: 
//   - outputs current art for the game
//  
//---------------------------------------------------------
void displayArt(char pics[ROWS][COLS]){

    cout << "    "; // to line up with the pictures being made as well as the output
    for (int i = 0; i < COLS; i++){

        cout << setw(2) << i << ' ';

    }cout << endl;
    //loop to display the art. uses setw to spread out the numbers
    for (int i = 0; i < ROWS; i++){

        cout <<  setw(2) << i <<  ' ';

        for (int j = 0; j < COLS; j++){

            cout <<  setw(2) << pics[i][j] << ' ';
        }cout << endl;
    } 
}




//-------------------------------------------------------
// Name:clearArray
// Description: clears occupied array into blank spaces so no pictures are in it
// PreCondition: 
//   - array must be created and occupied
//   
// PostCondition: 
//   - empty array with just the rows and columns displayed
//   - 
//---------------------------------------------------------
/// did not use but still incorperated, code still works the same way
void clearArray(char pics[ROWS][COLS]){
    //makes the array clear by looping and using the null terminator to make space
    for (int i = 0; i < ROWS; i++){

        for (int j = 0; j < COLS; j++){

            pics[i][j] = '\0';
        }
    }

}


//-------------------------------------------------------
// Name: conversion
// Description: converts any number into a character creating the correct ASCII value
// PreCondition: 
//   - valid integer
//   - 
// PostCondition: 
//   - a character from that value is made
//   - 
//---------------------------------------------------------

int conversion(int num){
    //by making a number a charcacer it in turn makes it an ascii value
    char ascii_int = num;

    return ascii_int;
}



//-------------------------------------------------------
// Name:playGame
// Description: main functionality of the game, calls all the functions to make the game work
// PreCondition: 
//   - multidimensional array must be created
//   - the array must be filled
// PostCondition: 
//   - main game logic functions
//   - 
//---------------------------------------------------------
void playGame(char pics[ROWS][COLS]){
    if (!picloaded(pics)){
        cout << "load a picture in first" << endl;
        return;
    }

    //copy of the multidimensional array
    char pics2[ROWS][COLS];


    //copies the values of the array into a new one
    for (int i = 0; i < ROWS; i++){

        for (int j = 0; j < COLS; j++){

            pics2[i][j] = pics[i][j];
        }
    }

    //picks random number between ROWS(10) and COLS(21)
    int randRow = rand() % ROWS;
    int randCol = rand() % COLS;

    //min is the minimum value for the ascii numbers and max is the maximum
    int min = 33;
    int max = 126;

    //formula to get a random number between the maximum and minimu
    int randnum = rand() % (max - min + 1) + min;

    //converts that random number into and ascii value
    int randascii = conversion(randnum);

    //takes the coordinate of the rows and cols and replaces it with a the random characater
    pics2[randRow][randCol] = randascii;

    //display the first picture then the 2nd so the player can see what changes
    displayArt(pics);
    displayArt(pics2);

    //calls guess change to complete game
    guessChange(randRow, randCol);


    

    
}



//-------------------------------------------------------
// Name:guessChange
// Description: guesses what row and column the changed character is in
// PreCondition: 
//   - valid integer for rows
//   - valid integer for columns
// PostCondition: 
//   - confirms if the row and column is correct
//   - 
//---------------------------------------------------------
void guessChange(int row, int col){
    bool found = false;
    int rowguess = 0;
    int colguess = 0;
do{
    cout << "what row is the change in? ";

    cin >> rowguess;

    cout << "what column is the change in? ";
    
    cin >> colguess;

    if (rowguess == row && colguess == col){

        cout << "You are correct!" << endl;

        found = true;

    }else{

        cout << "That is Incorrect!" << endl;
    }
}while(!found);


}



//-------------------------------------------------------
// Name:picloaded
// Description: checks if the array is populated
// PreCondition: 
//   - multidimentional array must be made
//   -
// PostCondition: 
//   - will confirm whether or not array is populated
//   - 
//---------------------------------------------------------
bool picloaded(char pics[ROWS][COLS]){
    for (int i = 0; i < ROWS; i++){

        for(int j = 0; j < COLS; j++){
            
            //checks if they have null terminators or empty space
            if (pics[i][j] == ' ' || pics[i][j] == '\0'){ 

                return true;
            }
        }
    }

    return false;
}

//-------------------------------------------------------
// Name:mainMenu
// Description: displays game options
// PreCondition: 
//   - nothing
//   - 
// PostCondition: 
//   - displays option for game function
//   - returns number picked from the options
//---------------------------------------------------------
int mainMenu(){
    int pick;

    cout << "What would you like to do? \n"
        "1. Load ASCII art from the File" "\n2. Display Art" "\n3. Play Game" "\n4. Exit" << endl;
    cin >> pick;
    
    return pick;
}

int main(){
    srand(time(NULL));

    char pics[ROWS][COLS];

    bool isLoaded = false;

    int choice = 0;

    cout << "Welcome to the Spot the Difference Game" << endl;

   while (choice != 4){
    choice = mainMenu();
    switch(choice){
        case 1:
        LoadFile(pics);
        isLoaded = picloaded(pics); // flag for the rest of the options to check if you need to load the file or not
        break;

        case 2:
        if (isLoaded == true){
            displayArt(pics);
        }else{
            cout << "load file first" << endl;
        }
        break;

        case 3:
        if (isLoaded == true){                                  
        playGame(pics);
        }else{
            cout << "load file first" << endl;
        }
        break;

        case 4:
        cout << "Thanks for playing" << endl;
        break;

        default:
        break; 
    }
   }
    

    





    return 0;
}