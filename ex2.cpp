#include <iostream>
#include <ctime>
#include <cstdlib>
using namespace std;

int m, n, k;
int bomb; //the number of grids isn't opened
int choice1, choice2; // player's choice
int myMap[100][100]; //the computer's matrix
char mapShown[100][100]; //the matrix for the player
int validChoice[100][100]; //check whether a grid is opened or not
int visited[100][100];
int x0[3] = { -1, 0, 1 };
int y0[3] = { -1, 0, 1 };
void checkBeside(int, int);
void bombLocation();
void updateMyMap();
void enterChoice();
bool checkChoice(int, int);
void buildMapShown();
void updateResult(int, int);
void printMapShown();
void printResult();
void checkWinning();

int main() {
	cin >> m >> n >> k;
	cout << "Please .... Waiting for playing!!!" << "\n";
	bombLocation();
	buildMapShown();
	do {
		enterChoice();
		system("cls");
		updateResult(choice1, choice2);
	} while (checkChoice(choice1, choice2) == true && bomb != k);

	if (checkChoice(choice1, choice2)) cout << "\n" << "You win!!" << "\n";
	else cout << "\n" << "You're dead!!!" << "\n";
	printResult();
	return 0;
}

//Update the showing matrix after a player's choice
void updateResult(int x, int y) {
	bomb = 0;
	if (myMap[x][y] == -1) {
		mapShown[x][y] = '!';
	}
	else if (myMap[x][y] != 0) {
		mapShown[x][y] = char(myMap[x][y] + 48);
	}
	else {
		checkBeside(x, y);
	}
	checkWinning();
	printMapShown();
}

void printMapShown() {
	for (int i = 1; i <= m; i++) {
		for (int j = 1; j <= n; j++) {
			cout << mapShown[i][j] << " ";
		}
		cout << "\n";
	}
}

void buildMapShown() {
	for (int i = 1; i <= n; i++) {
		for (int j = 1; j <= n; j++) {
			mapShown[i][j] = '*';
		}
	}
	printMapShown();
}

//the player will enter to open a grid
void enterChoice() {
	cout << "\n" << "Entering a grid you want to open: " << "\n";
	do {
		cin >> choice1 >> choice2;
	} while (validChoice[choice1][choice2] != 0 || choice1<1 || choice1>m || choice2<1 || choice2>n);


	validChoice[choice1][choice2] = 1; //the grid is choosen so we can't choose it again
}

//does the grid contain a bomb ?
bool checkChoice(int x, int y) {
	if (myMap[x][y] == -1) {
		return false;
	}
	return true;
}

//the correct answer for the game
void printResult() {
	for (int i = 1; i <= n; i++) {
		for (int j = 1; j <= n; j++) {
			if (myMap[i][j] == -1) {
				mapShown[i][j] = '!';
			}
			else {
				mapShown[i][j] = char(myMap[i][j] + 48);
			}
		}
	}
	printMapShown();
}

//the number of grids isn't opened
void checkWinning() {
	for (int i = 1; i <= m; i++) {
		for (int j = 1; j <= n; j++) {
			if (mapShown[i][j] == '*') {
				bomb++;
			}
		}
	}
}

//check the grid with no bombs around
void checkBeside(int xx, int yy) {
	if (myMap[xx][yy] == 0 && visited[xx][yy] == 0 && xx >= 1 && xx <= m && yy >= 1 && yy <= n) {
		visited[xx][yy] = 1;
		mapShown[xx][yy] = '0';
		for (int t = 0; t < 3; t++) {
			for (int k = 0; k < 3; k++) {
				if (x0[t] != 0 || y0[k] != 0)
					checkBeside(xx + x0[t], yy + y0[k]);
			}
		}
	}
	else if (myMap[xx][yy] != -1 && xx >= 1 && xx <= m && yy >= 1 && yy <= n) {
		visited[xx][yy] = 1;
		mapShown[xx][yy] = char(myMap[xx][yy] + 48);
		return;
	}
	else visited[xx][yy] = 1;
}

//random bombs' location
void bombLocation() {
	int bombNum = 0;
	while (bombNum < k) {
		srand(time(0));
		int x1 = rand() % m + 1;
		int y1 = rand() % n + 1;
		if (myMap[x1][y1] != -1) {
			myMap[x1][y1] = -1;
			bombNum++;
		}
	}
	updateMyMap();
}

//the matrix after having bombs
void updateMyMap() {
	int count;
	for (int i = 1; i <= m; i++) {
		for (int j = 1; j <= n; j++) {
			count = 0;
			if (myMap[i][j] != -1) {
				for (int t = 0; t < 3; t++) {
					for (int k = 0; k < 3; k++) {
						if (myMap[i + x0[t]][j + y0[k]] == -1) {
							count++;
						}
					}
				}
				myMap[i][j] = count;
			}
		}
	}
}
