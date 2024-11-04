#include <iostream>
#include <vector>

using namespace std;

const char PLAYER = 'X';
const char COMPUTER = 'O';
const char EMPTY = ' ';

void printBoard(const vector<char>& board) {
    for (int i = 0; i < 9; ++i) {
        if (board[i] == EMPTY) {
            cout << " " << i;
        } else {
            cout << " " << board[i];
        }

        if (i % 3 < 2) {
            cout << " |";
        } else {
            cout << " \n";
            if (i < 6) {
                cout << "---|---|---\n";
            }
        }
    }
}

bool isWinner(const vector<char>& board, char player) {
    int winCombinations[8][3] = {
        {0, 1, 2}, {3, 4, 5}, {6, 7, 8}, // rows
        {0, 3, 6}, {1, 4, 7}, {2, 5, 8}, // columns
        {0, 4, 8}, {2, 4, 6}             // diagonals
    };
    for (int i = 0; i < 8; ++i) {
        if (board[winCombinations[i][0]] == player &&
            board[winCombinations[i][1]] == player &&
            board[winCombinations[i][2]] == player) {
            return true;
        }
    }
    return false;
}

bool isBoardFull(const vector<char>& board) {
    for (int i = 0; i < board.size(); ++i) {
        if (board[i] == EMPTY) {
            return false;
        }
    }
    return true;
}

int minimax(vector<char>& board, bool isMaximizing) {
    if (isWinner(board, COMPUTER)) return 1;
    if (isWinner(board, PLAYER)) return -1;
    if (isBoardFull(board)) return 0;

    if (isMaximizing) {
        int bestScore = -1000;
        for (int i = 0; i < 9; ++i) {
            if (board[i] == EMPTY) {
                board[i] = COMPUTER;
                int score = minimax(board, false);
                board[i] = EMPTY;
                if (score > bestScore) {
                    bestScore = score;
                }
            }
        }
        return bestScore;
    } else {
        int bestScore = 1000;
        for (int i = 0; i < 9; ++i) {
            if (board[i] == EMPTY) {
                board[i] = PLAYER;
                int score = minimax(board, true);
                board[i] = EMPTY;
                if (score < bestScore) {
                    bestScore = score;
                }
            }
        }
        return bestScore;
    }
}

int findBestMove(vector<char>& board) {
    int bestMove = -1;
    int bestScore = -1000;
    for (int i = 0; i < 9; ++i) {
        if (board[i] == EMPTY) {
            board[i] = COMPUTER;
            int score = minimax(board, false);
            board[i] = EMPTY;
            if (score > bestScore) {
                bestScore = score;
                bestMove = i;
            }
        }
    }
    return bestMove;
}

void playerMove(vector<char>& board) {
    int move;
    while (true) {
        cout << "\nEnter your move (0-8): ";
        cin >> move;
        if (move >= 0 && move < 9 && board[move] == EMPTY) {
            board[move] = PLAYER;
            break;
        } else {
            cout << "\nInvalid move. Try again.\n";
        }
    }
}

int main() {
    vector<char> board(9, EMPTY);
    cout << "Tic-Tac-Toe Game\n";
    printBoard(board);

    while (true) {
        playerMove(board);
        
        printBoard(board);
        if (isWinner(board, PLAYER)) {
            cout << "\nYou win!\n";
            break;
        }
        if (isBoardFull(board)) {
            cout << "\nIt's a draw!\n";
            break;
        }
cout<<"\n";
        int bestMove = findBestMove(board);
        board[bestMove] = COMPUTER;
        printBoard(board);
        if (isWinner(board, COMPUTER)) {
            cout << "\nComputer wins!\n";
            break;
        }
        if (isBoardFull(board)) {
            cout << "\nIt's a draw!\n";
            break;
        }
    }

    return 0;
}

