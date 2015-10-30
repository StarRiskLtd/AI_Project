//CS471
//November 2015
//Jason Meyer & Russell Hathaway
//
//Tic tac toe AI using alpha beta pruning
//with the minimax algorithm.
//A depth limit may be introduced via a prompt
//which allows the depth of the search to be limited.


#include <stdio.h>
#include <stdlib.h>     /* srand, rand */
#include <time.h>       /* time */
#include <string>
#include <iostream>
#include <vector>
#include <limits>        /* max/min for alpha/beta*/

using std::string;
using std::cout;
using std::cin;
using std::endl;
using std::vector;
using std::max;
using std::min;




//The tic tac toe squares are represented by a multidimensional array
char board[3][3] = {0, 0, 0, 0, 0, 0, 0, 0, 0};
char player = 'X';
bool win = false;




//Each square on the board contains a pair of XY coordinates
class Square {
   
    public:
    int X, Y;
    Square(int x_val, int y_val) {
        X = x_val;
        Y = y_val;
    }
    
};


//A vector of all empty squares with their coordinates in the 3d array
vector<Square> availableSquares;

//Call getEmptySquares to return a vector of current available squares
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





//Each square has a value, An object of class Square Value contains a square and its corresponding value
class SquareValue {
 
    public:
    Square square;
    int value;
    
    //constructor
    SquareValue( Square current_square, int square_value) : square(current_square), value(square_value){
        square = current_square;
        value = square_value;
    }
    
    void squareValToString() {
        cout << "Square: " << "[" << square.X << ", " << square.Y << "]  " << "Value: " << value ;
    }
    
    ~SquareValue(){};
};

//A vector of the current child Square Values is used to represent the available moves for MAX or MIN
vector<SquareValue> child_scores_vector;





//Choose best square for the AI
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




//return the current value of a square
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





//get the value of a square move , called within alphabeta
int getChildValue() {
    int score = 0;
    //evaluate columns
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
        //update the score
        score+=currentValue(X, O);
    }
    //evaluate rows
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
        //update score
        score+=currentValue(X, O);
    }
    int empty = 0;
    int X = 0;
    int O = 0;
    
    //evaluate diagonals
    for (int i = 0, j = 0; i < 3; ++i, ++j) {
        if (board[i][j] == 'X') {
            X++;
        } else if (board[i][j] == 'O') {
            O++;
        } else {
            empty++;
        }
    }
    
    //update the score
    score+=currentValue(X, O);
    
    //reset temp values
    empty = 0;
    X = 0;
    O = 0;
    
   
    for (int i = 2, j = 0; i > -1; --i, ++j) {
        if (board[i][j] == 'X') {
            X++;
        } else if (board[i][j] == 'O') {
            O++;
        } else {
            empty++;
        }
    }
    
    //update the score
    score+=currentValue(X, O);
    return score;
}





//input for human player, checks for valid input
void getInput()
{
	int board_position_selection;
	cout << "O's move :";
	cin >> board_position_selection;
    while (cin.fail()) {
        
        cout<<"Invalid choice, must be [1-9] inclusive."<<endl;
        cout << "O's move :";
        std::cin.clear();
        std::cin.ignore(256,'\n');
        cin>>board_position_selection;
    }
	switch (board_position_selection)
	{
		case 1 :
            if(board[0][0]==0){
                board[0][0] = 'O';
                break;
            }
            else{
            getInput();
            break;
            }
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
            
        default:
            getInput();
            break;
	}
}





//check for winning state or tie state
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
    //end check win for 0
    
    return false;
    
}





//a depth limit can be used to reduce the AI
int depth_limit = -1;

//**
//Minimax depth first traversal evaluates nodes and updates alpha or beta as required.
int alphaBeta(char player, int depth, int alpha, int beta){
    
    if(beta<=alpha){ //Evaluate adjacent nodes only if beta > alpha, otherwise prune.
        //cout << "Performing alpha-beta pruning. Depth :  " <<  depth << endl;
        if(player == 'X')
        {
            return std::numeric_limits<int>::max();  //  represents +infinity
        }
        else
        {
            return std::numeric_limits<int>::min(); // represents -infinity
        }
    }
    
    if(depth == depth_limit || checkWin()){
     
        return getChildValue();
    }

   
    vector<Square> empty_squares = getEmptySquares();
    
    //if there are no moves left, return
    if(empty_squares.size() == 0) {
        return 0;
    }
    if(depth==0) {
        
        child_scores_vector.clear();  //ensure child_scores_vector is cleared
    }
    
    int MAX = std::numeric_limits<int>::min();  // +infinity
    int MIN = std::numeric_limits<int>::max();  // -infinity
    
    for(std::vector<Square>::iterator current_square = empty_squares.begin(); current_square != empty_squares.end(); ++current_square)
    {
        
        
        int current_value = 0;
        
        if(player == 'X'){
            
            board[current_square->X][current_square->Y] = 'X';
            current_value = alphaBeta('O', depth+1, alpha, beta);
            MAX = max(MAX, current_value);              //update MAX value
            alpha = max(current_value, alpha);          //update alpha
            if(depth == 0)
                
                //push current square value into scores vector
                child_scores_vector.push_back(SquareValue(*current_square, current_value));
            
        }else if(player == 'O'){
            
            board[current_square->X][current_square->Y] = 'O';
            current_value = alphaBeta('X', depth+1, alpha, beta);
            MIN = min(MIN, current_value);              //update MIN
            beta = min(current_value, beta);            //update beta
        }
        //reset square to empty value
        board[current_square->X][current_square->Y] = 0;
        
        //Don't evaluate the rest of the adjacent nodes if Alpha-Beta pruning was performed,
        if(current_value == std::numeric_limits<int>::max() || current_value == std::numeric_limits<int>::min()) break;
    }
    
    
    if(player == 'X'){
        return MAX;
    }
    else{
        return  MIN;
    }
}


int main(void) {
    cout << "         TIC TAC TOE AI" << endl;
    cout << "             CS471" << endl;
    cout << "   Jason Meyer & Russell Hathaway" << endl;

    cout<< "      1 2 3           - - -" << endl;
    cout<< "      4 5 6           - - -" << endl;
    cout<< "      7 8 9           - - -" << endl;
    cout << "spaces are numbered in order" <<endl;
    srand (time(NULL));         /* initialize random seed: */
    string userin;
    cout << "AI is X, You are O, do you want to go first?(y/n)";
    cin >> userin;
    if(userin.substr(0,1)=="n"|| userin.substr(0,1)=="N")/* if AI goes first */
    {
        int temp = rand() % 3 , temp2 = rand() % 3;// generate numbers between 0 and 2
        board[temp][temp2] = 'X'; //place AIs first move using random numbers
        
    }
    cout << string( 5, '\n' );
    
    
    
    //Begin Game
	while(!checkWin())
	{
        drawBoard();    cout << string( 5, '\n' );
        getInput();
        drawBoard();    cout << string( 5, '\n' );
    
        if(checkWin()){break;}      //check if O made a game-ending move
    
        //using the minimax algorith with alphabeta pruning, calculate the best square values for AI player X
        alphaBeta('X', 0, std::numeric_limits<int>::min(), std::numeric_limits<int>::max());
    
        
        Square ai_best_square = getBestSquare();            //get the MAX square for AI player X
        board[ai_best_square.X][ai_best_square.Y] = 'X';    //place the X for AI player
        
	}
    //End Game
    if(getEmptySquares().empty()){
        cout << string( 5, '\n' );
        drawBoard();
        cout << string( 5, '\n' );
        cout<< "Tie Game!"<<endl;
        return 0;
    }
    else{
        cout << string( 5, '\n' );
        drawBoard();
        cout << string( 5, '\n' );
        cout << "Winner!" << endl;
        return 0;
    }
}
