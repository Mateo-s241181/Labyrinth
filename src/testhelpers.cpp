
#include <vector>
#include "position.h"

/// @brief Finds a character in a grid
/// @param c Character to search for
/// @param v Given grid of chars
/// @return Object of type Position, which specifies the location of the character on the grid
Position findChar(char c, std::vector<std::vector<char>> v){

    Position charPos;

    //Range thorugh rows
    for(size_t i = 0; i < v.size(); i++){

        //range through columns of the i'th rot
        for(size_t j = 0; j < v[i].size(); j++){
            
            if(v[i][j] == c){

                charPos.row = i;
                charPos.col = j;
                return charPos;
            }
        }
    }
}



