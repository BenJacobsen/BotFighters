#include "Bot.h"

enum SquareState { BOT1SPOT, BOT2SPOT, GAINPOINTS, LOSEHEALTH, EMPTY };
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
  Bot[] endChecker();
  squarestate randoms();
  Grid(int);
private:
    square getBotSquare(Bot);
    int size;
    Grid[][] GridForm;
    Bot player1;
    Bot player2;
};

void Grid::Grid(int inputsize) {
    if (inputsize < 0 || inputsize == null) {
        throw illegal_argument();
    }
    this.size = inputsize;
    for (int row = 0; row < this.size; row++) {
        square* squareRow = new Square [this.size];
        for (int col = 0; col < this.size; col++) {
            squareRow[col].state = (rand() % 3) ? generateState() : EMPTY;
        }
        GridForm[row] = squareRow;
    }

    player1 = new Bot(generateCoordinates());
    getBotSquare(player1).state = BOT1SPOT;  //creates random spot for P1
    coor secondCoors = generateCoordinates();
    while(closeCheck(bot1.botpos, secondCoors)) {
        secondCoors = generateCoordinates();  //checks if P2 spot is too close to P1 and if so, try new spot
    }
    player2 = new Bot(secondCoors);
    getBotSquare(player2).state = BOT2SPOT;

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

SquareState generateState () {  //random creates a square type for mystery bonus
  int x = rand() % 2;
  if(x == 0){
    return GAINPOINTS;
  }
  if(x == 1){
    return LOSEHEALTH;
  }
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