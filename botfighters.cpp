#include <iostream>
#include <stdlib.h>
#include <math.h>
using namespace std;
enum squarestate { BOT1SPOT, BOT2SPOT, GAINPOINTS, LOSEHEALTH, EMPTY };
enum results { BOT1, BOT2, TIE, EXIT };
enum dir { UP, DOWN, LEFT, RIGHT, NONE };

struct coor{
  int rpos;
  int cpos;
};
struct bot{
  int health;
  int points;
  coor botpos;
  int bottag;
};
struct square{
  squarestate state;
};
struct boardrow{
  square* col;
};
class board{
public:
  void botupdate(bot bot, dir botd);
  void applysquare(bot abot);
  dir getkey();
  bool closecheck(coor coor1, coor coor2);
  void display();
  void turn();
  void start();
  void endcheck();
  squarestate randoms();
  void generateboard(int inputsize);
  board();
private:
  int bsize;
  boardrow* row;
  bot bot1;
  bot bot2;
  results winner;
  int turncount;
  bool exiter;
  bool ended;
};
dir board::getkey(){  //translates keys to moves
  char x;
  cin >> x;
  if(x == 'w'){
    return UP;
  }
  if(x == 'a'){
    return LEFT;
  }
  if(x == 's'){
    return DOWN;
  }
  if(x == 'd'){
    return RIGHT;
  }
  if(x == 'x'){
    exiter = true;
    return NONE;
  }
  if(x == 'z'){
    return NONE;
  }
  cout << "Enter one of the wasd keys" << endl;
  getkey();
}
void board::display(){   //displays the entire board
  cout << "BOT 1  HEALTH: " << bot1.health << "  POINTS: " << bot1.points <<  "      BOT 2  HEALTH: " << bot2.health << "  POINTS: " << bot2.points << endl;
  int colcount = 0;
	int rowcount = 0;

	while(rowcount < bsize){
		while(colcount < bsize){
			cout << "-----";
			++colcount;
		}
		cout << endl;
		colcount = 0;
		while(colcount < bsize){
			if(colcount == bsize -1){
				if(row[rowcount].col[colcount].state == EMPTY){
					cout << "|    |";
				}
        else if(row[rowcount].col[colcount].state == BOT1SPOT){
					cout << "|1  1|";
				}
        else if(row[rowcount].col[colcount].state == BOT2SPOT){
					cout << "|2  2|";
				}
        else{
					cout << "|xxxx|";
				}
			}
			else{
        if(row[rowcount].col[colcount].state == EMPTY){
          cout << "|    ";
        }
        else if(row[rowcount].col[colcount].state == BOT1SPOT){
          cout << "|1  1";
        }
        else if(row[rowcount].col[colcount].state == BOT2SPOT){
          cout << "|2  2";
        }
        else{
          cout << "|xxxx";
        }
			}
			++colcount;
		}
		colcount = 0;
		cout << endl;
    while(colcount < bsize){
			if(colcount == bsize -1){
				if(row[rowcount].col[colcount].state == EMPTY){
					cout << "|    |";
				}
        else if(row[rowcount].col[colcount].state == BOT1SPOT){
					cout << "|1  1|";
				}
        else if(row[rowcount].col[colcount].state == BOT2SPOT){
					cout << "|2  2|";
				}
        else{
					cout << "|xxxx|";
				}
			}
			else{
        if(row[rowcount].col[colcount].state == EMPTY){
          cout << "|    ";
        }
        else if(row[rowcount].col[colcount].state == BOT1SPOT){
          cout << "|1  1";
        }
        else if(row[rowcount].col[colcount].state == BOT2SPOT){
          cout << "|2  2";
        }
        else{
          cout << "|xxxx";
        }
			}
			++colcount;
		}
		colcount = 0;
		cout << endl;
		++rowcount;
	}
	colcount = 0;
	while(colcount < bsize){
		cout << "-----";
		++colcount;
	}
  cout << endl;
}
void board::turn(){
  dir bot1d;
  dir bot2d;
  cout << "PLAYER 1's MOVE:" << endl;   //gets keys for bot's move
  bot1d = getkey();
  cout << "PLAYER 2's MOVE:" << endl;
  bot2d = getkey();

  botupdate(bot1, bot1d);   //update the postions of the bots
  botupdate(bot2, bot2d);
  row[bot1.botpos.rpos].col[bot1.botpos.cpos].state = BOT1SPOT;
  if(row[bot2.botpos.rpos].col[bot2.botpos.cpos].state = BOT1SPOT){
    endcheck();
  }
  else{
    row[bot2.botpos.rpos].col[bot2.botpos.cpos].state = BOT2SPOT;
  }
  display();
}
void board::endcheck(){   //checks conditions to see if game is over, and if so, who won
  if(exiter == true){
    winner = EXIT;
    ended = true;
    return;
  }
  if(bot1.health == 0){
    winner = BOT2;
    ended = true;
    return;
  }
  if(bot2.health == 0){
    winner = BOT1;
    ended = true;
    return;
  }
  if(turncount == 60 || (bot1.botpos.rpos == bot2.botpos.rpos && bot1.botpos.cpos == bot2.botpos.cpos)){
    if(bot1.points > bot2.points){
      winner = BOT1;
      ended = true;
      return;
    }
    if(bot2.points > bot1.points){
      winner = BOT2;
      ended = true;
      return;
    }
    if(bot1.points == bot2.points){
      winner = TIE;
      ended = true;
      return;
    }
  }
  return;
}
bool board::closecheck(coor coor1, coor coor2){ //checkes to see that bots are at least 5 squares apart
  int rowdif = coor1.rpos - coor2.rpos;
  if(rowdif < 0){
    rowdif = rowdif * (-1);
  }
  int coldif = coor1.cpos - coor2.cpos;
  if(coldif < 0){
    coldif = coldif * (-1);
  }
  int dist = coldif + rowdif;
  if(dist > 4){
    return false;
  }
  return true;
}
void board::botupdate(bot bot, dir botd){   //updated the bot's position, and the game board
  if(bot.bottag == 1){
    if(botd == UP){
      if(bot1.botpos.rpos == 0){
        return;
      }
      row[bot1.botpos.rpos].col[bot1.botpos.cpos].state = EMPTY;
      bot1.botpos.rpos--;
    }
    if(botd == DOWN){
      if(bot1.botpos.rpos == bsize-1){
        return;
      }
      row[bot1.botpos.rpos].col[bot1.botpos.cpos].state = EMPTY;
      bot1.botpos.rpos++;
    }
    if(botd == LEFT){
      if(bot1.botpos.cpos == 0){
        return;
      }
      row[bot1.botpos.rpos].col[bot1.botpos.cpos].state = EMPTY;
      bot1.botpos.cpos--;
    }
    if(botd == RIGHT){
      if(bot1.botpos.cpos == bsize-1){
        return;
      }
      row[bot1.botpos.rpos].col[bot1.botpos.cpos].state = EMPTY;
      bot1.botpos.cpos++;
    }
    if(botd == NONE){
      return;
    }
    applysquare(bot1);

  }
  if(bot.bottag == 2){
    if(botd == UP){
      if(bot2.botpos.rpos == 0){
        return;
      }
      row[bot2.botpos.rpos].col[bot2.botpos.cpos].state = EMPTY;
      bot2.botpos.rpos--;
    }
    if(botd == DOWN){
      if(bot2.botpos.rpos == bsize-1){
        return;
      }
      row[bot2.botpos.rpos].col[bot2.botpos.cpos].state = EMPTY;
      bot2.botpos.rpos++;
    }
    if(botd == LEFT){
      if(bot2.botpos.cpos == 0){
        return;
      }
      row[bot2.botpos.rpos].col[bot2.botpos.cpos].state = EMPTY;
      bot2.botpos.cpos--;
    }
    if(botd == RIGHT){
      if(bot2.botpos.cpos == bsize-1){
        return;
      }
      row[bot2.botpos.rpos].col[bot2.botpos.cpos].state = EMPTY;
      bot2.botpos.cpos++;
    }
    applysquare(bot2);


  }
}
void board::applysquare(bot abot){    //applies changes to points and health of bots based on square
  if(abot.bottag == 1){
    if(row[bot1.botpos.rpos].col[bot1.botpos.cpos].state == EMPTY){
      return;
    }

    if(row[bot1.botpos.rpos].col[bot1.botpos.cpos].state == GAINPOINTS){
      bot1.points++;
      return;
    }
    if(row[bot1.botpos.rpos].col[bot1.botpos.cpos].state == LOSEHEALTH){
      bot2.health -= 10;
      return;
    }
  }
  if(abot.bottag == 2){
    if(row[bot2.botpos.rpos].col[bot2.botpos.cpos].state == EMPTY){
      return;
    }
    if(row[bot2.botpos.rpos].col[bot2.botpos.cpos].state == GAINPOINTS){
      bot2.points++;
      return;
    }
    if(row[bot2.botpos.rpos].col[bot2.botpos.cpos].state == LOSEHEALTH){
      bot1.health -= 10;
      return;
    }
  }

}
squarestate board::randoms(){  //random creates a square type for mystery bonus
  int x = rand() % 2;
  if(x == 0){
    return GAINPOINTS;
  }
  if(x == 1){
    return LOSEHEALTH;
  }
}
void board::generateboard(int inputsize){
  bsize = inputsize;
  ended = false;
  exiter = false;
  int rowcount = 0;
  int colcount = 0;
  bot1.health = 50;
  bot2.health = 50;
  bot1.points = 0;
  bot2.points = 0;
  bot1.bottag = 1;
  bot2.bottag = 2;
  row = new boardrow [bsize];      //create all squares empty
  while(rowcount < bsize){
    row[rowcount].col = new square [bsize];
    while(colcount < bsize){
      row[rowcount].col[colcount].state = EMPTY;
      int third = rand() % 3; //one third chance of square having random power-up
      if(third == 0){
        row[rowcount].col[colcount].state = randoms();
      }
      ++colcount;
    }
    colcount = 0;
    ++rowcount;
  }
  rowcount = 0;

  bot1.botpos.rpos =  rand() % bsize;
  bot1.botpos.cpos =  rand() % bsize;
  row[bot1.botpos.rpos].col[bot1.botpos.cpos].state = BOT1SPOT;  //creates random spot for P1
  bot2.botpos.rpos =  rand() % bsize;
  bot2.botpos.cpos =  rand() % bsize;
  while(closecheck(bot1.botpos, bot2.botpos)){
    bot2.botpos.rpos =  rand() % bsize;
    bot2.botpos.cpos =  rand() % bsize;  //checks if P2 spot is too close to P1 and if so, try new spot
  }
  row[bot2.botpos.rpos].col[bot2.botpos.cpos].state = BOT2SPOT;

}
board::board(){
  row = NULL;  //contructor for board
}
void board::start(){

  turncount = 0;

  while(!ended){ //checks if game ends and if not, do another turn
    turn();
    ++turncount;
    endcheck();
  }
  if(winner == BOT1){
    cout << "--------PLAYER 1 WINS-----------" << endl;
  }
  if(winner == BOT2){
    cout << "--------PLAYER 2 WINS-----------" << endl;
  }
  if(winner == TIE){
    cout << "--------TIE GAME-----------" << endl;
  }
  if(winner == EXIT){
    cout << "GAME ABANDONED" << endl;
  }
}
int main(const int argc, const char* const argv[]){
	srand (time(NULL));
  int size = -1;
  if(argv[1] != NULL){
    size = atoi(argv[1]);
  }


  while(size > 30 || size < 10){
    cout << "Please enter a value for the size of the gameboard between 10 and 30" << endl;
    cin >> size;
  }


  board gameboard;
  gameboard.generateboard(size);
  gameboard.display();
  gameboard.start();
	return 0;
	}
