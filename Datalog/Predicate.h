#ifndef PREDICATE_H
#define PREDICATE_H
#include <vector>
#include <string>
#include "Parameter.h"

enum PredicateType { PRED_SCHEME, PRED_FACT, PRED_QUERY, PRED_RULE };

class Predicate
{
public:
	Predicate(PredicateType, std::string, std::vector<Parameter>);
	~Predicate();
	std::string ToString();
	PredicateType GetType() { return type; }
	std::string GetName() { return name; }
	Parameter at(size_t i) { return parameters.at(i); }
	std::vector<Parameter> GetParameters() { return parameters; }
	std::vector<std::string> GetValues();
private:
	PredicateType type;
	std::string name;
	std::vector<Parameter> parameters;
};

#endif