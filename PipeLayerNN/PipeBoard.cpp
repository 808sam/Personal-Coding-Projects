//
// Created by samue on 12/28/2020.
//

#include "PipeBoard.h"

PipeBoard::PipeBoard(size_t size)
{
	//create each row
	for (size_t i = 0; i < 2 * size - 1; ++i)
	{
		board.emplace_back(i % 2 ? size - 1 : size);
		std::fill(board.at(i).begin(), board.at(i).end(), PLAY_EMPTY);
	}
}

char PipeBoard::GetConnection(play played, char lineChar)
{
	if (lineChar == 'o') return played == PLAY_O ? '-' : played == PLAY_X ? '|' : ' ';
	else return played == PLAY_O ? '|' : played == PLAY_X ? '-' : ' ';
}

void PipeBoard::Print(std::ostream& output)
{
	//print top row
	output << "    x";
	for (size_t i = 0; i < board.at(0).size() - 1; ++i)
	{
		output << "   x";
	}
	output << std::endl;

	char lineChar = ' ';
	for (size_t i = 0; i < board.size(); ++i)
	{
		//switch character each row, starting with 'o'
		lineChar = lineChar == 'o' ? 'x' : 'o';

		//print line number
		output << i + 1 << " ";
		//print first character of row
		if (lineChar == 'o') output << 'o';
		else output << "  x";

		//output line
		for (auto & j : board.at(i))
		{
			output << ' ' << GetConnection(j, lineChar) << ' ' << lineChar;
		}

		output << std::endl;
	}

	//print bottom row
	output << "    x";
	for (size_t i = 0; i < board.at(0).size() - 1; ++i)
	{
		output << "   x";
	}
	output << std::endl;
}

void PipeBoard::Play(size_t row, size_t col, play played)
{
	if (row  >= board.size() || col  >= board.at(0).size()) throw "INVALID PLAY";

	if (board.at(row).at(col) != PLAY_EMPTY) throw "OVERLAPPING PLAY";
	else board.at(row).at(col) = played;
}

bool PipeBoard::CheckWin(play player)
{
	return CheckWin(player, board);
}

bool PipeBoard::CheckWin(play player, std::vector<std::vector<play>> boardIn)
{
	if (player == PLAY_X)
	{
		for (size_t i = 0; i < boardIn.at(0).size(); ++i)
		{
			if (CheckWin(boardIn, 0, i, PLAY_X)) return true;
		}
	}
	else
	{
		for (size_t i = 0; i < boardIn.size(); i += 2)
		{
			if (CheckWin(boardIn, i, 0, PLAY_O)) return true;
		}
	}
	return false;
}

bool PipeBoard::CheckWin(std::vector<std::vector<play>>& board, size_t row, size_t col, play player)
{
	//check if off board
	if (row >= board.size() || col >= board.at(row).size()) return false;
	//check if self is good
	if (board.at(row).at(col) != player) return false;

	//check if reached edge
	if (player == PLAY_X && row == board.size() - 1) return true;
	if (player == PLAY_O && col == board.at(0).size() - 1) return true;


	//clear self and begin recursion
	board.at(row).at(col) = PLAY_EMPTY;
	bool isHorizontal = (row % 2 == 0 ^ player == PLAY_X);

	if (isHorizontal)
	{
		//check direct left or right
		if (CheckWin(board, row, col - 1, player) || CheckWin(board, row, col + 1, player)) return true;
		//check top wings
		if (CheckWin(board, row - 1, row % 2 ? col + 1 : col - 1, player) || CheckWin(board, row - 1, col, player)) return true;
		//check bottom wings
		if (CheckWin(board, row + 1, row % 2 ? col + 1 : col - 1, player) || CheckWin(board, row + 1, col, player)) return true;
	}
	else {
		//check direct up or down
		if (CheckWin(board, row - 2, col, player) || CheckWin(board, row + 2, col, player)) return true;
		//check top wings
		if (CheckWin(board, row - 1, row % 2 ? col + 1 : col - 1, player) || CheckWin(board, row - 1, col, player)) return true;
		//check bottom wings
		if (CheckWin(board, row + 1, row % 2 ? col + 1 : col - 1, player) || CheckWin(board, row + 1, col, player)) return true;
	}
	return false;
}

point PipeBoard::CalcPlay(play player)
{
	int maxTurns = 0;
	for (const auto& row : board) maxTurns += row.size();

	//start at worst possible score
	int bestScore = (maxTurns * -1) - 1;
	point bestPlay(0, 0);

	for (size_t i = 0; i < board.size(); ++i)
	{
		for (size_t j = 0; j < board.at(i).size(); ++j)
		{
			if (board.at(i).at(j) == PLAY_EMPTY)
			{
				int currScore = CalcScore(board, i, j, player, maxTurns + 1);
				std::cout << "(" << i + 1 << " " << j + 1 << "): " << currScore << std::endl;
				if (currScore > bestScore)
				{
					bestScore = currScore;
					bestPlay = point(i, j);
				}
			}
		}
	}
	return bestPlay;
}

int PipeBoard::CalcScore(std::vector<std::vector<play>> board, size_t row, size_t col, play player, int maxScore)
{
	board.at(row).at(col) = player;

	//if win, return max Score
	if (CheckWin(player, board)) return maxScore;

	//swap player
	player = player == PLAY_X ? PLAY_O : PLAY_X;


	//calculate other players best option
	int worstCase = maxScore * -1;
	for (size_t i = 0; i < board.size(); ++i)
	{
		for (size_t j = 0; j < board.at(i).size(); ++j)
		{
			if (board.at(i).at(j) == PLAY_EMPTY)
			{
				int currScore = CalcScore(board, i, j, player, maxScore);
				if (currScore > worstCase) worstCase = currScore;
				//short circuit if maxed score
				if (worstCase == maxScore) return (maxScore - 1) * -1;
			}
		}
	}
	//once have best case for next move for other player
	//penalize to make it closer to 0 so both players want shortest game possible to win, and longest to loss
	if (worstCase > 0) return (worstCase * -1) + 1; //slightly better to delay loss
	else return (worstCase * -1) - 1; //slightly worse to take longer to win
}