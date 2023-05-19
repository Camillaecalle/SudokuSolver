// Author: Camilla Calle
// Date: April 24, 2023
// File: SudokuSolver.cpp
// Description: This file reads in my given input (puzzle1.csv) and is the implementatation of my 9 X 9 sudoku solver.

#include "SudokuSolver.hpp"
#include <fstream>
#include <sstream>
#include <iostream>
#include <chrono>
#include <thread>
#define M 4
#define N 5


//Constructors:

// SudokuSolver(), the default constructor initializes an emtpy board, that is, a board filled with zeros 
// (an array of 9 arrays, each filled with 9 zeros). This board will be marked unsolvable. 

SudokuSolver::SudokuSolver(){
    for (int i = 0; i < 9; i++){ 
        board_[i] = new int[9]; 
    }
    for (int i = 0; i < 9; i++){
        for (int j = 0; j < 9; j++){
            board_[i][j] = 0; //Created a Sudoku board / 2D array with all elements in array equal to 0.
        }
    }
} // Works

// the parameterized constructor reads the input file to initialize the board.
// The input files consist of 9 digits on each row separated by commas, and 9 rows
// separated by new line characters \n, corresponding to a sudoku board. Empty squares
// contain the digit 0. After reading the puzzle, the constructor tries to solve it and
// records whether the puzzle has a solution or not.
// TIP! We strongly suggest that you break down this task with the use of helper functions
// (reading the file, solving the puzzle etc.) and thoroughly test and debug each functionality separately.

SudokuSolver::SudokuSolver(std::string input_file){
    std::ifstream fin(input_file); // Reading in file
    if (fin.fail()){
        std::cerr << "File failed to open. \n";
        exit(1);  //Addresses if file does not open.
    }
    for (int i = 0; i < 9; i++){
        board_[i] = new int[9];
    }
    std::string line;
    int row = 0;
    while (getline(fin, line)){ //Reading Sudoku board puzzle information. 
        std::stringstream ss(line);
        std::string pos;
        int col = 0;
        while (getline(ss, pos, ',')){
            board_[row][col] = std::stoi(pos); //converts string to int.
            col++;
        }
        row++;
    }
    SudokuSolverHelperFunction(board_); // Calling helper function that tries to solve it and records solution. 
}

// Needed helper function solve puzzle and record whether it has a solution using recursive backtracking.

bool SudokuSolver::SudokuSolverHelperFunction(int** board){
    Sudoku::Location solveBoard;
    for (int i = 0; i < 9; i++){ //row
        for (int j = 0; j < 9; j++){ //col
            solveBoard.row = i;
            solveBoard.col = j;
            if (board[i][j] == 0){ 
                for (int value = 0; value <= 9; value++){
                    if (checkLegalValue(value, solveBoard)){ //Calls checkLegalValue function.
                        board[i][j] = value; 
                        if (SudokuSolverHelperFunction(board)){ //Calls SudokuSolverHelperFunction function.
                            isSolvable_ = true;
                            return true;
                        }
                        board[i][j] = 0;
                    }
                }
                isSolvable_ = false;
                return false;
            }
        }
    }
    isSolvable_ = true;
    return true;
}

//Accessors and mutators:

// isPuzzleSolvable() returns true if the puzzle is solvable, false otherwise. We suggest you keep track of this when 
// solving the problem at construction, rather than solving the puzzle again each time this function is called.

bool SudokuSolver::isPuzzleSolvable(){
    return isSolvable_;
}

//setSolvable() records the puzzle as being solvable.

void SudokuSolver::setSolvable(){
    isSolvable_ = true;
}

//getPuzzleNumbers() returns the  2D pointer array representing the puzzle

int **SudokuSolver::getPuzzleNumbers(){ // Accessor
    return board_;
}

//setPuzzleNumbers(int** puzzle) sets the  2D pointer array representing the puzzle to the value of the parameter 

void SudokuSolver::setPuzzleNumbers(int** puzzle){
    for (int i = 0; i < 9; i++){
        for (int j = 0; j < 9; j++){
            board_[i][j] = puzzle[i][j]; //Sets 2D pointer array elements [i][j] = param values. 
        }
    }
}

// returnNextEmpty() returns a Location object with the coordinates of
//  the first 0 found in the 2D pointer array, meaning that it is an empty
//  square in the sudoku board. To find the first empty square you must read
//  the 2D array from top-left (0,0) to bottom right (8,8), one row at a time.
//  Set the row and col of the Location to the indices
//   at which the first 0 is found in the 2D array. If there are no empty squares
//   the Location object should have row and col values of -1.
// a pointer which references an item in the array.

Sudoku::Location SudokuSolver::returnNextEmpty(){
    Sudoku::Location location; //created instance of location
    location.row = -1; //set to default -1
    location.col = -1;
    for (int i = 0; i < 9; i++){ // made a nested loop to go through rows and cols, and if the puzzle[row][col] is 0, then I set the row and col == 1 and j, respectively. 
        for (int j = 0; j < 9; j++){
            if (board_[i][j] == 0){
                location.row = i;
                location.col = j;
                return location; 
            }
        }
    }
    return location; 
}

//Utility functions:

// checkLegalValue(int value, Sudoku::Location location) returns true if the value parameter (which can take on values 1-9) can legally
// be placed at the given location in the 2D array without breaking the rules of sudoku. It
// returns false if placing value at location is not a legal move. Remember, in order to be a valid move, the value must be unique with
// a row, column, and sub-grid.

// Hint: to define the top-left corner of the sub-grid in which the location falls, integer division of the coordinates (row and col) by 3 
// will come in handy since all sub-grids are 3x3.

bool SudokuSolver::checkLegalValue(int value, Sudoku::Location location){
    for (int i = 0; i < 9; i++){ // checked through row, if arr element has the same value
        if ((board_[location.row][i] == value)){
            return false;
        }
    }
    for (int i = 0; i < 9; i++){ // repeated for column
        if ((board_[i][location.col] == value)){
            return false;
        }
    } // Accounting for subgrids
    int subRow = location.row - (location.row % 3); 
    int subCol = location.col - (location.col % 3);
    for (int i = subRow; i < subRow + 3; i++){ // I checked subgrid of my 2D array using nested for loop
        for (int j = subCol; j < subCol + 3; j++){ //to see arr element == value
            if (board_[i][j] == value){
                return false;
            }
        }
    }
    return true;
}

//display() will display the board as illustrated below: 

// Example:
// N X X  | N X N  | X X N
// N X N  | X N N  | X X X
// N X N  | N X X  | X X X
// - - - - - - - - - - - - 
// X N X  | N X N  | N X X
// X X X  | X N X  | X X X
// X X N  | N X N  | X N X
// - - - - - - - - - - - - 
// X X X  | X X N  | N X N
// X X X  | N N X  | N X N
// N X X  | N X N  | X X N

// N is an integer 1-9 (the function displays the actual integer not an N)

// X represents a blank box where there is a zero (the function displays the X not the zero)


void SudokuSolver::display(){
    int row = 1;
    int col = 1;
    for (int i = 0; i < 9; i++){
        for (int j = 0; j < 9; j++){
            if (board_[i][j] == 0){
                std::cout << "X";
            }
            else {
                std::cout << board_[i][j];
            }
            if (col % 3 == 0 && col != 9){
                std::cout << "|"; // After every 3 numbers (columns), we have a " | " to separate sub-grids.
            }
            col++;
        }
        std::cout << "\n";
        if (row % 3 == 0 && row != 9){
            std::cout << "- - - - - - - - - - - -\n"; // After every 3 rows, we have 12 dashes " - " to separate the sub-grids.
        }
        col = 1;
        row++;
    }
}
