#include<stdio.h>
#include<string.h>
#include<algorithm>

using namespace std;


/**
    *function to display the broad game
    *char board[5][5]: the board game
*/
void Ve_Bang(char board[5][5]) {
    for(int i = 0; i < 4; i++) {
        for(int j = 0; j < 4; j++) {
            printf("%c ", board[i][j]);
        }
        printf("\n");
    }
}
/**
    *function to check the board have any empty cell
    *char board[5][5]: the board game
*/
bool isMovesLeft(char board[5][5])
{
    for (int i = 1; i<4; i++)
        for (int j = 1; j<4; j++)
            if (board[i][j]=='*')
                return true;
    return false;
}
/**
    *function to caculate score after X or O move
    *char board[5][5]: the board game
*/
int check_win_lose_tie(char board[5][5]) {
    for(int i = 1; i < 4; i++) {
        if(board[i][1] == board[i][2] && board[i][2] == board[i][3]) {
            if(board[i][1] == 'X'&&board[i][2] == 'X' && board[i][3] == 'X') return 11;
            else if(board[i][1] == 'O'&&board[i][2] == 'O' && board[i][3] == 'O') return -11;
        }
    }
    for(int i = 1; i < 4; i++) {
        if(board[1][i] == board[2][i] && board[2][i] == board[3][i]) {
            if(board[1][i] == 'X'&&board[2][i] == 'X'&&board[3][i] == 'X') return 11;
            else if(board[1][i] == 'O'&&board[2][i] == 'O'&&board[3][i] == 'O') return -11;
        }
    }

    if(board[1][1] == board[2][2] && board[2][2] == board[3][3]) {
        if(board[1][1] == 'X'&&board[2][2] == 'X'&&board[3][3] == 'X') return 11;
            else if(board[1][1] == 'O'&&board[2][2] == 'O'&&board[3][3] == 'O') return -11;
    }

    if(board[1][3] == board[2][2] && board[2][2] == board[3][1]) {
        if(board[1][3] == 'X'&&board[2][2] == 'X'&&board[3][1] == 'X') return 11;
            else if(board[1][3] == 'O'&&board[2][2] == 'O'&&board[3][1] == 'O') return -11;
    }

    return 0;
}
/**
    *controll player move
*/
void player(char board[5][5], char p) {
    int x, y;
    printf("\n Nhap toa do x, y : "); scanf("%d%d", &x, &y);
    printf("\n");
    if(board[y][x] == '*')
    board[y][x] = p;
    else{
        printf("\n Nhap toa do x, y : "); scanf("%d%d", &x, &y);
        printf("\n");
    }
}
/**
    *implement minimax algorithm
*/
int minimax(char board[5][5], char turn, int depth) {
    int diem = check_win_lose_tie(board);
    if(diem == 11) return diem-depth;
    else if(diem == -11) return diem+depth;
    if(!isMovesLeft(board)) return 0;
    if(turn == 'X') {
        diem = -20;
        for(int i = 1; i < 4; i++) {
            for(int j = 1; j < 4; j++) {
                if(board[i][j] == '*') {
                    board[i][j] = 'X';
                    diem = max(diem, minimax(board,'O', depth+1));
                    board[i][j] = '*';

                }
            }
        }
        return diem;
    }
    else if(turn == 'O') {
        diem = 20;
        for(int i = 1; i < 4; i++) {
            for(int j = 1; j < 4; j++) {
                if(board[i][j] == '*') {
                    board[i][j] = 'O';
                    diem = min(diem, minimax(board,'X', depth+1));
                    board[i][j] = '*';

                }
            }
        }
        return diem;
    }
}
/**
    *controll computer move
*/
void computer(char board[5][5], int depth, char c) {
    if(c == 'X') {
        int x, y;
        int diem = -20;
        for(int i = 1; i < 4; i++) {
            for(int j = 1; j < 4; j++) {
                if(board[i][j] == '*') {
                        board[i][j] = 'X';
                        int d = minimax(board, 'O', depth+1);
                        board[i][j] = '*';
                        if(d > diem) {
                            diem = d;
                            y = i;
                            x = j;
                        }
                }
            }
        }
        board[y][x] = 'X';
   // printf("%d %d %d", x, y, diem);
    } else if(c == 'O') {
        int x, y;
        int diem = 20;
        for(int i = 1; i < 4; i++) {
            for(int j = 1; j < 4; j++) {
                if(board[i][j] == '*') {
                        board[i][j] = 'O';
                        int d = minimax(board, 'X', depth+1);
                        board[i][j] = '*';
                        if(d < diem) {
                            diem = d;
                            y = i;
                            x = j;
                        }
                }
            }
        }
        board[y][x] = 'O';
    }
}

int main() {
    char board[5][5] = {" 123",
                        "1***",
                        "2***",
                        "3***"};
    //printf("%d ", minimax(board, 'X', 0));
    //computer(board, 0);
    int k;
    char p, c;
    printf("chon X hoac O\n");
    printf("1. X\n");
    printf("2. O\n");
    printf("Nhap so: "); scanf("%d", &k);
    if(k == 1) {
        p = 'X';
        c = 'O';
        Ve_Bang(board);
        printf("Bat dau tro choi, player di truoc\n");

    } else {
        p = 'O';
        c = 'X';
        Ve_Bang(board);
        printf("Bat dau tro choi, computer di truoc\n");
    }
    for(int i = 0; i < 9; i++) {
        if(i%2 == 0) {
            if(k == 1) {
                player(board, p);
            } else {
                computer(board, 0, c);
           }
        } else {
            if(k == 1) {
                computer(board, 0, c);
                Ve_Bang(board);
            } else {
                Ve_Bang(board);
               player(board, p);
           }
        }
        if(check_win_lose_tie(board) > 0) {
            Ve_Bang(board);
            printf("\nX thang");
            return 0;
        } else if(check_win_lose_tie(board) < 0) {
            Ve_Bang(board);
            printf("/nO thang");
            return 0;
        }
    }
    Ve_Bang(board);
    printf("\nHoa");
    return 0;

}
