#ifndef HEADER_H
#define HEADER_H

#include <iostream>
#include <string>
#include <vector>
#include <sstream>

#include "position.h"

struct Maze {

    ///@brief Number of Rows of the Maze
    int rows;
     ///@brief Number of Columns of the Maze
    int cols;

    ///@brief Character, that moves through the Maze
    char moveChar;

    ///@brief Maze is described by a grid, using a 2D-Matrix
    std::vector<std::vector<char>> grid;
    
    //-------------------------------------------------------------------------------------------------------------------------------
    //Method Definitions:
    //-------------------------------------------------------------------------------------------------------------------------------

    ///@brief Instantiates empty object of type Maze with cols, rows = 0, an empty grid and a moveChar 'o'
    Maze(){
        rows = 0;
        cols = 0;
        grid = {};
        moveChar = 'o';
    }

    ///@brief Initializes a Maze with a given grid. REQUIREMENT: The grid needs to be rectangular
    void MazeInit(std::vector<std::vector<char>> v) {

        //Checks if the grid is empty, avoiding problem of adressing an element of an empty vector
        if (v == std::vector<std::vector<char>> {}){
            std::cout << "An empty grid is not a Maze...";
            cols = 0;
            rows = 0;
            grid = v;
            return;
        }

        //Checks if grid is rectangular and resets the Maze if not so
        for (size_t i = 0; i < v.size(); i++){
            if (v[i].size() != v[0].size()) {
                
                grid = std::vector<std::vector<char>> {};
                cols = 0;
                rows = 0;
                return;
            }
        }
        
        grid = v;
        rows = v.size();
        cols = v[0].size();
    }



    ///@brief Creates a String-representation of the Maze's Grid
    std::string String() {
        std::ostringstream out;
        std::string result;
        
        for(int i = 0; i < rows; i++){
            for(int j = 0; j < cols; j++){
                //Append the Character to the result-string
                result += grid[i][j];
            }
            //Append a newline character at the end of each row
            result += '\n';
        }

        return result;
    }



    ///@brief Searches for an empty position in the lowest row of the maze, sets the MoveChar there and returns the position.
    ///@returns Position of moveChar, if it could be set. If the maze wasnt initialized correctly, it returns a position with row ans col = -1
    Position MoveCharInit(){

        Position pos;

        //If the grid is empty or the rows or cols are zero values, the function should return a default position (-1, -1)
        if (rows == 0 || cols == 0 || grid == std::vector<std::vector<char>> {}) {
            std::cout<< "Maze was not initalized properly";
            return pos;
        }

        //Search for an empty space in the lowest row, set the moveChar there and return the position
        //Requirement for Mazes => Must be solvable from every starting position in the lowest row
        for(int i = 0; i < cols; i++) {
            if (grid[rows -1][i] == ' '){
                grid[rows -1][i] = moveChar;
                
                pos.row = rows - 1;
                pos.col = i;
                return pos;
            }
        }

        //If no starting Position was found, the Function returns the position (-1, -1)
        std::cout << "No valid starting position found in given Maze";
        return pos;
    }

    
    /// @param pos Position, to be checked 
    /// @return true, if the position is valid, false if not
    bool ValidCharPosition(Position pos){

        if (pos.col == -1 || pos.row == -1 || pos.row >= rows || pos.col >= cols){
            return false;
        }
        return true;
    }

    
    /// @brief Returns the Character at a given Position in the Maze, or '?' if the specified position is not in the maze. Parameter is not a object of type position for easier implementation into loops
    /// @param row Row of the unknown character
    /// @param col Column of the unknown character
    char getChar(int row, int col){
        
        //preventing segfault error
        if (row < 0 || row >= rows || col < 0 || col >= cols){
            return '?';
        }

        return grid[row][col];
    }

    /// @brief Sets a character to a given position in the maze
    /// @param pos Location of the space in the grid
    /// @param c Character, to be placed at given position
    void setChar(Position pos, char c){
        
        ValidCharPosition(pos) ? grid[pos.row][pos.col] = c : 0;
    }
    
    
    /// @brief Searches for the moving character in the first Row. Returns, whether it was found or not.
    /// @return True if Maze is solved, false if not 
    bool MazeIsSolved(){

        //searach for moveChar in the first row
        for (auto el : grid[0]){

            if (el == moveChar) {
                return true;
            }
        }
        return false;
    }

    /// @brief Moves the Character one step upwards on the grid
    /// @param pos Specifies the Characters previos position
    void MoveUp(Position &pos){
        grid[pos.row - 1][pos.col] = moveChar;
        pos.row--;
    }

    /// @brief Moves the Character one step downwards on the grid
    /// @param pos Specifies the Characters previos position
    void MoveDown(Position &pos){
        grid[pos.row + 1][pos.col] = moveChar;
        pos.row++;
    }

    /// @brief Moves the Character one step to the right on the grid
    /// @param pos Specifies the Characters previos position
    void MoveRight(Position &pos){
        grid[pos.row][pos.col + 1] = moveChar;
        pos.col++;
    }

    /// @brief Moves the Character one step to the left on the grid
    /// @param pos Specifies the Characters previos position
    void MoveLeft(Position &pos){
        grid[pos.row][pos.col - 1] = moveChar;
        pos.col--;
    }

    /// @brief Solves any Maze by Backtracking
    /// @param pos Valid starting position
    void solveByBacktracking(Position &pos) {

        // Base case: Check if the maze is solved
        if (MazeIsSolved()) {
            std::cout << "Maze Solved!\n\n\n";
            std::cout << String();
            return;
        }
    
        // Check if the position is valid
        if (!ValidCharPosition(pos)) {
            std::cout << "Invalid position encountered during solving.\n";
            return;
        }
    
        // Try moving upwards
        if (getChar(pos.row - 1, pos.col) == ' ') {
            MoveUp(pos);
            //recursive call
            solveByBacktracking(pos);

            //if the maze wasn't solved, the position and the char at the current position need to be reset
            if (!MazeIsSolved()) {
                setChar(pos, ' ');
                pos.row++;
            }
        }
    
        // Try moving to the right
        if (getChar(pos.row, pos.col + 1) == ' ') {
            MoveRight(pos);
            solveByBacktracking(pos);

            //if the maze wasn't solved, the position and the char at the current position need to be reset
            if (!MazeIsSolved()) {
                setChar(pos, ' ');
                pos.col--;
            }
        }
    
        // Try moving downwards
        if (getChar(pos.row + 1, pos.col) == ' ') {
            MoveDown(pos);
            
            //if the maze wasn't solved, the position and the char at the current position need to be reset
            solveByBacktracking(pos);
            if (!MazeIsSolved()) { // Backtrack if not solved
                setChar(pos, ' ');
                pos.row--;
            }
        }
    
        // Try moving to the left
        if (getChar(pos.row, pos.col - 1) == ' ') {
            MoveLeft(pos);
            
            //if the maze wasn't solved, the position and the char at the current position need to be reset
            solveByBacktracking(pos);
            if (!MazeIsSolved()) { // Backtrack if not solved
                setChar(pos, ' ');
                pos.col++;
            }
        }
    }

};


#endif
