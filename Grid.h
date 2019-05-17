#include "Bot.h"

using namespace std;
struct square{
    SquareState state;
};

class Grid {
public:

    void botupdate(bot bot, dir botd);
    void applysquare(bot abot);
    bool closecheck(coor, coor);
    void display();
    squarestate randoms();
    Grid(int);
    Bot player1;
    Bot player2;
private:
    square getBotSquare(Bot);
    int size;
    Grid[][] grid_form;
};

void Grid::Grid(int inputsize) {
    if (inputsize < 0 || inputsize == null) {
        throw illegal_argument();
    }
    this.size = inputsize;
    for (int row = 0; row < this.size; row++) {
        square* squareRow = new Square [this.size];
        for (int col = 0; col < this.size; col++) {
            squareRow[col].state = (rand() % 3) ? ((rand() % 2) ? GAINPOINTS : LOSEHEALTH) : EMPTY;
        }
        GridForm[row] = squareRow;
    }

    Player1 = new Bot(generateCoordinates());
    getBotSquare(Player1).state = BOT1SPOT;  //creates random spot for P1
    coor secondCoors = generateCoordinates();
    while(closeCheck(bot1.botpos, secondCoors)) {
        secondCoors = generateCoordinates();  //checks if P2 spot is too close to P1 and if so, try new spot
    }
    Player2 = new Bot(secondCoors);
    getBotSquare(Player2).state = BOT2SPOT;

}

void Grid::botupdate(bot bot, char dir) {   //updated the bot's position, and the game Grid
  if(bot.bottag == 1) {
    if(botd == UP) {
      if(Grid.Player1.botpos.rpos == 0) {
        return;
      }
      row[Grid.Player1.botpos.rpos].col[Grid.Player1.botpos.cpos].state = EMPTY;
      Grid.Player1.botpos.rpos--;
    }
    if(botd == DOWN) {
      if(Grid.Player1.botpos.rpos == bsize-1) {
        return;
      }
      row[Grid.Player1.botpos.rpos].col[Grid.Player1.botpos.cpos].state = EMPTY;
      Grid.Player1.botpos.rpos++;
    }
    if(botd == LEFT) {
      if(Grid.Player1.botpos.cpos == 0) {
        return;
      }
      row[Grid.Player1.botpos.rpos].col[Grid.Player1.botpos.cpos].state = EMPTY;
      Grid.Player1.botpos.cpos--;
    }
    if(botd == RIGHT) {
      if(Grid.Player1.botpos.cpos == bsize-1) {
        return;
      }
      row[Grid.Player1.botpos.rpos].col[Grid.Player1.botpos.cpos].state = EMPTY;
      Grid.Player1.botpos.cpos++;
    }
    if(botd == NONE) {
      return;
    }
    applysquare(Grid.Player1);

  }
  if(bot.bottag == 2) {
    if(botd == UP) {
      if(Grid.Player2.botpos.rpos == 0) {
        return;
      }
      row[Grid.Player2.botpos.rpos].col[Grid.Player2.botpos.cpos].state = EMPTY;
      Grid.Player2.botpos.rpos--;
    }
    if(botd == DOWN) {
      if(Grid.Player2.botpos.rpos == bsize-1) {
        return;
      }
      row[Grid.Player2.botpos.rpos].col[Grid.Player2.botpos.cpos].state = EMPTY;
      Grid.Player2.botpos.rpos++;
    }
    if(botd == LEFT) {
      if(Grid.Player2.botpos.cpos == 0) {
        return;
      }
      row[Grid.Player2.botpos.rpos].col[Grid.Player2.botpos.cpos].state = EMPTY;
      Grid.Player2.botpos.cpos--;
    }
    if(botd == RIGHT) {
      if(Grid.Player2.botpos.cpos == bsize-1) {
        return;
      }
      row[Grid.Player2.botpos.rpos].col[Grid.Player2.botpos.cpos].state = EMPTY;
      Grid.Player2.botpos.cpos++;
    }
    applysquare(Grid.Player2);


  }
}

void Grid::display() {   //displays the entire Grid
    cout << "PLAYER 1  HEALTH: " << bot1.health << "  POINTS: " << bot1.points <<  "      PLAYER 2  HEALTH: " << bot2.health << "  POINTS: " << bot2.points << endl;
    int colcount = 0;
	int rowcount = 0;

	while(rowcount < size) {
		while(colcount < size) {
			cout << "-----";
			++colcount;
		}
		cout << endl;
		colcount = 0;
		while(colcount < size) {
			if(colcount == size -1) {
				if(GridForm[rowcount][colcount].state == EMPTY) {
					cout << "|    |";
				}
        else if(GridForm[rowcount][colcount].state == BOT1SPOT) {
					cout << "|1  1|";
				}
        else if(GridForm[rowcount][colcount].state == BOT2SPOT) {
					cout << "|2  2|";
				}
        else{
					cout << "|xxxx|";
				}
			}
			else{
        if(GridForm[rowcount][colcount].state == EMPTY) {
          cout << "|    ";
        }
        else if(GridForm[rowcount][colcount].state == BOT1SPOT) {
          cout << "|1  1";
        }
        else if(GridForm[rowcount][colcount].state == BOT2SPOT) {
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
    while(colcount < size) {
			if(colcount == size -1) {
				if(GridForm[rowcount][colcount].state == EMPTY) {
					cout << "|    |";
				}
        else if(GridForm[rowcount][colcount].state == BOT1SPOT) {
					cout << "|1  1|";
				}
        else if(GridForm[rowcount][colcount].state == BOT2SPOT) {
					cout << "|2  2|";
				}
        else{
					cout << "|xxxx|";
				}
			}
			else{
        if(GridForm[rowcount][colcount].state == EMPTY) {
          cout << "|    ";
        }
        else if(GridForm[rowcount][colcount].state == BOT1SPOT) {
          cout << "|1  1";
        }
        else if(GridForm[rowcount][colcount].state == BOT2SPOT) {
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
	while(colcount < size) {
		cout << "-----";
		++colcount;
	}
  cout << endl;
}

coor generateCoordinates () {

    return coor newCoor = {rand() % this.size, rand() % this.size};

}

bool closeCheck(coor coor1, coor coor2){ //checkes to see that bots are at least 5 squares apart
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