//
// Created by samue on 12/28/2020.
//

#ifndef PIPELAYER_PIPEBOARD_H
#define PIPELAYER_PIPEBOARD_H
#include <vector>
#include <iostream>

enum play { PLAY_EMPTY, PLAY_X, PLAY_O };
struct point
{
	size_t row;
	size_t col;
	point(size_t rowIn, size_t colIn) : row(rowIn), col(colIn) {}
};

class PipeBoard {
private:
	std::vector<std::vector<play>> board;
	static char GetConnection(play played, char lineChar);
	static bool CheckWin(std::vector<std::vector<play>>& board, size_t row, size_t col, play player);
	static int CalcScore(std::vector<std::vector<play>> board, size_t row, size_t col, play player, int maxScore);
	static bool CheckWin(play player, std::vector<std::vector<play>> boardIn);

public:
	//create board with set side length
	explicit PipeBoard(size_t size);
	//prints board to given file
	void Print(std::ostream& output = std::cout);
	//adds play to board
	void Play(size_t row, size_t col, play played);
	//checks if the board is in a winning state
	bool CheckWin(play player);
	//calculates the best play by exhaustive search
	//takes a long time for all but the smallest cases
	point CalcPlay(play player);
	std::vector<std::vector<play>> GetBoard() { return board; }
};


#endif //PIPELAYER_PIPEBOARD_H
