#include "maze.h"

int main() {
    
    Maze m;

    std::vector<std::vector<char>> v1 = {
      {'#', '#', '#', ' '},
      {'#', '#', ' ', ' '},
      {'#', ' ', ' ', '#'},
      {'#', ' ', '#', '#'},
    };

    m.MazeInit(v1);

    std::cout << m.String() << "\n\n\n";

    Position pos = m.MoveCharInit();

    std::cout << m.String() << "\n\n\n";

    while (!m.MazeIsSolved()) {

        pos = m.move(pos);

        std::cout << m.String() << "\n\n\n";
    };


    std::cout << "Maze is solved!";
}