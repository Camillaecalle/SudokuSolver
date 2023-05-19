//Author: Camilla Calle
//Date: April 23, 2023
//File: SudokuSolver.hpp
//Description: In this file I declared my private member variables and public member functions for my Sudoku Solver.


#ifndef SUDOKU_SOLVER_HPP_
#define SUDOKU_SOLVER_HPP_
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#define M 4
#define N 5
 
//We define Location within the Sudoku namespace.
//To use Location, you must specify the namespace Sudoku::Location
//Just like you do when using the standard namespace std::
namespace Sudoku
{ 
  struct Location
  {
    int row;
    int col;
  };
}

class SudokuSolver
{
public:
 
//Add your public members here

//Constructors:

// SudokuSolver(), the default constructor initializes an emtpy board, that is, a board filled with zeros 
// (an array of 9 arrays, each filled with 9 zeros). This board will be marked unsolvable.

SudokuSolver();

// the parameterized constructor reads the input file to initialize the board.
// The input files consist of 9 digits on each row separated by commas, and 9 rows
// separated by new line characters \n, corresponding to a sudoku board. Empty squares
// contain the digit 0. After reading the puzzle, the constructor tries to solve it and
// records whether the puzzle has a solution or not.
// TIP! We strongly suggest that you break down this task with the use of helper functions
// (reading the file, solving the puzzle etc.) and thoroughly test and debug each functionality separately.

SudokuSolver(std::string input_file);

// Needed helper function to solve puzzle and record whether it has a solution using recursive backtracking.

bool SudokuSolverHelperFunction(int** board);

//Accessors and mutators:

// isPuzzleSolvable() returns true if the puzzle is solvable, false otherwise. We suggest you keep track of this when 
// solving the problem at construction, rather than solving the puzzle again each time this function is called.

bool isPuzzleSolvable();

//setSolvable() records the puzzle as being solvable.

void setSolvable();

//getPuzzleNumbers() returns the  2D pointer array representing the puzzle

int** getPuzzleNumbers();

//setPuzzleNumbers(int** puzzle) sets the  2D pointer array representing the puzzle to the value of the parameter 

void setPuzzleNumbers(int** puzzle);

// returnNextEmpty() returns a Location object with the coordinates of
//  the first 0 found in the 2D pointer array, meaning that it is an empty
//  square in the sudoku board. To find the first empty square you must read
//  the 2D array from top-left (0,0) to bottom right (8,8), one row at a time.
//  Set the row and col of the Location to the indices
//   at which the first 0 is found in the 2D array. If there are no empty squares
//   the Location object should have row and col values of -1.
// a pointer which references an item in the array.

Sudoku::Location returnNextEmpty();

//Utility functions:

// checkLegalValue(int value, Sudoku::Location location) returns true if the value parameter (which can take on values 1-9) can legally
// be placed at the given location in the 2D array without breaking the rules of sudoku. It
// returns false if placing value at location is not a legal move. Remember, in order to be a valid move, the value must be unique with
// a row, column, and sub-grid.

// Hint: to define the top-left corner of the sub-grid in which the location falls, integer division of the coordinates (row and col) by 3 
// will come in handy since all sub-grids are 3x3.

bool checkLegalValue(int value, Sudoku::Location location);

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

// After every 3 numbers (columns), we have a " | " to separate sub-grids. Note that each " | " is 
// preceded by two space characters and followed by a single space character.

// After every 3 rows, we have 12 dashes " - " to separate the sub-grids.

void display();


//Add your private members here

private:

//You must store the puzzle as a 2D pointer to int ( int** a pointer of pointers to int) used to dynamically allocate a 2-dimensional array.
// the default constructor initializes an emtpy board, that is, a board filled with zeros (an array of 9 arrays, each filled with 9 zeros). This 
// board will be marked unsolvable. 

int** board_ = new int*[9];

bool isSolvable_ {false}; //Marked unsolvable.

};

#endif
