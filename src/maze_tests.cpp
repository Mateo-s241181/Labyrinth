#include <catch2/catch_test_macros.hpp>

#include <vector>

#include "maze.h"


TEST_CASE("Basic testing workflow", "[Basic Testing]") {
  CHECK(returnFive() == 5);
}




TEST_CASE("Constructor of struct Maze", "[Maze Constructor Test]") {
  Maze m;
  std::vector<std::vector<char>> v = {};

  //CHECK(std::equal(m.grid.begin(), m.grid.end(), v.begin()));
  CHECK(m.grid == v);
  CHECK(m.cols == 0);
  CHECK(m.rows == 0);
}




TEST_CASE("Initialization of an Object with Type Maze", "[Maze Initialization Test]") {
  Maze m;
  std::vector<std::vector<char>> v1 = {
    {'#', '#', '#', ' ', },
    {'#', '#', ' ', ' ', },
    {'#', ' ', ' ', '#', },
    {'#', ' ', '#', '#', },
  };

  std::vector<std::vector<char>> v2 = {
    {'#', '#', '#', ' ', },
    {'#', '#', ' '},
    {'#', ' ', ' ', '#', },
    {'#', ' ', '#', '#', },
  };

  std::vector<std::vector<char>> v3 = {};
  
  m.MazeInit(v1);

  //CHECK(std::equal(m.grid.begin(), m.grid.end(), v.begin()));
  CHECK(m.grid == v1);
  CHECK(m.cols == 4);
  CHECK(m.rows == 4);

  m.MazeInit(v2);

  //CHECK(std::equal(m.grid.begin(), m.grid.end(), v.begin()));
  CHECK(m.grid == std::vector<std::vector<char>> {});
  CHECK(m.cols == 0);
  CHECK(m.rows == 0);

  m.MazeInit(v3);

  CHECK(m.grid == std::vector<std::vector<char>> {});
  CHECK(m.cols == 0);
  CHECK(m.rows == 0);
}




TEST_CASE("Initializing starting point", "[Starting Position Test]"){

  Maze m;
  Position pos;
  std::vector<std::vector<char>> v1 = {
    {'#', '#', '#', ' ', },
    {'#', '#', ' ', ' ', },
    {'#', ' ', ' ', '#', },
    {'#', ' ', '#', '#', },
  };

  std::vector<std::vector<char>> v2 = {
    {'#', '#', '#', ' ', },
    {'#', '#', ' ', ' ', },
    {'#', ' ', ' ', '#', },
    {'#', '#', '#', '#', },
  };

  m.MazeInit(v1);
  pos = m.MoveCharInit();

  std::vector<std::vector<char>> expected = {
    {'#', '#', '#', ' ', },
    {'#', '#', ' ', ' ', },
    {'#', ' ', ' ', '#', },
    {'#', m.moveChar, '#', '#', },
  };

  CHECK(m.grid == expected);
  CHECK(pos.row == 3);
  CHECK(pos.col == 1);

  m.MazeInit(v2);
  pos = m.MoveCharInit();

  CHECK(m.grid == v2);
  CHECK(pos.row == -1);
  CHECK(pos.col == -1);
}



TEST_CASE("String Output of Maze", "[Maze as String-Output]") {

  Maze m;
  std::vector<std::vector<char>> v1 = {
    {'#', '#', '#', ' ', },
    {'#', '#', ' ', ' ', },
    {'#', ' ', ' ', '#', },
    {'#', ' ', '#', '#', },
  };

  m.MazeInit(v1);

  std::string expected_1 = "### \n##  \n#  #\n# ##\n";

  CHECK(m.String() == expected_1);

  //Calling the Method without saving the return value, no need for a object of type Position
  m.MoveCharInit();

  std::string expected_2 = "### \n##  \n#  #\n#o##\n";

  CHECK(m.String() == expected_2);

}



TEST_CASE("Move Method", "[Moving the Character]"){

  Maze m;
  Position pos;
  std::vector<std::vector<char>> v1 = {
    {'#', '#', '#', ' '},
    {'#', '#', ' ', ' '},
    {'#', ' ', ' ', '#'},
    {'#', ' ', '#', '#'},
  };
  
  std::vector<std::vector<char>> expected_1 = {
    {'#', '#', '#', ' '},
    {'#', '#', ' ', ' '},
    {'#', 'o', ' ', '#'},
    {'#', ' ', '#', '#'},
  };

  std::vector<std::vector<char>> expected_2 = {
    {'#', '#', '#', ' '},
    {'#', '#', ' ', ' '},
    {'#', ' ', 'o', '#'},
    {'#', ' ', '#', '#'},
  };

  std::vector<std::vector<char>> emptyGrid = {};

  m.MazeInit(v1);
  
  pos = m.move(m.MoveCharInit());

  CHECK(m.grid == expected_1);

  //Calling move() without saving it's value in another variable
  m.move(pos);

  CHECK(m.grid == expected_2);

  m.MazeInit(emptyGrid);
  pos = m.MoveCharInit();

  CHECK(pos.row == -1);
  CHECK(pos.col == -1);

  pos = m.move(pos);

  CHECK(pos.row == -1);
  CHECK(pos.col == -1);
}





TEST_CASE("Wincondition", "[Wincondition Test]"){

  Maze m;

  std::vector<std::vector<char>> v1 = {
    {'#', '#', '#', 'o'},
    {'#', '#', ' ', ' '},
    {'#', ' ', ' ', '#'},
    {'#', ' ', '#', '#'},
  };
  
  std::vector<std::vector<char>> v2 = {
    {'#', '#', '#', 'x'},
    {'#', '#', ' ', ' '},
    {'#', 'o', ' ', '#'},
    {'#', ' ', '#', '#'},
  };

  std::vector<std::vector<char>> v3 = {
    {'#', '#', '#', ' '},
    {'#', '#', ' ', ' '},
    {'#', ' ', 'o', '#'},
    {'#', ' ', '#', '#'},
  };

  m.MazeInit(v1);

  CHECK(m.MazeIsSolved() == true);

  m.MazeInit(v2);

  CHECK(m.MazeIsSolved() == false);

  m.MazeInit(v3);

  CHECK(m.MazeIsSolved() == false);
}