#ifndef TUPLE_H
#define TUPLE_H
#include <string>
#include <vector>
#include "Scheme.h"

class Tuple
{
public:
	Tuple(std::vector<std::string> valuesIn) : values(valuesIn) {}
	~Tuple();
	std::string at(size_t i) { return values.at(i); }
	std::string ToString();
	std::vector<std::string> GetValues() const { return values; }
	bool operator<(Tuple const& tuple) const;
	bool CanJoin(std::vector<std::string>, Tuple, std::vector<std::string>);
	Tuple Join(std::vector<std::string>, Tuple, std::vector<std::string>);
private:
	std::vector<std::string> values;
};
#endif