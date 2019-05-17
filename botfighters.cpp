#include <iostream>
#include <stdlib.h>
#include <math.h>
using namespace std;
enum results { P1, P2, TIE, EXIT, NONE };
enum Move { UP, DOWN, LEFT, RIGHT, NONE };

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
  {"z", NONE}
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

void Grid::turn() {
  cout << "PLAYER 1's MOVE:" << endl;   //gets keys for bot's move
  Move p1_move = get_move();
  cout << "PLAYER 2's MOVE:" << endl;
  Move p2_move = get_move();

  bot_update(grid.player1 p1_move);   //update the postions of the bots
  bot_update(Grid.player2, p2_move);

  display();
}
result is_game_over() {   //checks conditions to see if game is over, and if so, who won

  results result = None;

  if(turncount == 60 || (Grid.Player1.coors() == Grid.Player2.coors())) {
    if(Grid.Player1.points() > Grid.Player2.points()) {
      result = P1;
    }
    if(Grid.Player2.points() > Grid.Player1.points()) {
      result = P2;
    }
    else{
      result = TIE;
    }
  }

  result = if (Grid.Player1.health() <= 0) result = P1;
  result = if (Grid.Player2.health() <= 0) result = P2;
  result = if (Grid.Player1.health() <= 0 && Grid.Player2.health() <= 0) result = TIE;


  return result;
}

void Grid::applysquare(bot abot) {    //applies changes to points and health of bots based on square
  if(abot.bottag == 1) {
    if(row[Grid.Player1.botpos.rpos].col[Grid.Player1.botpos.cpos].state == EMPTY) {
      return;
    }

    if(row[Grid.Player1.botpos.rpos].col[Grid.Player1.botpos.cpos].state == GAINPOINTS) {
      Grid.Player1.points++;
      return;
    }
    if(row[Grid.Player1.botpos.rpos].col[Grid.Player1.botpos.cpos].state == LOSEHEALTH) {
      Grid.Player2.health -= 10;
      return;
    }
  }
  if(abot.bottag == 2) {
    if(row[Grid.Player2.botpos.rpos].col[Grid.Player2.botpos.cpos].state == EMPTY) {
      return;
    }
    if(row[Grid.Player2.botpos.rpos].col[Grid.Player2.botpos.cpos].state == GAINPOINTS) {
      Grid.Player2.points++;
      return;
    }
    if(row[Grid.Player2.botpos.rpos].col[Grid.Player2.botpos.cpos].state == LOSEHEALTH) {
      Grid.Player1.health -= 10;
      return;
    }
  }

}

void Grid::start() {

  turncount = 0;

  while(!ended) { //checks if game ends and if not, do another turn
    turn();
    ++turncount;
    endcheck();
  }
  if(result == Grid.Player1) {
    cout << "--------PLAYER 1 WINS-----------" << endl;
  }
  if(result == Grid.Player2) {
    cout << "--------PLAYER 2 WINS-----------" << endl;
  }

  if(result == TIE) {
    cout << "--------TIE GAME-----------" << endl;
  }
  if(result == EXIT) {
    cout << "GAME ABANDONED" << endl;
  }
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

  Grid gameGrid = new Grid(size);

  int turncount = 0;

  while(endchecker()) { //checks if game ends and if not, do another turn
    gameGrid.display();
    turn();
    ++turncount;
    endchecker();
  }

	return 0;
	}
