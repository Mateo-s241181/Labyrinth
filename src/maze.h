#ifndef HEADER_H
#define HEADER_H

#include <string>
#include <vector>
#include <iostream>
#include <sstream>

#include "position.h"

/// Function just returns five
int returnFive();

struct Maze {

    //describing size of the maze
    int rows;
    int cols;

    //Describes, which Character moves through the Maze
    char moveChar;

    //Grid is a 2d-Matrix
    std::vector<std::vector<char>> grid;

    //-------------------------------------------------------------------------------------------------------------------------------
    //Methods:
    //-------------------------------------------------------------------------------------------------------------------------------

    ///Instantiates empty object of type Maze with cols, rows = 0, an empty grid and a moveChar 'o'
    Maze(){
        rows = 0;
        cols = 0;
        grid = {};
        moveChar = 'o';
    }

    ///MazeInit initializes a Maze with a given grid. REQUIREMENT: The grid needs to be rectangular
    void MazeInit(std::vector<std::vector<char>> v) {

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



    ///Creates a String-representation of the Maze's Grid 
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

        if (rows == 0 || cols == 0) {
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

        //check is specified position is inside of the grid
        if (pos.row == -1 || pos.col == -1 || pos.col == cols || pos.row == rows) {
            
            std::cout << "Invalid Input in method: move()";
            return pos;
        }

        Position newPos;

        //check if the Space over the character is occupied
        if (grid[pos.row - 1][pos.col] == ' ') {

            grid[pos.row][pos.col] = ' ';
            grid[pos.row - 1][pos.col] = moveChar;

            newPos.row = pos.row - 1;
            newPos.col = pos.col;
        }

        //check if the Space on the right of the character is occupied
        else if (grid[pos.row][pos.col + 1] == ' '){

            grid[pos.row][pos.col] = ' ';
            grid[pos.row][pos.col + 1] = moveChar;

            newPos.row = pos.row;
            newPos.col = pos.col + 1;
        }

        return newPos;
    }

};


#endif