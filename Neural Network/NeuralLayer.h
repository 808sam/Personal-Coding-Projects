#ifndef NEURAL_LAYER_H
#define NEURAL_LAYER_H

#include "Neuron.h"
#include <vector>

class NeuralLayer
{
public:
	//takes how many neurons there are and a neuron function
	NeuralLayer(size_t layerSize, double (*NeuronFunc)(double));
	~NeuralLayer();
	//spits out a vector of outputs based on inputs and given weights
	vector<double> Compute(vector<double> inputs, vector<vector<double>> weights);
	//takes the error from later layer and weights and gives back error for this layer. Also an optional scale factor
	vector<double> BackDerivative(vector<double> partialDerivatives, vector<vector<double>>& weights, double scale);
	void SetInputs(vector<double> inputs);
	//gets the output from the neurons
	vector<double> GetValues();
	//returns a vector of approximate derivitives for each neuron based on output, weights, and neuron function
	vector<double> GetDerivitives();
private:
	//the neurons in the layer
	vector<Neuron*> neuronLayer;
};

#endif
