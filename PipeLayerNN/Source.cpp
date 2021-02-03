#include "PipeBoard.h"
#include "NeuralNetwork.h"

#define BOARD_SIZE 5

using namespace std;

point getPoint(size_t index, size_t boardSize);
void LinearNormalize(vector<double>& vect);
void operator+=(vector<double>& vect1, const vector<double>& vect2);
vector<play> linearizeBoard(PipeBoard& board);
void filterPlayPipeLayer(vector<double>& output, const vector<play>& board);
size_t WeightedChoice(const vector<double> vect);
point GetNNPlay(PipeBoard board, NeuralNetwork& NN, play symbol);
pair <bool, point> NNPlayPipe(NeuralNetwork& NN1, NeuralNetwork& NN2);

int main()
{
	//setup
	srand(2);
	vector<size_t> size = { 41, 35, 30, 20, 20, 20, 20, 20, 30, 35, 41};
	NeuralNetwork NN(size);
	NN.RandInitialize();
	NeuralNetwork NN2(size);
	NN2.RandInitialize();
	bool first = true;
	vector<double> score(41);
	vector<double> score2(41);
	for (size_t i = 0; i < 41; ++i)
	{
		score.at(i) = 0;
		score2.at(i) = 0;
	}

	pair<bool, point> check = NNPlayPipe(NN, NN2);

	cout << "WE HAVE A WINNER!" << endl;
	cout << check.first << " " << "(" << check.second.row << "," << check.second.col << ")" << endl;
	system("pause");
}

point getPoint(size_t index, size_t boardSize)
{
	size_t currRow = 0;
	//sideways rows are off rows
	bool offRow = false;

	while (index >= (boardSize - 1 * (offRow)))
	{
		index -= boardSize -1*(offRow);
		offRow = offRow?false:true;
		++currRow;
	}
	return (point(currRow, index));

}
void LinearNormalize(vector<double>& vect)
{
	double total = 0;
	for (const double& num : vect) total += num;
	for (double& num : vect) num /= total;
}
void operator+=(vector<double>& vect1, const vector<double>& vect2)
{
	if (vect1.size() != vect2.size()) return;
	for (size_t i = 0; i < vect1.size(); ++i) vect1.at(i) += vect2.at(i);
}
vector<play> linearizeBoard(PipeBoard& board)
{
	vector<play> vectBoard;
	for (const vector<play>& line : board.GetBoard())
	{
		for (const play& symbol : line) vectBoard.push_back(symbol);
	}
	return vectBoard;
}
void filterPlayPipeLayer(vector<double>& output, const vector<play>& board)
{
	for (size_t i = 0; i < output.size(); ++i)
	{
		if (board.at(i) != PLAY_EMPTY || output.at(i) < 0) output.at(i) = 0;
	}
}
size_t WeightedChoice(const vector<double> vect)
{
	double total = 0;
	for (double num : vect) total += num;
	if (total == 0) return vect.size();
	double choice = ((double) rand()/RAND_MAX) * total;
	for (size_t i = 0; i < vect.size(); ++i)
	{
		choice -= vect.at(i);
		if (choice <= 0) return i;
	}
	return vect.size() - 1;
}
point GetNNPlay(PipeBoard board, NeuralNetwork& NN, play symbol)
{
	//create input vect
	vector<double> inputs;
	for (play place: linearizeBoard(board))
	{
		if (place == PLAY_EMPTY) inputs.push_back(0);
		else if (place == symbol) inputs.push_back(1);
		else inputs.push_back(-1);
	}

	vector<double> output = NN.Compute(inputs);
	//fixme need to not allow overlapping play
	filterPlayPipeLayer(output, linearizeBoard(board));
	size_t spot = WeightedChoice(output);
	return getPoint(spot, BOARD_SIZE);
}
pair<bool, point> NNPlayPipe(NeuralNetwork& NN1, NeuralNetwork& NN2)
{
	PipeBoard board(BOARD_SIZE);
	point spot(0,0);
	while (true)
	{
		spot = GetNNPlay(board, NN1, PLAY_X);
		board.Play(spot.row, spot.col, PLAY_X);
		if (board.CheckWin(PLAY_X)) return pair<bool, point>(true, spot);
		board.Print();
		//system("pause");

		//fixme rotate board

		spot = GetNNPlay(board, NN2, PLAY_O);
		board.Play(spot.row, spot.col, PLAY_O);
		if (board.CheckWin(PLAY_O)) return pair<bool, point>(false, spot);
		board.Print();
		//system("pause");
	}
}