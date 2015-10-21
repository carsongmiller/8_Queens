#include <iostream>
#include <fstream>
#include <cstdlib>

using namespace std;

const int w_ = 8;
const int h_ = 8;

bool isValid(int r, int c);
bool canPlace(int board[][w_], int r, int c, int &smallDim);
void placeQueens(int board[][w_], int r, int c, int& smallDim, int queenCount, ofstream &fileOut);
void copyBoard(int board[][w_], int newBoard[][w_]);
void printBoard(int board[][w_], ofstream &fileOut);
void printBoardLarge(int board[][w_], ofstream &fileOut);


int main()
{
	int board[h_][w_];

	ofstream fileOut;
	fileOut.open("8queens.txt");
	if (fileOut.fail())
	{
		cout << "Failed to create stream";
		exit(1);
	}

	cout << "Press enter to begin";
	cin.ignore();
	cout << "Generating Boards and writing to \"8queens.txt\"";

	for (int r = 0; r < h_; r++)
		for (int c = 0; c < w_; c++)
			board[r][c] = 0;

	int smallDim; //keeps track of which of w_ and h_ is larger and smaller
	if (h_ <= w_)
		smallDim = h_;
	else
		smallDim = w_;

	placeQueens(board, 0, 0, smallDim, 0, fileOut);

	fileOut.close();
	return 0;
}






void placeQueens(int board[][w_], int r, int c, int& smallDim, int queenCount, ofstream &fileOut)
{
	int newBoard[h_][w_];
	copyBoard(board, newBoard);

	bool alreadyUsedCol[w_]; //helping with efficiency
	for (int i = 0; i < w_; i++)
		alreadyUsedCol[i] = false;

	for (r; r < h_; r++)
	{
		for (c; c < w_; c++)
		{
			if (board[r][c] == 0 && !alreadyUsedCol[c] && canPlace(board, r, c, smallDim))
			{
				board[r][c] = 1;
				placeQueens(board, r + 1, 0, smallDim, queenCount + 1, fileOut);
				board[r][c] = 0;
				//printBoard(board);
				//cout << "\n\n\n";
			}
		}
	}

	if (queenCount >= 8)
	{
		cout << "Board found\n";
		printBoardLarge(board, fileOut);
		fileOut << "\n\n\n\n";
	}
}






bool canPlace(int board[][w_], int r, int c, int &smallDim)
{
	//diagonals
	for (int i = -smallDim + 1; i < smallDim - 1; i++)
	{
		if (isValid(r + i, c + i) && i != 0 && board[r + i][c + i])
			return false;
		else if (isValid(r - i, c + i) && i != 0 && board[r - i][c + i])
			return false;
	}

	//vertical
	for (int i = 0; i < h_; i++)
	{
		if (i != r && isValid(i, c) && board[i][c] != 0)
			return false;
	}

	//horizontal
	for (int i = 0; i < w_; i++)
	{
		if (i != c && isValid(r, i) && board[r][i] != 0)
			return false;
	}

	return true;
}



void copyBoard(int board[][w_], int newBoard[][w_])
{
	for (int r = 0; r < h_; r++)
		for (int c = 0; c < w_; c++)
			newBoard[r][c] = board[r][c];
}



void printBoard(int board[][w_], ofstream &fileOut)
{
	for (int r = 0; r < h_; r++)
	{
		for (int c = 0; c < w_; c++)
		{
			fileOut << board[r][c] << "\t";
		}
		fileOut << "\n";
	}
}



bool isValid(int r, int c)
{
	if (r >= 0 && r < h_ && c >= 0 && c < w_)
		return true;
	else return false;
}



//Copied from connect 4
void printBoardLarge(int board[][w_], ofstream &fileOut)
{
	fileOut << "+";

	//First row of ----+----
	for (int i = 0; i < w_; ++i)
		fileOut << "-------+";

	fileOut << "\n";


	//rows of cells with discs in them	
	for (int r = 0; r < h_; r++)
	{
		//First Row of | with no discs
		fileOut << "|   ";

		for (int i = 0; i < w_; i++)
			fileOut << "    |   ";

		//Row with discs

		fileOut << "\n|   ";

		for (int c = 0; c < w_; c++)
		{
			if (board[r][c] == 0)
				fileOut << " ";
			else
				fileOut << "X";

			fileOut << "   |   ";
		}

		//Second Row of | with no discs
		fileOut << "\n|   ";

		for (int i = 0; i < w_; i++)
			fileOut << "    |   ";

		//Bottom of each cell ----+----
		fileOut << "\n+";

		for (int i = 0; i < w_; ++i)
			fileOut << "-------+";

		fileOut << "\n";
	}
}