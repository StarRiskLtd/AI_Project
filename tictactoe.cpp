#include <stdio.h>
#include <stdlib.h>     /* srand, rand */
#include <time.h>       /* time */
#include <string>
#include <iostream>
#include <vector>
#include <limits>        /* max/min */


using std::string;
using std::cout;
using std::cin;
using std::endl;
using std::vector;
using std::max;
using std::min;



char board[3][3] = {0, 0, 0, 0, 0, 0, 0, 0, 0};
char player = 'X';
bool win = false;

//Each square on the board has an XY pos.
class Square {
   
    public:
    int X, Y;
    Square(int x_val, int y_val) {
        X = x_val;
        Y = y_val;
    }
    
};

//vector for empty square indexes
vector<Square> availableSquares;
vector<Square> getEmptySquares() {
    
    
    availableSquares.clear();
    for (int i = 0; i < 3; ++i) {
        for (int j = 0; j < 3; ++j) {
            if (board[i][j] != 'X' && board[i][j] != 'O') {
                availableSquares.push_back(Square(i, j));
                
            }
        }
    }
    return availableSquares;
}

//Square Value contains a square and its corresponding value

class SquareValue {
 
    public:
    Square square;
    int value;
    
   
    SquareValue( Square current_square, int square_value) : square(current_square), value(square_value){
        square = current_square;
        value = square_value;
    }
    
    void squareValToString() {
        cout << "Square: " << "[" << square.X << ", " << square.Y << "]  " << "Value: " << value ;
    }
};

vector<SquareValue> child_scores_vector;

Square getBestSquare() {
    int MAX = -100000;
    int best = -1;
    int i = 0;
    for(std::vector<SquareValue>::iterator it = child_scores_vector.begin(); it != child_scores_vector.end(); ++it) {
        
        if (MAX < it->value ) {
            MAX = it->value;
            best = i;
            
        }
        ++i;
    }
    
    return child_scores_vector[best].square;
}


int currentValue(int X, int O){
    int currentValue;
    if (X == 3) {
        currentValue = 100;
    } else if (X == 2 && O == 0) {
        currentValue = 10;
    } else if (X == 1 && O == 0) {
        currentValue = 1;
    } else if (O == 3) {
        currentValue = -100;
    } else if (O == 2 && X == 0) {
        currentValue = -10;
    } else if (O == 1 && X == 0) {
        currentValue = -1;
    } else {
        currentValue = 0;
    }
    return currentValue;
}


//draw the 3x3 board
void drawBoard()
{
    for (int i = 0; i<3;i++)
    {
        for (int j = 0; j<3; j++)
        {
            if(board[i][j] != 'X' && board[i][j] != 'O' ){
                cout << "- ";
            }
            else{
                cout << board[i][j] << " ";
            }
        }
        cout << endl;
    }
    cout << endl;
}

//get the value of a state, called within alphabeta
int getChildValue() {
    int score = 0;
    
    //Check all rows
    for (int i = 0; i < 3; ++i) {
        int empty = 0;
        int X = 0;
        int O = 0;
        for (int j = 0; j < 3; ++j) {
            if (board[i][j] == 0) {
                empty++;
            } else if (board[i][j] == 'X') {
                X++;
            } else {
                O++;
            }
            
        }
        score+=currentValue(X, O);
    }
    
    //Check all columns
    for (int j = 0; j < 3; ++j) {
        int empty = 0;
        int X = 0;
        int O = 0;
        for (int i = 0; i < 3; ++i) {
            if (board[i][j] == 0) {
                empty++;
            } else if (board[i][j] == 'X') {
                X++;
            } else {
                O++;
            }
        }
        score+=currentValue(X, O);
    }
    
    int empty = 0;
    int X = 0;
    int O = 0;
    
    //Check diagonal (first)
    for (int i = 0, j = 0; i < 3; ++i, ++j) {
        if (board[i][j] == 'X') {
            X++;
        } else if (board[i][j] == 'O') {
            O++;
        } else {
            empty++;
        }
    }
    
    score+=currentValue(X, O);
    
    empty = 0;
    X = 0;
    O = 0;
    
    //Check Diagonal (Second)
    for (int i = 2, j = 0; i > -1; --i, ++j) {
        if (board[i][j] == 'X') {
            X++;
        } else if (board[i][j] == 'O') {
            O++;
        } else {
            empty++;
        }
    }
    
    score+=currentValue(X, O);
    return score;
}





//input for human player, checks for valid input
void getInput()
{

	int board_position_selection;
	cout << "O's move :";
	cin >> board_position_selection;

	switch (board_position_selection)
	{
		case 1 :
            if(board[0][0]==0){
                board[0][0] = 'O';
                break;
            }
            getInput();
            break;
		case 2 :
            if(board[0][1]==0){
                board[0][1] = 'O';
                break;
            }
            getInput();
            break;
		case 3 :
            if(board[0][2]==0){
                board[0][2] = 'O';
                break;
            }
            getInput();
            break;
		case 4 :
            if(board[1][0]==0){
                board[1][0] = 'O';
                break;
            }
            getInput();
            break;
		case 5 :
            if(board[1][1]==0){
                board[1][1] = 'O';
                break;
            }
            getInput();
            break;
		case 6 :
            if(board[1][2]==0){
                board[1][2] = 'O';
                break;
            }
            getInput();
            break;
		case 7 :
            if(board[2][0]==0){
                board[2][0] = 'O';
                break;
            }
            getInput();
            break;
		case 8 :
            if(board[2][1]==0){
                board[2][1] = 'O';
                break;
            }
            getInput();
            break;
		case 9 :
            if(board[2][2]==0){
                board[2][2] = 'O';
                break;
            }
            getInput();
            break;
            
        default:  getInput();


	}
    

}

bool checkWin()
{
    //check if the game is a tie
    if(getEmptySquares().empty()){
        
        return true;
    }
    
	//check win for X
    if ((board[0][0] == board[1][1] && board[0][0] == board[2][2] && board[0][0] == 'X') || (board[0][2] == board[1][1] && board[0][2] == board[2][0] && board[0][2] == 'X')) {
        return true;
    }
    for (int i = 0; i < 3; ++i) {
    if ((board[i][0] == board[i][1] && board[i][0] == board[i][2] && board[i][0] == 'X')
        || (board[0][i] == board[1][i] && board[0][i] == board[2][i] && board[0][i] == 'X')) {
        return true;
        }
    }
    //end check win for X

	//check win for O
    if ((board[0][0] == board[1][1] && board[0][0] == board[2][2] && board[0][0] == 'O') || (board[0][2] == board[1][1] && board[0][2] == board[2][0] && board[0][2] == 'O')) {
        return true;
    }
    for (int i = 0; i < 3; ++i) {
        if ((board[i][0] == board[i][1] && board[i][0] == board[i][2] && board[i][0] == 'O')
            || (board[0][i] == board[1][i] && board[0][i] == board[2][i] && board[0][i] == 'O')) {
           return true;
        }
    }
    
    return false;
    
    
}




int depth_limit = -1;

int alphaBeta(char player, int depth, int alpha, int beta){
    
    if(beta<=alpha){
        cout << "Performing alpha-beta pruning. Depth :  " <<  depth << endl;
        if(player == 'X')
        {
            return std::numeric_limits<int>::max();
        }
        else
        {
            return std::numeric_limits<int>::min();
        }
    }
    
    if(depth == depth_limit || checkWin()){
     
        return getChildValue();
    }

   
    vector<Square> empty_squares = getEmptySquares();
    
    if(empty_squares.size() == 0) {
        return 0;
    }
    if(depth==0) {
        
        child_scores_vector.clear();
    }
    
    int MAX = std::numeric_limits<int>::min();
    int MIN = std::numeric_limits<int>::max();
    
    for(std::vector<Square>::iterator current_square = empty_squares.begin(); current_square != empty_squares.end(); ++current_square)
    {
        
        
        int current_value = 0;
        
        if(player == 'X'){
            
            board[current_square->X][current_square->Y] = 'X';
            current_value = alphaBeta('O', depth+1, alpha, beta);
            
            //update MAX value
            MAX = max(MAX, current_value);
            
            //update alpha
            alpha = max(current_value, alpha);
            
            if(depth == 0)
                
                //push square value into scores vector
                
                child_scores_vector.push_back(SquareValue(*current_square, current_value));
            
        }else if(player == 'O'){
            
            board[current_square->X][current_square->Y] = 'O';
            current_value = alphaBeta('X', depth+1, alpha, beta);
            
            //update MIN
            MIN = min(MIN, current_value);
            
            //update beta
            beta = min(current_value, beta);
        }
        //Reset board
        drawBoard(); cout<<depth<<endl;
        board[current_square->X][current_square->Y] = 0;
        
        //Don't evaluate the rest of the adjacent nodes if Alpha-Beta pruning was performed,
        if(current_value == std::numeric_limits<int>::min() || current_value == std::numeric_limits<int>::max()) break;
    }
    
    
    if(player == 'X'){
        return MAX;
    }
    else{
        return  MIN;
    }
}


int main(void) {
    /* initialize random seed: */
    srand (time(NULL));
	drawBoard();
    
    string userin;
    cout << "AI is X, You are O, do you want to go first?(y/n)";
    cin >> userin;
    if(userin.substr(0,1)=="n"|| userin.substr(0,1)=="N")/* if AI goes first */
    {
        int temp = rand() % 3 , temp2 = rand() % 3;/* generate numbers between 0 and 2: */

        board[temp][temp2] = 'X'; //place AIs first move using random numbers
        drawBoard();        //display the game board
        
        
    }
    //Begin Game
	while(!checkWin())
	{
   
    cout << string( 100, '\n' );
    drawBoard();
	getInput();
        
    cout << string( 100, '\n' );
	drawBoard();
    if(checkWin()){break;}
	
        
    alphaBeta('X', 0, std::numeric_limits<int>::min(), std::numeric_limits<int>::max());
        
   
    Square ai_best_square = getBestSquare();
    board[ai_best_square.X][ai_best_square.Y] = 'X';
        
        
	}
    if(getEmptySquares().empty()){
        cout << string( 100, '\n' );
        drawBoard();
        cout<< "Tie Game!"<<endl;
        return 0;
    }
    //End Game
    cout << string( 100, '\n' );
    drawBoard();
    cout << "winner!" << endl;
	return 0;
}
