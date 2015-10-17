#include <stdio.h>
#include <string>
#include <iostream>
#include <vector>

using std::string;
using std::cout;
using std::cin;
using std::endl;
using std::vector;


char board[3][3] = {'1', '2', '3', '4', '5', '6', '7', '8', '9'};
char player = 'X';
bool win = false;



class Square {
    
    int X, Y;
    
    public: Square(int x_val, int y_val) {
        X = x_val;
        Y = y_val;
    }
    
    void squareToString() {
        cout << "[" << X << ", " << Y << "]" << endl;
    }
};

    
vector<Square> availableSquares;
    
void getEmptySquares() {
    availableSquares.clear();
    for (int i = 0; i < 3; ++i) {
        for (int j = 0; j < 3; ++j) {
            if (board[i][j] != 'X' && board[i][j] != 'O') {
                availableSquares.push_back(Square(i, j));
                
            }
        }
    }
}
    
    


void drawBoard()
{
	for (int i = 0; i<3;i++)
	{
		for (int j = 0; j<3; j++)
		{
			cout << board[i][j] << " ";
		}
		cout << endl;
	}
    cout << endl;
}

void getInput()
{

	int board_position_selection;
	cout << player << "'s move :";
	cin >> board_position_selection;

	switch (board_position_selection)
	{
		case 1 :
			board[0][0] = player;
			break;
		case 2 :
			board[0][1] = player;
			break;
		case 3 :
			board[0][2] = player;
			break;
		case 4 :
			board[1][0] = player;
			break;
		case 5 :
			board[1][1] = player;
			break;
		case 6 :
			board[1][2] = player;
			break;
		case 7 :
			board[2][0] = player;
			break;
		case 8 :
			board[2][1] = player;
			break;
		case 9 :
			board[2][2] = player;
			break;

	}

}

void switchPlayer()
{
	if (player == 'X')
	{
		player = 'O';
	}
	else
	{
		player = 'X';
	}
}

void checkWin()
{
	//check win for X
    if ((board[0][0] == board[1][1] && board[0][0] == board[2][2] && board[0][0] == 'X') || (board[0][2] == board[1][1] && board[0][2] == board[2][0] && board[0][2] == 'X')) {
        win = true;
    }
    for (int i = 0; i < 3; ++i) {
    if ((board[i][0] == board[i][1] && board[i][0] == board[i][2] && board[i][0] == 'X')
        || (board[0][i] == board[1][i] && board[0][i] == board[2][i] && board[0][i] == 'X')) {
        win = true;
        }
    }
    //end check win for X

	//check win for O
    if ((board[0][0] == board[1][1] && board[0][0] == board[2][2] && board[0][0] == 'O') || (board[0][2] == board[1][1] && board[0][2] == board[2][0] && board[0][2] == 'O')) {
        win = true;
    }
    for (int i = 0; i < 3; ++i) {
        if ((board[i][0] == board[i][1] && board[i][0] == board[i][2] && board[i][0] == 'O')
            || (board[0][i] == board[1][i] && board[0][i] == board[2][i] && board[0][i] == 'O')) {
            win = true;
        }
    }
}



int main(void) {
	drawBoard();
	while(win == false)
	{
    getEmptySquares();
        for(std::vector<Square>::iterator it = availableSquares.begin(); it != availableSquares.end(); ++it) {
            it->squareToString();
        }
	getInput();
    cout << string( 100, '\n' );
	drawBoard();
	checkWin();
	switchPlayer();
	}
	cout << "Winner!" << endl;
	return 0;
}
