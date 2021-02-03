#ifndef NEURON_H
#define NEURON_H

#include <vector>

double PositiveOrZero(double a);
//used as default func for neuron
double SmoothSwitch(double input);

using namespace std;

class Neuron
{
public:
	//takes the function the neuron will use
	Neuron(double(*neuronFunc)(double));
	//takes a vector of inputs from previous neuronLayer and weights and gives calculates neuronValue
	double CalculateNeuron(vector<double>& inputLayer, vector<double>& weights);
	//returns an approximate derivitive of the neuron based on it's value and neuronFunction
	double ApproxDerivative() const;
	//gets the neuronValue
	double GetOutput();
private:
	//the neuron function
	double(*NeuronFunc)(double);
	//the output value
	double neuronValue;
};

#endif