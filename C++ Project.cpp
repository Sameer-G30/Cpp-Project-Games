#include <iostream>
#include <ctime>
#include <cstdlib>
#include <string>
#include <cctype>
#include <windows.h>
#include <conio.h> 
using namespace std;

const int width = 80;
const int height = 20;


class SnakeGame {
private:
    int x, y; 
    int fruitCordX, fruitCordY; 
    int playerScore;
    int snakeTailX[100], snakeTailY[100];
    int snakeTailLen;
    enum snakesDirection { STOP = 0, LEFT, RIGHT, UP, DOWN };
    snakesDirection sDir;
    bool isGameOver;

public:
    SnakeGame() {
        x = width / 2;
        y = height / 2;
        fruitCordX = rand() % width;
        fruitCordY = rand() % height;
        playerScore = 0;
        snakeTailLen = 0;
        sDir = STOP;
        isGameOver = false;
    }

    void userInput() {
        if (_kbhit()) {
            switch (_getch()) {
            case 'a':
                sDir = LEFT;
                break;
            case 'd':
                sDir = RIGHT;
                break;
            case 'w':
                sDir = UP;
                break;
            case 's':
                sDir = DOWN;
                break;
            case 'x':
                isGameOver = true;
                break;
            }
        }
    }

    void updateGame() {
        int prevX = snakeTailX[0]; 
        int prevY = snakeTailY[0]; 
        int prev2X, prev2Y; 
        snakeTailX[0] = x; 
        snakeTailY[0] = y; 

        for (int i = 1; i < snakeTailLen; i++) { 
            prev2X = snakeTailX[i]; 
            prev2Y = snakeTailY[i]; 
            snakeTailX[i] = prevX; 
            snakeTailY[i] = prevY; 
            prevX = prev2X; 
            prevY = prev2Y; 
        } 

        switch (sDir) { 
        case LEFT: 
            x--; 
            break; 
        case RIGHT: 
            x++; 
            break; 
        case UP: 
            y--; 
            break; 
        case DOWN: 
            y++; 
            break; 
        } 

        if (x >= width || x < 0 || y >= height || y < 0) 
            isGameOver = true; 

        for (int i = 0; i < snakeTailLen; i++) { 
            if (snakeTailX[i] == x && snakeTailY[i] == y) 
                isGameOver = true; 
        } 

        if (x == fruitCordX && y == fruitCordY) { 
            playerScore += 10; 
            fruitCordX = rand() % width; 
            fruitCordY = rand() % height; 
            snakeTailLen++; 
        } 
    }

    void gameRender(string playerName) {
        cout << "\x1b[2J\x1b[H"; // Clear the console

        for (int i = 0; i < width + 2; i++) 
            cout << "-"; 
        cout << endl; 

        for (int i = 0; i < height; i++) { 
            for (int j = 0; j <= width; j++) { 
                if (j == 0 || j == width) 
                    cout << "|"; 
                if (i == y && j == x) 
                    cout << "O"; 
                else if (i == fruitCordY && j == fruitCordX) 
                    cout << "#"; 
                else { 
                    bool prTail = false; 
                    for (int k = 0; k < snakeTailLen; k++) { 
                        if (snakeTailX[k] == j && snakeTailY[k] == i) { 
                            cout << "o"; 
                            prTail = true; 
                        } 
                    } 
                    if (!prTail) 
                        cout << " "; 
                } 
            } 
            cout << endl; 
        } 

        for (int i = 0; i < width + 2; i++) 
            cout << "-"; 
        cout << endl; 

        cout << playerName << "'s Score: " << playerScore << endl; 
    }

    void gameInit() {
        isGameOver = false; 
        sDir = STOP; 
        x = width / 2; 
        y = height / 2; 
        fruitCordX = rand() % width; 
        fruitCordY = rand() % height; 
        playerScore = 0; 
    }

    bool gameOver() {
        return isGameOver;
    }

    int setDifficulty() {
        int dfc, choice; 
        cout << "\nSET DIFFICULTY\n1: Easy\n2: Medium\n3: hard\nDefault difficulty:Medium\nChoose difficulty level: "; 
        cin >> choice; 
        switch (choice) { 
        case 1: 
            dfc = 50; 
            break; 
        case 2: 
            dfc = 100; 
            break; 
        case 3: 
            dfc = 150; 
            break; 
        default: 
            dfc = 100; 
            break;
        } 
        return dfc; 
    }
};

// Hand Cricket game functions
class Human {
public:
    int runs;
};

class Bot {
public:
    int runs;
};

int botbat(int wick, int over);
int botbowl(int wick, int over);



//TIC TAC TOE FUNCTIONS
int won = 0; // Winning condition

class Move {
public:
    int x;
    int y;
};

char computer = 'X';
char user = 'O';

void rules() {
    cout << "TIC TAC TOE\n";
    cout << "MULTIPLAYER GAME\n";
    cout << "Rules are simple, 3 X's or O's in a row (vertical, horizontal and diagonal)\nEG: X wins belows\n";
    cout << "X\tO\tO\nX\tX\tX\nO\tO\tX\n";
}

void board_initialization(char board[3][3]) {
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            board[i][j] = '_';
        }
    }
}

void check_board(char board[3][3]) {
    int i = 0, j = 0;

    char move[2] = {'X', 'O'};

    for (int cntr = 0; cntr < 2; cntr++) {
        if (((board[i][j] == move[cntr]) && (board[i][j + 1] == move[cntr]) && (board[i][j + 2] == move[cntr])) ||
            ((board[i][j] == move[cntr]) && (board[i + 1][j] == move[cntr]) && (board[i + 2][j] == move[cntr])) ||
            ((board[i][j] == move[cntr]) && (board[i + 1][j + 1] == move[cntr]) && (board[i + 2][j + 2] == move[cntr])) ||
            ((board[i][j + 2] == move[cntr]) && (board[i + 1][j + 1] == move[cntr]) && (board[i + 2][j] == move[cntr])) ||
            ((board[i][j + 2] == move[cntr]) && (board[i + 1][j + 2] == move[cntr]) && (board[i + 2][j + 2] == move[cntr])) ||
            ((board[i][j + 1] == move[cntr]) && (board[i + 1][j + 1] == move[cntr]) && (board[i + 2][j + 1] == move[cntr])) ||
            ((board[i + 1][j] == move[cntr]) && (board[i + 1][j + 1] == move[cntr]) && (board[i + 1][j + 2] == move[cntr])) ||
            ((board[i + 2][j] == move[cntr]) && (board[i + 2][j + 1] == move[cntr]) && (board[i + 2][j + 2] == move[cntr]))) {
            cout << "\n" << move[cntr] << " WON\nCONGRATS " << move[cntr] << "\n";
            won++;
            break;
        }
    }
}

bool is_valid(int move_x, int move_y, char board[3][3]) {
    if (move_x > 2 || move_x < 0 || move_y > 2 || move_y < 0)
        return false;
    if (board[move_x][move_y] == 'O' || board[move_x][move_y] == 'X')
        return false;
    return true;
}

void print_board(char board[3][3]) {
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            cout << board[i][j] << "\t";
        }
        cout << endl;
    }
}

bool move_verification(char board[3][3]) {
    for (int i = 0; i < 3; i++)
        for (int j = 0; j < 3; j++)
            if (board[i][j] == '_')
                return true;
    return false;
}

int evaluation(char board[3][3]) {
    for (int row = 0; row < 3; row++) {
        if (board[row][0] == board[row][1] && board[row][1] == board[row][2]) {
            if (board[row][0] == computer)
                return +10;
            else if (board[row][0] == user)
                return -10;
        }
    }
    for (int col = 0; col < 3; col++) {
        if (board[0][col] == board[1][col] && board[1][col] == board[2][col]) {
            if (board[0][col] == computer)
                return +10;
            else if (board[0][col] == user)
                return -10;
        }
    }
    if (board[0][0] == board[1][1] && board[1][1] == board[2][2]) {
        if (board[0][0] == computer)
            return +10;
        else if (board[0][0] == user)
            return -10;
    }
    if (board[0][2] == board[1][1] && board[1][1] == board[2][0]) {
        if (board[0][2] == computer)
            return +10;
        else if (board[0][2] == user)
            return -10;
    }
    return 0;
}

int minimax(char board[3][3], int depth, int isMax) {
    int score = evaluation(board);
    if (score == 10)
        return score;
    if (score == -10)
        return score;
    if (move_verification(board) == false)
        return 0;
    if (isMax == 1) {
        int best = -1000;
        for (int i = 0; i < 3; i++) {
            for (int j = 0; j < 3; j++) {
                if (board[i][j] == '_') {
                    board[i][j] = computer;
                    best = max(best, minimax(board, depth + 1, 0));
                    board[i][j] = '_';
                }
            }
        }
        return best;
    } else {
        int best = 1000;
        for (int i = 0; i < 3; i++) {
            for (int j = 0; j < 3; j++) {
                if (board[i][j] == '_') {
                    board[i][j] = user;
                    best = min(best, minimax(board, depth + 1, 1));
                    board[i][j] = '_';
                }
            }
        }
        return best;
    }
}

void computer_plays(char board[3][3]) {
    Move play;
    play.x = -1;
    play.y = -1;
    int best_val = -1000;
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            if (board[i][j] == '_') {
                board[i][j] = computer;
                int move_val = minimax(board, 0, 0);
                board[i][j] = '_';
                if (move_val > best_val) {
                    best_val = move_val;
                    play.x = i;
                    play.y = j;
                }
            }
        }
    }
    board[play.x][play.y] = computer;
}

void user_plays(char board[3][3]) {
    Move play;
    play.x = -1;
    play.y = -1;
    cout << "\nEnter the x and y co-ordinate of your move rows-(1-3) col-(1-3) : ";
    cin >> play.x >> play.y;
    play.x--;
    play.y--;
    if (is_valid(play.x, play.y, board) == true)
        board[play.x][play.y] = user;
    else {
        cout << "Not A Valid Move!\n";
        user_plays(board);
    }
}

void computer_move(char board[3][3]) {
    cout << "\nComputer is playing it's move ...\n";
    computer_plays(board);
    check_board(board);
    print_board(board);
}

void user_move(char board[3][3]) {
    user_plays(board);
    check_board(board);
    print_board(board);
}

int toss1() {
    cout << "Time for the toss: \n";
    srand(time(NULL));
    int toss1 = rand() % 2;
    if (toss1 == 0)
        cout << "User wins the toss ! Finish him!\n";
    else if (toss1 == 1)
        cout << "Computer wins the toss ! Let me begin by annihilating you!\n";
    return toss1;
}

void gameplay(char board[3][3], int toss) {
    while (won != 1 && move_verification(board) == true) {
        if (toss == 0) {
            user_move(board);
            if (won == 1)
                break;
            toss = 1;
            continue;
        } else if (toss == 1) {
            computer_move(board);
            if (won == 1)
                break;
            toss = 0;
        }
    }
    if (move_verification(board) == false) {
        cout << "It's a draw !\n";
    }
}


int main()
{
    int choice;
    string playerName;
    int dfc;
    int userrun, botrun, wick, over;
    string playerGuess;
    string playerChoice;
    int tossResult, botChoice;
    string toss;
    string botDecision;
    SnakeGame snakeGame;

    do {    
    cout << "Which game do you want to play?" << endl;
    cout << "1. Hand Cricket" << endl;
    cout << "2. Snake Game" << endl;
    cout << "3. Tic-Tac-Toe" << endl;
    cout << "4. Quit" << endl;
    cin >> choice;

    switch (choice)
    {
        case 1:
        // Hand Cricket Game
        while (true) {
        cout << "Decide Overs to be played:";
        cin >> over;
        if (over <= 0 || over > 5) {
            cout << "Enter number between 1 and 5";
            continue;
        }
        else
            break;
    }
    while (true) {
        cout << "Decide wickets per side(1-11):";
        cin >> wick;
        if (wick <= 0 || wick >= 11) {
            cout << "Enter number between 1 and 11";
            continue;
        }
        else
            break;
    }
    cout << "Enter your guess (heads/tails):\n";
    cin >> playerGuess;
    // Convert to lowercase
    for (char &c : playerGuess) {
        c = tolower(c);
    }
    cout << playerGuess << endl;
    srand(time(0));
    tossResult = rand() % 2;
    toss = (tossResult == 0) ? "heads" : "tails";
    cout << "Toss result: " << toss << endl;

    if (playerGuess == toss) {
        cout << "Congratulations! You won the toss.\n";
        cout << "What do you choose (bat/bowl)?\n";
        cin >> playerChoice;
        // Convert to lowercase
        for (char &c : playerChoice) {
            c = tolower(c);
        }
        cout << "You chose to " << playerChoice << " first.\n";
        if (playerChoice == "bat") {
            userrun = botbowl(wick, over);
            cout << "\ninnings completed you scored " << userrun << " runs." << endl;
            botrun = botbat(wick, over);
            cout << "\ninnings completed bot scored " << botrun << " runs." << endl;
        }
        else {
            botrun = botbat(wick, over);
            cout << "\ninnings completed bot scored " << botrun << " runs." << endl;
            userrun = botbowl(wick, over);
            cout << "\ninnings completed you scored " << userrun << " runs." << endl;
        }
        if (botrun == userrun) {
            cout << "\nIt's a draw" << endl;
            cout << "Thanks for playing \n";
        }
        else if (botrun > userrun) {
            cout << "\nYou lost. Better luck next time." << endl;
            cout << "Thanks for playing \n";
        }
        else {
            cout << "\nCongratulations!! You won." << endl;
            cout << "Thanks for playing \n";
        }
    }
    else {
        cout << "Sorry, you lost the toss.\n";
        botChoice = rand() % 2;
        botDecision = (botChoice == 0) ? "bat" : "bowl";
        cout << "Bot chooses to " << botDecision << " first.\n";
        if (botDecision == "bat") {
            botrun = botbat(wick, over);
            cout << "\ninnings completed bot scored " << botrun << " runs." << endl;
            userrun = botbowl(wick, over);
            cout << "\ninnings completed you scored " << userrun << " runs." << endl;
        }
        else {
            userrun = botbowl(wick, over);
            cout << "\ninnings completed you scored " << userrun << " runs." << endl;
            botrun = botbat(wick, over);
            cout << "\ninnings completed bot scored " << botrun << " runs." << endl;
        }
        if (botrun == userrun) {
            cout << "\nIt's a draw" << endl;
            cout << "Thanks for playing \n";
        }
        else if (botrun > userrun) {
            cout << "\nYou lost. Better luck next time." << endl;
            cout << "Thanks for playing \n";
        }
        else {
            cout << "\nCongratulations!! You won." << endl;
            cout << "Thanks for playing \n";
        }
    }
        break;

        case 2:
        // Snake Game
        cout << "Enter your name: ";
        cin >> playerName;
        dfc = snakeGame.setDifficulty();
        snakeGame.gameInit();
        while (!snakeGame.gameOver()) 
        {
            snakeGame.gameRender(playerName);
            snakeGame.userInput();
            snakeGame.updateGame();
            Sleep(dfc);
        }
        break;

        case 3:
        //Tic Tac Toe
        char board[3][3];
        rules();
        board_initialization(board);
        print_board(board);
        gameplay(board, toss1());
        break;
    }
    }while(choice!=4);
    return 0;
}

int botbat(int wick, int over) {
    int c, j = 0, r = 0, r1 = 0, r2 = 0, d, loop;
    Bot botarr[6];
    for (j = 0; j < 6; j++) {
        botarr[j].runs = 0;
    }
    j = 0;
    cout << "\n\n Terminal Handcricket Person vs Bot \n\n";
    for (loop = 0; loop < wick; loop++) {
        // r1=r1+r;
        r = 0;
        while (true) {
            j = j + 1;
            if (j == ((over * 6) + 1)) {
                loop = 12;
                break;
            }
            srand(time(NULL));
            c = rand() % 7;
            cout << "\n Input d number from 0 to 6 \n";
            cin >> d;
            r = r + c;
            r2 = r2 + c;
            if (c > 6 || c < 0) {
                cout << "Input d valid number from 0 to 6";
                r = r - c;
                r2 = r2 - c;
                j = j - 1;
                continue;
            }
            else if (d == c && j % 6 == 0) {
                cout << "Computer chose " << d << endl;
                cout << "You bowled out your opponent";
                r = r - c;
                r2 = r2 - c;
                cout << "The Bot scored " << r + r1 << " run in " << j << " balls uptill now \n";
                if (loop == (wick - 1)) {
                    botarr[(int)((j - 1) / 6)].runs += r2;
                }
                botarr[j % 6].runs = r2;
                r2 = 0;
                break;
            }
            else if (d == c && j % 6 != 0) {
                cout << "Computer chose " << d << endl;
                cout << "You bowled out your opponent";
                r = r - c;
                r2 = r2 - c;
                cout << "The Bot scored " << r + r1 << " run in " << j << " balls uptill now \n";
                if (loop == (wick - 1)) {
                    botarr[(int)((j - 1) / 6)].runs += r2;
                }
                break;
            }
            else if (c == 6) {
                cout << "Slogged sweeped on the up and its a hugee six. \n";
                cout << "The Bot scored " << r + r1 << " run in " << j << " balls uptill now \n";
            }
            else if (c == 5) {
                cout << "An overthrow from the fielding team and its 5 \n";
                cout << "The Bot scored " << r + r1 << " run in " << j << " balls uptill now \n";
            }
            else if (c == 4) {
                cout << "A classical cover drive into the gap for 4. \n";
                cout << "The Bot scored " << r + r1 << " run in " << j << " balls uptill now \n";
            }
            else if (c == 3) {
                cout << "Some brave running and carefully placed into the gap, they take 3 runs \n";
                cout << "The Bot scored " << r + r1 << " run in " << j << " balls uptill now \n";
            }
            else if (c == 2) {
                cout << "Some quick running on display here, 2 runs \n";
                cout << "The Bot scored " << r + r1 << " run in " << j << " balls uptill now \n";
            }
            else if (c == 1) {
                cout << "Just d single on this one \n";
                cout << "The Bot scored " << r + r1 << " run in " << j << " balls uptill now \n";
            }
            else if (c == 0) {
                cout << "Clean defence ,good bowl.Dot \n";
                cout << "The Bot scored " << r + r1 << " run in " << j << " balls uptill now \n";
            }
            if (j % 6 == 0 && j > 1) {
                botarr[(j / 6) - 1].runs = r2;
                r2 = 0;
            }
        }
        r1 = r1 + r;
    }
    return r1;
}


int botbowl(int wick, int over) {
    int b, i = 0, s = 0, s1 = 0, s2 = 0, a, loop;
    Human humanarr[6];
    for (i = 0; i < 6; i++) {
        humanarr[i].runs = 0;
    }
    i = 0;
    cout << "\n\n Terminal Handcricket Person vs Bot \n\n";
    for (loop = 0; loop < wick; loop++) {
        // s1=s1+s;
        s = 0;
        while (true) {
            i = i + 1;
            if (i == ((over * 6) + 1)) {
                loop = 12;
                break;
            }
            srand(time(NULL));
            a = rand() % 7;
            cout << "Input a number from 0 to 6 \n";
            cin >> b;
            s = s + b;
            s2 = s2 + b;
            if (b > 6 || b < 0) {
                cout << "Input a valid number from 0 to 6";
                s = s - b;
                s2 = s2 - b;
                i = i - 1;
                continue;
            }
            else if (a == b && i % 6 == 0) {
                cout << "Computer chose " << a << endl;
                cout << "You bowled out your opponent";
                s = s - b;
                s2 = s2 - b;
                cout << "You scored " << s + s1 << " run in " << i << " balls uptill now \n";
                if (loop == (wick - 1)) {
                    humanarr[(int)((i - 1) / 6)].runs += s2;
                }
                humanarr[i % 6].runs = s2;
                s2 = 0;
                break;
            }
            else if (a == b) {
                cout << "Computer chose " << a << endl;
                cout << "You are out.";
                s = s - b;
                s2 = s2 - b;
                cout << "You scored " << s + s1 << " run in " << i << " balls uptill now \n";
                if (loop == (wick - 1)) {
                    humanarr[(int)((i - 1) / 6)].runs += s2;
                }
                break;
            }
            else if (b == 6) {
                cout << "Slogged sweeped on the up and its a hugee six. \n";
                cout << "Computer chose " << a << endl;
                cout << "You scored " << s + s1 << " run in " << i << " balls uptill now \n";
            }
            else if (b == 5) {
                cout << "An overthrow from the fielding team and its a 5 \n";
                cout << "Computer chose " << a << endl;
                cout << "You scored " << s + s1 << " run in " << i << " balls uptill now \n";
            }
            else if (b == 4) {
                cout << "A classical cover drive into the gap for a 4. \n";
                cout << "Computer chose " << a << endl;
                cout << "You scored " << s + s1 << " run in " << i << " balls uptill now \n";
            }
            else if (b == 3) {
                cout << "Some brave running and carefully placed into a gap, they take 3 runs \n";
                cout << "Computer chose " << a << endl;
                cout << "You scored " << s + s1 << " run in " << i << " balls uptill now \n";
            }
            else if (b == 2) {
                cout << "Some quick running on display here, 2 runs \n";
                cout << "Computer chose " << a << endl;
                cout << "You scored " << s + s1 << " run in " << i << " balls uptill now \n";
            }
            else if (b == 1) {
                cout << "Just a single on this one \n";
                cout << "Computer chose " << a << endl;
                cout << "You scored " << s + s1 << " run in " << i << " balls uptill now \n";
            }
            else if (b == 0) {
                cout << "Clean defence a good bowl.Dot \n";
                cout << "Computer chose " << a << endl;
                cout << "You scored " << s + s1 << " run in " << i << " balls uptill now \n";
            }
            if (i % 6 == 0 && i > 1) {
                humanarr[(i / 6) - 1].runs = s2;
                s2 = 0;
            }
        }
        s1 = s1 + s;
    }
    return s1;
}