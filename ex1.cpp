#include<bits/stdc++.h>

using namespace std;

const int MAX_SIZE = 100; 
const int MAX_MINES = 100; 

int board[MAX_SIZE][MAX_SIZE]; 
bool revealed[MAX_SIZE][MAX_SIZE]; 
int m, n, K; 

void generateMines() {
    int count = 0; 
    while (count < K) {
        int x = rand() % m;
        int y = rand() % n;
        if (board[x][y] != -1) {
            board[x][y] = -1;
            count++;
        }
    }
}

// Print the map
void printBoard(int rows, int cols) {
    cout << "  ";
    for (int i = 0; i < n; i++) cout << i << " ";
    cout << endl;
    for (int i = 0; i < m; i++) {
        cout << i << " ";
        for (int j = 0; j < n; j++) {
            if (revealed[i][j]) {
                if (board[i][j] == -1) {
                    cout << "* ";
                }
                else {
                    cout << board[i][j] << " ";
                }
            }
            else {
                cout << ". ";
            }
        }
        cout << endl;
    }
}

//Find the bombs
int countMines(int x, int y) {
    int count = 0;
    for (int i = -1; i <= 1; i++) {
        for (int j = -1; j <= 1; j++) {
            if (i == 0 && j == 0) {
                continue;
            }
            int row = x + i;
            int col = y + j;
            if (row >= 0 && row < m && col >= 0 && col < n && board[row][col] == -1) {
                count++;
            }
        }
    }
    return count;
}

int main() {
    srand(time(NULL));

    // Board size and bomb's amount
    cout << "Nhap kich thuoc bang(m, n) va so luong min: ";
    cin >> m >> n >> K;

    for (int i = 0; i < m; i++) {
        for (int j = 0; j < n; j++) {
            board[i][j] = 0;
            revealed[i][j] = false;
        }
    }

    generateMines();

    bool gameOver = false;
    while (!gameOver) {
        printBoard(m, n);

        int x, y;
        cout << "Enter the coordinators: ";
        cin >> x >> y;

        if (x < 0 || x >= m || y < 0 || y >= n) {
            cout << "Coordinators unavailable. Try again" << endl;
            continue;
        }

        if (revealed[x][y]) {
            cout << "Open the chosen coordinators. Continue" << endl;
            continue;
        }

        revealed[x][y] = true;
        if (board[x][y] == -1) {
            cout << "BOOMMMMMMMMMMMM!" << endl;
            printBoard(m, n);
            gameOver = true;
        }
        else {
            
            int count = countMines(x, y);
            board[x][y] = count;

            int countUnrevealed = 0;
            for (int i = 0; i < m; i++) {
                for (int j = 0; j < n; j++) {
                    if (!revealed[i][j]) {
                        countUnrevealed++;
                    }
                }
            }
            if (countUnrevealed == K) {
                cout << "Congratulations! You won" << endl;
                printBoard(m, n);
                gameOver = true;
            }
        }
    }

    return 0;
}
