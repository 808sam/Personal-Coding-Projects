#include "NeuralNetwork.h"
#include <cmath>

NeuralNetwork::NeuralNetwork(vector<size_t>& sizeVect, double(*computeFunc)(double)) : NeuronFunc(computeFunc)
{
	//create neuron net vector
	for (size_t i = 0; i < sizeVect.size(); ++i)
	{
		neuralNet.push_back(new NeuralLayer(sizeVect.at(i), computeFunc));
	}

	//create weight connections vector
	for (size_t i = 0; i < sizeVect.size() - 1; ++i)
	{
		weightNet.push_back(*new vector<vector<double>>);
		for (size_t j = 0; j < sizeVect.at(i + 1); ++j)
		{
			weightNet.at(i).push_back(*new vector<double>(sizeVect.at(i)));
		}
	}
}

//initializes all weights randomly between -1 and 1
void NeuralNetwork::RandInitialize()
{
	for (size_t i = 0; i < weightNet.size(); ++i)
	{
		for (size_t j = 0; j < weightNet.at(i).size(); ++j)
		{
			for (size_t k = 0; k < weightNet.at(i).at(j).size(); ++k)
			{
				weightNet.at(i).at(j).at(k) = ((double)rand() / RAND_MAX) * 2 - 1;
			}
		}
	}
}

//randomly varies the weight by up to the input amount
//caps weights at +/- 1
void NeuralNetwork::RandVary(double randAmount)
{
	//all the loops!
	for (size_t i = 0; i < weightNet.size(); ++i)
	{
		for (size_t j = 0; j < weightNet.at(i).size(); ++j)
		{
			for (size_t k = 0; k < weightNet.at(i).at(j).size(); ++k)
			{
				weightNet.at(i).at(j).at(k) += randAmount * (((double)rand() / RAND_MAX) * 2 - 1);
				if (weightNet.at(i).at(j).at(k) > 1) weightNet.at(i).at(j).at(k) = 1;
				else if (weightNet.at(i).at(j).at(k) < -1) weightNet.at(i).at(j).at(k) = -1;
			}
		}
	}
}

vector<double> NeuralNetwork::Compute(vector<double> inputs)
{
	//trim or extend inputs to math initial layer
	inputs.push_back(1); //bias neuron, will get trimmed if already added
	while (inputs.size() < weightNet.at(0).at(0).size()) inputs.push_back(0);
	if (inputs.size() > weightNet.at(0).at(0).size()) inputs.resize(weightNet.at(0).at(0).size());

	//calculate inputs through first neurons
	neuralNet.at(0)->SetInputs(inputs);
	inputs = neuralNet.at(0)->GetValues();

	//propogate values through net
	for (size_t i = 1; i < neuralNet.size(); ++i)
	{
		inputs = neuralNet.at(i)->Compute(inputs, weightNet.at(i - 1));
	}

	return inputs;
}

size_t NeuralNetwork::NormalizeCompute(vector<double>& inputs)
{
	double totalPositive = 0;
	vector<double> outputs = Compute(inputs);
	for (double num : outputs) if (num > 0) totalPositive += num;
	double randNum = rand() * totalPositive;
	for (size_t i = 0; i < outputs.size(); ++i)
	{
		if (outputs.at(i) > 0)
		{
			totalPositive -= outputs.at(i);
			if (totalPositive <= 0) return i;
		}
	}
	//default case in case rounding errors and a high rand number cause it to not add up
	//only happens on high rand, so just pick the last index
	return outputs.size() - 1;
}

//returns string with size and weights
string NeuralNetwork::Export()
{
	ostringstream output;
	for (size_t i = 0; i < weightNet.size(); ++i)
	{
		output << weightNet.at(i).at(0).size() << " ";
	}
	output << weightNet.at(weightNet.size() - 1).size();
	output << endl << endl;


	for (size_t i = 0; i < weightNet.size(); ++i)
	{
		for (size_t j = 0; j < weightNet.at(i).size(); ++j)
		{
			for (size_t k = 0; k < weightNet.at(i).at(j).size(); ++k)
			{
				output << weightNet.at(i).at(j).at(k) << " ";
			}
			output << endl;
		}
		output << endl;
	}
	return output.str();
}

//reads in string of size and weights
void NeuralNetwork::Import(string& inputStr)
{
	neuralNet.clear();
	weightNet.clear();

	istringstream input(inputStr);
	string dimensions;
	getline(input, dimensions);


	//get size vector
	istringstream netSize(dimensions);
	int currLayerSize;
	vector<int> sizeVect;
	netSize >> currLayerSize;
	while (!netSize.eof())
	{
		sizeVect.push_back(currLayerSize);
		netSize >> currLayerSize;
	}
	sizeVect.push_back(currLayerSize);


	//taken from constructor
	//create neuron net vector
	for (size_t i = 0; i < sizeVect.size(); ++i)
	{
		neuralNet.push_back(new NeuralLayer(sizeVect.at(i), NeuronFunc));
	}


	//create weight connections vector
	for (size_t i = 0; i < sizeVect.size() - 1; ++i)
	{
		weightNet.push_back(*new vector<vector<double>>);
		for (size_t j = 0; j < sizeVect.at(i + 1); ++j)
		{
			weightNet.at(i).push_back(*new vector<double>(sizeVect.at(i)));
		}
	}


	//read in values for weights
	for (size_t i = 0; i < weightNet.size(); ++i)
	{
		for (size_t j = 0; j < weightNet.at(i).size(); ++j)
		{
			for (size_t k = 0; k < weightNet.at(i).at(j).size(); ++k)
			{
				double weightIn;
				input >> weightIn;
				weightNet.at(i).at(j).at(k) = weightIn;
			}
		}
	}
}

void NeuralNetwork::operator=(NeuralNetwork& netIn)
{
	string tempString = netIn.Export();
	this->Import(tempString);
}

//should do gradient decent for score. Whether or not it does, we'll see
void NeuralNetwork::BackPropogation(vector<double> goalOutput, double scale)
{
	//find vect of cost derivative for changes in final neuron layer
	vector<double> costDerivatives(goalOutput.size());
	vector<double> derivatives = neuralNet.at(neuralNet.size() - 1)->GetDerivitives();
	vector<double> netOutputs = neuralNet.at(neuralNet.size() - 1)->GetValues();
	for (size_t i = 0; i < goalOutput.size(); ++i)
	{
		//cost = (goal-NF(output))^2
		//cost' = -2(goal - NF(output))*NF'(output)
		costDerivatives.at(i) = 2 * (netOutputs.at(i) - goalOutput.at(i)) * derivatives.at(i);
	}


	for (size_t i = neuralNet.size() - 1; i > 0; --i)
	{
		costDerivatives = neuralNet.at(i - 1)->BackDerivative(costDerivatives, weightNet.at(i - 1), scale);
	}
}
