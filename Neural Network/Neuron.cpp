#include "Neuron.h"
Neuron::Neuron(double (*neuronFunc)(double)) : neuronValue(0)
{
	this->NeuronFunc = neuronFunc;
}

double Neuron::CalculateNeuron(vector<double>& inputLayer, vector<double>& weights)
{
	//sum inputs
	neuronValue = 0;
	for (size_t i = 0; i < inputLayer.size() && i < weights.size(); ++i) //weights and inputLayer should be the same size
	{
		neuronValue += inputLayer.at(i) * weights.at(i);
	}

	return NeuronFunc(neuronValue);
}

double Neuron::ApproxDerivative() const
{
	const double DELTA = 0.000001;
	return (NeuronFunc(neuronValue + DELTA) - NeuronFunc(neuronValue - DELTA)) / (2*DELTA);
}

double Neuron::GetOutput()
{ 
	return NeuronFunc(neuronValue); 
}


//Neuron Functions
double SmoothSwitch(double input)
{
	if (input > 0) return 1.5 * input / (input + 1);
	else return -1.5 * input / (input - 1);
}

double PositiveOrZero(double a) //used as default func for neuron
{
	if (a > 1) return 1;
	else if (a > 0) return a;
	else return 0;

}