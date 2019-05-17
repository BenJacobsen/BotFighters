#include <iostream>
#include <stdlib.h>
#include <math.h>
using namespace std;
enum squarestate { BOT1SPOT, BOT2SPOT, GAINPOINTS, LOSEHEALTH, EMPTY };
enum results { BOT1, BOT2, TIE, EXIT, None };
enum dir { UP, DOWN, LEFT, RIGHT, NONE };

struct coor{
  int row;
  int column;
};

dir getkey() {  //translates keys to moves
  char x;
  cin >> x;
  if(x == 'w') {
    return UP;
  }
  if(x == 'a') {
    return LEFT;
  }
  if(x == 's') {
    return DOWN;
  }
  if(x == 'd') {
    return RIGHT;
  }
  if(x == 'x') {
    exiter = true;
    return NONE;
  }
  if(x == 'z') {
    return NONE;
  }
  cout << "Enter one of the wasd keys" << endl;
  getkey();
}

void Grid::turn() {
  dir bot1d;
  dir bot2d;
  cout << "PLAYER 1's MOVE:" << endl;   //gets keys for bot's move
  bot1d = getkey();
  cout << "PLAYER 2's MOVE:" << endl;
  bot2d = getkey();

  botupdate(bot1, bot1d);   //update the postions of the bots
  botupdate(bot2, bot2d);
  row[bot1.botpos.rpos].col[bot1.botpos.cpos].state = BOT1SPOT;
  if(row[bot2.botpos.rpos].col[bot2.botpos.cpos].state = BOT1SPOT) {
    endcheck();
  }
  else{
    row[bot2.botpos.rpos].col[bot2.botpos.cpos].state = BOT2SPOT;
  }
  display();
}
bool endChecker() {   //checks conditions to see if game is over, and if so, who won

  results results = None;

  if(turncount == 60 || (bot1.botpos.rpos == bot2.botpos.rpos && bot1.botpos.cpos == bot2.botpos.cpos)) {
    if(bot1.points > bot2.points) {
      winner = BOT1;
      return;
    }
    if(bot2.points > bot1.points) {
      winner = BOT2;
      return;
    }
    if(bot1.points == bot2.points) {
      winner = TIE;
      return;
    }
  }

  return false;
}

void Grid::botupdate(bot bot, dir botd) {   //updated the bot's position, and the game Grid
  if(bot.bottag == 1) {
    if(botd == UP) {
      if(bot1.botpos.rpos == 0) {
        return;
      }
      row[bot1.botpos.rpos].col[bot1.botpos.cpos].state = EMPTY;
      bot1.botpos.rpos--;
    }
    if(botd == DOWN) {
      if(bot1.botpos.rpos == bsize-1) {
        return;
      }
      row[bot1.botpos.rpos].col[bot1.botpos.cpos].state = EMPTY;
      bot1.botpos.rpos++;
    }
    if(botd == LEFT) {
      if(bot1.botpos.cpos == 0) {
        return;
      }
      row[bot1.botpos.rpos].col[bot1.botpos.cpos].state = EMPTY;
      bot1.botpos.cpos--;
    }
    if(botd == RIGHT) {
      if(bot1.botpos.cpos == bsize-1) {
        return;
      }
      row[bot1.botpos.rpos].col[bot1.botpos.cpos].state = EMPTY;
      bot1.botpos.cpos++;
    }
    if(botd == NONE) {
      return;
    }
    applysquare(bot1);

  }
  if(bot.bottag == 2) {
    if(botd == UP) {
      if(bot2.botpos.rpos == 0) {
        return;
      }
      row[bot2.botpos.rpos].col[bot2.botpos.cpos].state = EMPTY;
      bot2.botpos.rpos--;
    }
    if(botd == DOWN) {
      if(bot2.botpos.rpos == bsize-1) {
        return;
      }
      row[bot2.botpos.rpos].col[bot2.botpos.cpos].state = EMPTY;
      bot2.botpos.rpos++;
    }
    if(botd == LEFT) {
      if(bot2.botpos.cpos == 0) {
        return;
      }
      row[bot2.botpos.rpos].col[bot2.botpos.cpos].state = EMPTY;
      bot2.botpos.cpos--;
    }
    if(botd == RIGHT) {
      if(bot2.botpos.cpos == bsize-1) {
        return;
      }
      row[bot2.botpos.rpos].col[bot2.botpos.cpos].state = EMPTY;
      bot2.botpos.cpos++;
    }
    applysquare(bot2);


  }
}
void Grid::applysquare(bot abot) {    //applies changes to points and health of bots based on square
  if(abot.bottag == 1) {
    if(row[bot1.botpos.rpos].col[bot1.botpos.cpos].state == EMPTY) {
      return;
    }

    if(row[bot1.botpos.rpos].col[bot1.botpos.cpos].state == GAINPOINTS) {
      bot1.points++;
      return;
    }
    if(row[bot1.botpos.rpos].col[bot1.botpos.cpos].state == LOSEHEALTH) {
      bot2.health -= 10;
      return;
    }
  }
  if(abot.bottag == 2) {
    if(row[bot2.botpos.rpos].col[bot2.botpos.cpos].state == EMPTY) {
      return;
    }
    if(row[bot2.botpos.rpos].col[bot2.botpos.cpos].state == GAINPOINTS) {
      bot2.points++;
      return;
    }
    if(row[bot2.botpos.rpos].col[bot2.botpos.cpos].state == LOSEHEALTH) {
      bot1.health -= 10;
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
  if(winner == BOT1) {
    cout << "--------PLAYER 1 WINS-----------" << endl;
  }
  if(winner == BOT2) {
    cout << "--------PLAYER 2 WINS-----------" << endl;
  }

  if(winner == TIE) {
    cout << "--------TIE GAME-----------" << endl;
  }
  if(winner == EXIT) {
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
    turn();
    ++turncount;
    endchecker();
  }



  gameGrid.display();
  gameGrid.start();
	return 0;
	}
