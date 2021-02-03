#ifndef NEURAL_NETWORK_H
#define NEURAL_NETWORK_H

#include "NeuralLayer.h"
#include <string>
#include <iostream>
#include <sstream>
#include <fstream>
#include <ctime>
#include <random>
using namespace std;

class NeuralNetwork
{
public:
	//takes size of network as vector of each layer size and optional neruon function pointer double(*fnc)(double)
	NeuralNetwork(vector<size_t>& sizeVect, double(*computeFunc)(double) = SmoothSwitch);
	//initializes the weights to random values
	void RandInitialize();
	//takes the random amount, varies all weights by +/-randAmount/2
	void RandVary(double randAmount = 0.1);
	//takes inputs as vector and spits out outputs from neural network
	vector<double> Compute(vector<double> inputs);
	//gets the output by randomly selecting from normalized positive outputs
	size_t NormalizeCompute(vector<double>& inputs);
	//restuns a string with the neural network data
	string Export();
	//takes a string as input to form a neural network. String must be in same form as Export() returns;
	void Import(string& inputStr);
	//uses import and export to copy a NeuralNet
	void operator=(NeuralNetwork& inNet);
	//takes the vector of errors for each output neuron and optional scaling factor for a step. 
	//Preforms backprop with those results to update the Neural Network
	void BackPropogation(vector<double>, double = 1);
private:
	//The neurons
	vector<NeuralLayer*> neuralNet;
	//The weights connecting neurons
	vector<vector<vector<double>>> weightNet;
	//the stores neuron function
	double(*NeuronFunc)(double);

	//helper functions
};

#endif