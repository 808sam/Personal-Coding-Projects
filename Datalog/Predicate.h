#ifndef PREDICATE_H
#define PREDICATE_H
#include <vector>
#include <string>
#include "Parameter.h"

enum PredicateType { PRED_SCHEME, PRED_FACT, PRED_QUERY, PRED_RULE };

//holds each parameter and name to form a predicate
//predicateName(parameter1, parameter2, ..., parameterN)
class Predicate
{
public:
	//creates a predicate with specified predicate type, predicate id, and list of parameters
	Predicate(PredicateType typeIn, std::string IdIn, std::vector<Parameter> parametersIn);
	~Predicate();
	//returns string of "<name>(<parameters>)"
	std::string ToString();

	//getters
	PredicateType GetType() { return type; }
	std::string GetName() { return name; }
	Parameter at(size_t i) { return parameters.at(i); }
	std::vector<Parameter> GetParameters() { return parameters; }
	//returns a vector of all the parameters data (strings)
	std::vector<std::string> GetValues();
private:
	PredicateType type;
	std::string name;
	std::vector<Parameter> parameters;
};

#endif