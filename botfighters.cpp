#include <iostream>
#include <stdlib.h>
#include <math.h>
#include "Grid.h"

using namespace std;
enum results { P1, P2, TIE, EXIT, NONE };
enum Move { UP, DOWN, LEFT, RIGHT, STAY, END };

struct coor{
  int row;
  int column;
  
};

const map<char, Move> move_lookup {
  {"w", UP},
  {"a", DOWN},
  {"s", LEFT},
  {"d", RIGHT},
  {"x", END},
  {"z", STAY}
};

Move get_move() {
  char x;
  cin >> x;

  Move move = move_lookup[x];
  if (move != move_lookup.end()){
    return move;
  }
  cout << "Enter one of the wasd keys" << endl;
  get_move();
}

void turn(Grid grid) {
  cout << "PLAYER 1's MOVE:" << endl;   //gets keys for bot's move
  Move p1_move = get_move();
  cout << "PLAYER 2's MOVE:" << endl;
  Move p2_move = get_move();

  grid.bot_update(grid.player1, p1_move);   //update the postions of the bots
  grid.bot_update(grid.player2, p2_move);

}
results check_results(Grid & grid, int num_turns) {   //checks conditions to see if game is over, and if so, who won

  results result = NONE;

  if(num_turns == 60 || (grid.player1.coors() == grid.player2.coors())) {
    if(grid.player1.points() > grid.player2.points()) {
      result = P1;
    }
    if(grid.player2.points() > grid.player1.points()) {
      result = P2;
    }
    else{
      result = TIE;
    }
  }

  result = (grid.player1.health() <= 0) ? P2 : result;
  result = (grid.player2.health() <= 0) ? P1 : result;
  result = (grid.player1.health() <= 0 && grid.player2.health() <= 0) ? TIE : result;


  return result;
}

int main(const int argc, const char* const argv[]) {
	srand (time(NULL));
  int size = -1;
  if(argv[1] != NULL) {
    size = atoi(argv[1]);
  }

  while(size > 30 || size < 10) {
    cout << "Please enter a value for the size of the gameGrid between 10 and 30" << endl;
    cin >> size;
  }

  Grid* grid = new Grid(size);

  int turncount = 0;
  results result = NONE;

  while(result == NONE) { //checks if game ends and if not, do another turn
    cout << "PLAYER 1's MOVE:" << endl;   //gets keys for bot's move
    Move p1_move = get_move();
    cout << "PLAYER 2's MOVE:" << endl;
    Move p2_move = get_move();

    grid->bot_update(grid->player1, p1_move);   //update the postions of the bots
    grid->bot_update(grid->player2, p2_move);

    ++turncount;
    result = check_results(*grid, turncount);
  }

  switch (result)
  {
  case P1:
    cout << "--------PLAYER 1 WINS-----------" << endl;
    break;

  case P2:
    cout << "--------PLAYER 2 WINS-----------" << endl;
    break;
  
  default:
      cout << "--------TIE GAME-----------" << endl;
    break;
  }

	return 0;
	}
