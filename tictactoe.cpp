#include <stdio.h>
#include <string>
#include <iostream>
using std::string;
using std::cout;
using std::cin;
using std::endl;


char board[3][3] = {'1', '2', '3', '4', '5', '6', '7', '8', '9'};
char player = 'X';
bool win = false;

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
	if (board[0][0] == 'X' && board[0][1] == 'X' && board[0][2] == 'X')
	{
		win = true;
	}
	else if (board[1][0] == 'X' && board[1][1] == 'X' && board[1][2] == 'X')
	{
		win = true;
	}
	else if (board[2][0] == 'X' && board[2][1] == 'X' && board[2][2] == 'X')
	{
		win = true;
	}
	else if (board[1][2] == 'X' && board[1][1] == 'X' && board[2][0] == 'X')
	{
		win = true;
	}
	else if (board[0][0] == 'X' && board[1][1] == 'X' && board[2][2] == 'X')
	{
		win = true;
	}
	//end check win for X

	//check win for O
	if (board[0][0] == 'O' && board[0][1] == 'O' && board[0][2] == 'O')
	{
		win = true;
	}
	else if (board[1][0] == 'O' && board[1][1] == 'O' && board[1][2] == 'O')
	{
		win = true;
	}
	else if (board[2][0] == 'O' && board[2][1] == 'O' && board[2][2] == 'O')
	{
		win = true;
	}
	else if (board[1][2] == 'O' && board[1][1] == 'O' && board[2][0] == 'O')
	{
		win = true;
	}
	else if (board[0][0] == 'O' && board[1][1] == 'O' && board[2][2] == 'O')
	{
		win = true;
	}
}


int main(void) {
	drawBoard();
	while(win == false)
	{
	getInput();
	drawBoard();
	checkWin();
	switchPlayer();
	}
	cout << "Winner!" << endl;
	return 0;
}
