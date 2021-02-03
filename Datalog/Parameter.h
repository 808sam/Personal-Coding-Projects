#ifndef PARAMETER_H
#define PARAMETER_H
#include <string>

enum ParameterType { STR, PARAM_ID, EXP };

class Parameter
{
public:
	Parameter(ParameterType typeIn, std::string dataIn) : type(typeIn), data(dataIn) {}
	~Parameter();
	std::string ToString() { return data; }
	ParameterType GetType() { return type; }
	std::string GetData() { return data; }
private:
	ParameterType type;
	std::string data;
};

#endif