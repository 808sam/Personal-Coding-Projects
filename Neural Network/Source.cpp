#include "NeuralNetwork.h"
#include <vector>
#include <iostream>
#include <fstream>
#include <string>

//min score is best
double Cost(vector<double>, vector<double>);
size_t Max(vector<double>);
void PrintVect(vector<double>);
vector<vector<vector<double>>> AddingTraining(size_t, size_t, size_t);
vector<vector<vector<double>>> TotalAddAnswerKey(size_t);
size_t WeightedAnswer(vector<double>);
vector<double> PositivePercents(vector<double> vect)
{
	double total = 0;
	for (double num : vect)
	{
		if (num > 0) total += num;
	}
	vector<double> output;
	for (double num : vect)
	{
		if (num > 0)
		{
			double tempNum = (int)(num * 100000 / total);
			output.push_back(tempNum/1000);

		}
		else
		{
			output.push_back(0);
		}
	}
	return output;
}

using namespace std;

int main(int argc, char* argv[])
{
	srand(time(NULL));
	vector<size_t> size = { 21, 30, 19 };
	NeuralNetwork nNet(size);

	cout << "Do you want to train or load or continue train (t/l/c): ";
	char input;
	cin >> input;
	if (input == 't')
	{
		vector<vector<vector<double>>> key = AddingTraining(20, 19, 500);
		nNet.RandInitialize();

		//train neural net
		for (size_t j = 10000; j > 1; --j)
		{
			for (size_t i = 0; i < key.size(); ++i)
			{
				nNet.Compute(key.at(i).at(0));
				nNet.BackPropogation(key.at(i).at(1), 0.01);
			}
			if (j % 1 == 0) cout << j << endl;
		}

		ofstream outFile(argv[1]);
		outFile << nNet.Export();
		outFile.close();
	}
	else if (input == 'c')
	{
		cout << "How many iterations? (10 seconds per 25 iterations):";
		int numIterations;
		cin >> numIterations;
		
		cout << "How drastic the change (reccomended 0.005): ";
		double change;
		cin >> change;

		vector<vector<vector<double>>> key = TotalAddAnswerKey(9);

		//import
		ifstream inFile(argv[1]);
		string inText;
		while (!inFile.eof())
		{
			string tmpString;
			getline(inFile, tmpString);
			inText = inText + tmpString + "\n";
		}
		nNet.Import(inText);
		inFile.close();

		//train neural net
		for (size_t j = numIterations; j > 0; --j)
		{
			for (size_t i = 0; i < key.size(); ++i)
			{
				nNet.Compute(key.at(i).at(0));
				nNet.BackPropogation(key.at(i).at(1), change);
			}
			if (j % 1 == 0) cout << j << endl;
		}
		cout << (char)7;

		ofstream outFile(argv[1]);
		outFile << nNet.Export();
		outFile.close();

	}
	else
	{
		ifstream inFile(argv[1]);
		string inText;
		while (!inFile.eof())
		{
			string tmpString;
			getline(inFile, tmpString);
			inText = inText + tmpString + "\n";
		}
		nNet.Import(inText);
		inFile.close();
	}

	cout << "NEURAL NET: " << endl << nNet.Export();

	//print total cost
	double totalScore = 0;
	for (vector<vector<double>> answer : TotalAddAnswerKey(9))
	{
		totalScore += Cost(answer.at(1), nNet.Compute(answer.at(0)));
	}
	cout << "TOTAL Cost: " << totalScore << endl;

	char yOrN;
	cout << "Would you like to see percentages while testing (y/n): ";
	cin >> yOrN;
	bool seeWeights = (yOrN == 'y');

	cout << "Manual Train? (y/n);";
	cin >> yOrN;
	bool manualTrain = (yOrN == 'y');

	//test neural net
	int input1;
	int input2;

	cout << "INPUT 1: ";
	cin >> input1;
	cout << "INPUT 2: ";
	cin >> input2;

	while (input2 >= 0 && input2 <= 9 && input1 >= 0 && input1 <= 9)
	{
		vector<double> input(20);
		for (size_t i = 0; i < 10; ++i) input.at(i) = 0;
		input.at(input1) = 1;
		input.at(input2 + size.at(0)/2) = 1;

		if (seeWeights)
		{
			PrintVect(PositivePercents(nNet.Compute(input)));
		}
		cout << endl << WeightedAnswer(nNet.Compute(input)) << endl;
		if (manualTrain)
		{
			vector<double> correctAnswer(19);
			fill(correctAnswer.begin(), correctAnswer.end(), 0);
			correctAnswer.at(input1 + input2) = 1;
			nNet.BackPropogation(correctAnswer, 0.00001);
		}
		cin.clear();
		cin.ignore();

		cout << "INPUT 1: ";
		cin >> input1;
		cout << "INPUT 2: ";
		cin >> input2;
	}

	ofstream outFile(argv[1]);
	outFile << nNet.Export();
	outFile.close();

	system("pause");
	return 0;
}



//functions
size_t Max(vector<double> inputs)
{
	size_t max = 0;
	for (size_t i = 1; i < inputs.size(); i++)
	{
		if (inputs.at(i) > inputs.at(max)) max = i;
	}
	return max;
}

//min cost is best
double Cost(vector<double> test, vector<double> in)
{
	double score = 0;
	for (size_t i = 0; i < test.size() && i < in.size(); i++)
	{
		score += (test.at(i) - in.at(i)) * (test.at(i) - in.at(i));
	}
	return score;
}

void PrintVect(vector<double> list)
{
	cout << "(" << list.at(0);
	for (size_t i = 1; i < list.size(); ++i) cout << ", " << list.at(i);
	cout << ")";
}

//cuts input in half, one for each integer input
//output is the neuron of the sum of two random inputs
vector<vector<vector<double>>> AddingTraining(size_t inputSize, size_t outputSize, size_t numTrials)
{
	vector<vector<vector<double>>> trainingData;
	for (size_t i = 0; i < numTrials; ++i)
	{
		trainingData.push_back(*(new vector<vector<double>>));
		trainingData.at(i).push_back(*(new vector<double>(inputSize)));
		trainingData.at(i).push_back(*(new vector<double>(outputSize)));

		//create inputs
		for (size_t j = 0; j < inputSize; ++j) trainingData.at(i).at(0).at(j) = 0;
		size_t randNum1 = rand() % (inputSize / 2);
		size_t randNum2 = rand() % (inputSize / 2);
		trainingData.at(i).at(0).at(randNum1) = 1;
		trainingData.at(i).at(0).at(randNum2 + inputSize/2) = 1;
		
		//create output
		for (size_t j = 0; j < outputSize; ++j) trainingData.at(i).at(1).at(j) = 0;
		trainingData.at(i).at(1).at(randNum1 + randNum2) = 1;
	}

	return trainingData;
}

//gives as answer weighted by square to higher outputs
//ignores negative numbers
size_t WeightedAnswer(vector<double> input)
{
	//find sum of outputs
	double sum = 0;
	for (double output : input)
	{
		if (output > 0) sum += output * output;
	}

	//subtract until less than 0
	//tells which input the rand picked, weighted to larger inputs
	double randNum = ((double) rand() / RAND_MAX) * sum;
	for (size_t i = 0; i < input.size(); ++i)
	{
		if (input.at(i) > 0) randNum -= input.at(i) * input.at(i);
		if (randNum <= 0) return i;
	}

	//if rounding error skips, must have been the last positive one
	for (int i = input.size() - 1; i >= 0; --i)
	{
		if (input.at(i) > 0) return i;
	}

	//if all are less than 0, return random
	return rand() % input.size();
}

vector<vector<vector<double>>> TotalAddAnswerKey(size_t maxNum)
{
	vector<vector<vector<double>>> key;
	for (size_t firstNum = 0; firstNum <=  maxNum; ++firstNum)
	{
		for (size_t secondNum = 0; secondNum <= maxNum; ++secondNum)
		{
			vector<vector<double>> singleAnswer(2);
			//initialize input and outputs
			vector<double> input((maxNum+1)*2);
			vector<double> output((maxNum * 2) + 1);
			for (size_t i = 0; i < input.size(); ++i)
			{
				input.at(i) = 0;
			}
			for (size_t i = 0; i < output.size(); ++i)
			{
				output.at(i) = 0;
			}

			//add inputs and output num
			input.at(firstNum) = 1;
			input.at(maxNum + 1 + secondNum) = 1;
			output.at(firstNum + secondNum) = 1;
			
			//create single key
			singleAnswer.at(0) = input;
			singleAnswer.at(1) = output;
			
			//add single to test key vector
			key.push_back(singleAnswer);
		}
	}
	return key;
}