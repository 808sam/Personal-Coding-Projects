#ifndef TUPLE_H
#define TUPLE_H
#include <string>
#include <vector>
#include "Scheme.h"

//holds the list of values
//used to store individual facts
class Tuple
{
public:
	Tuple(std::vector<std::string> valuesIn) : values(valuesIn) {}
	~Tuple();

	//input index and get that value in the tuple
	std::string at(size_t i) { return values.at(i); }

	//print each element in the tuple as a comma separated list in parenthesis
	std::string ToString();

	//getter
	std::vector<std::string> GetValues() const { return values; }

	//uses vector comparisons to define < for tuple
	//defined so computer can know how to add tuples to a set
	bool operator<(Tuple const& tuple) const;

	//takes this tuples scheme, another tuples and it's scheme
	//returns true if both tuples have the same value everywhere the schemes match
	bool CanJoin(std::vector<std::string>, Tuple, std::vector<std::string>);

	//Joins 2 tuples together based on the given scheme
	//no check if values are the same, first tuple will overwright second
	Tuple Join(std::vector<std::string>, Tuple, std::vector<std::string>);
private:
	std::vector<std::string> values;
};
#endif