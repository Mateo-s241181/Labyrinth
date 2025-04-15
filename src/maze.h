#ifndef HEADER_H
#define HEADER_H

#include <iostream>
#include <string>
#include <vector>
#include <sstream>

#include "position.h"

/// Function just returns five
int returnFive();

struct Maze {

    ///@brief Number of Rows of the Maze
    int rows;
     ///@brief Number of Columns of the Maze
    int cols;

    ///@brief Character, which moves through the Maze
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
    Position MoveCharInit(){

        Position pos;

        //If the grid is empty or the rows or cols are zero values, the function should return a default position (-1, -1)
        if (rows == 0 || cols == 0 || grid == std::vector<std::vector<char>> {}) {
            std::cout<< "FEHLER IN MOVECHARINIT";
            return pos;
        }

        for(int i = 0; i < cols; i++) {
            if (grid[rows -1][i] == ' '){
                grid[rows -1][i] = moveChar;
                
                pos.row = rows - 1;
                pos.col = i;
                return pos;
            }
        }

        std::cout << "No valid starting position found in given Maze";
        return pos;
    }



    /// @brief The Method move() moves the Character once and returns the new Position of the character.
    /// @param character specifies the position of the character on the grid 
    Position move(Position pos){

        //check if specified position is inside of the grid again (shouldn't be at this point)
        if (pos.row == -1 || pos.col == -1 || pos.col == cols || pos.row == rows) {
            std::cout << "Invalid Input in method: move()";
            return pos;
        }

        Position newPos;

        //check if the Space over the character is occupied
        if (grid[pos.row - 1][pos.col] == ' ') {

            grid[pos.row][pos.col] = ' ';
            grid[pos.row - 1][pos.col] = moveChar;

            pos.row -= 1;
        }

        //check if the Space on the right of the character is occupied
        else if (grid[pos.row][pos.col + 1] == ' '){

            grid[pos.row][pos.col] = ' ';
            grid[pos.row][pos.col + 1] = moveChar;

            pos.col += 1;
        }

        return pos;
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

};


#endif