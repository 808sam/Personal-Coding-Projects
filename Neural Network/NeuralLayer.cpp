#include "NeuralLayer.h"



NeuralLayer::NeuralLayer(size_t layerSize, double(*NeuronFunc)(double)) : neuronLayer(layerSize)
{
	for (size_t i = 0; i < layerSize; ++i)
	{
		neuronLayer.at(i) = new Neuron(NeuronFunc);
	}
}

NeuralLayer::~NeuralLayer()
{
	for (Neuron* neuron : neuronLayer)
	{
		delete neuron;
	}
}

vector<double> NeuralLayer::Compute(vector<double> inputs, vector<vector<double>> weights)
{
	vector<double> outputs;
	for (size_t i = 0; i < neuronLayer.size(); ++i)
	{
		outputs.push_back(neuronLayer.at(i)->CalculateNeuron(inputs, weights.at(i)));
	}
	return outputs;
}

//returns a vector of partial derivatives for neurons
//changes weight to minimize cost (based on input partialDerivatives)
//need partial Derivatives for next layer and weights going to next layer
vector<double> NeuralLayer::BackDerivative(vector<double> partialDerivatives, vector<vector<double>>& weights, double scale)
{
	//initialize output to 0
	vector<double> partDerivOut(weights.at(0).size());
	for (size_t i = 0; i < partDerivOut.size(); ++i)
	{
		partDerivOut.at(i) = 0;
	}

	for (size_t i = 0; i < weights.size(); ++i)
	{
		for (size_t j = 0; j < weights.at(i).size(); ++j)
		{
			//partDeriv of (f(wg(x)) = f'(wg(x)) * wg'(x)
			//f'(g(x)) is what's in partDeriv vector given
			partDerivOut.at(j) += partialDerivatives.at(i) * weights.at(i).at(j) * neuronLayer.at(j)->ApproxDerivative();

			//since all the partial dervatives form gradient, can just change the weights by their negative partial derivitive to decrease cost
			//calculate like before, but now it's the weight changing instead of the neuron
			//f(wg(x))' = f'(wg(x) * g(x)w'
			//w' = 1, it's just what we say it is
			weights.at(i).at(j) -= partialDerivatives.at(i) * neuronLayer.at(j)->GetOutput() * scale;
		}
	}

	return partDerivOut;
}

vector<double> NeuralLayer::GetValues()
{
	vector<double> values;
	for (Neuron* neuron : neuronLayer)
	{
		values.push_back(neuron->GetOutput());
	}
	return values;
}

void NeuralLayer::SetInputs(vector<double> inputs)
{
	vector<double> fillerWeight = { 1 };
	vector<double> input(1);
	for (size_t i = 0; i < neuronLayer.size(); ++i)
	{
		input.at(0) = inputs.at(i);
		neuronLayer.at(i)->CalculateNeuron(input, fillerWeight);
	}
}

vector<double> NeuralLayer::GetDerivitives()
{
	vector<double> output;
	for (Neuron* neuron : neuronLayer)
	{
		output.push_back(neuron->ApproxDerivative());
	}
	return output;
}