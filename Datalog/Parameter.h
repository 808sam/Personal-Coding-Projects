#ifndef PARAMETER_H
#define PARAMETER_H
#include <string>

enum ParameterType { STR, PARAM_ID, EXP };

//holds type and value for parameters
class Parameter
{
public:
	//creates a parameter with specified type and value (dataIn)
	Parameter(ParameterType typeIn, std::string dataIn) : type(typeIn), data(dataIn) {}
	~Parameter();
	//could just use GetData, but when printing this is more familier
	std::string ToString() { return data; }
	ParameterType GetType() { return type; }
	std::string GetData() { return data; }
private:
	ParameterType type;
	std::string data;
};

#endif