#ifndef RELATION_H
#define RELATION_H
#include <vector>
#include <string>
#include <set>
#include "Tuple.h"
#include "Scheme.h"

class Relation
{
public:
	Relation(std::string nameIn, Scheme schemeIn, std::set<Tuple> tuplesIn) : tuples(tuplesIn), name(nameIn), scheme(schemeIn) {}
	Relation() : scheme(std::vector<std::string>(0)) {}
	~Relation();
	Relation SelectValue(std::string index, std::string value);
	Relation SelectIndex(std::string index1, std::string index2);
	Relation Project(std::vector<std::string> indexNames);
	Relation Rename(std::vector<std::string> newScheme);
	Relation Join(Relation relation);
	Scheme GetScheme() { return scheme; }
	std::string ToString();
	std::set<Tuple> GetTuples() { return tuples; }
	std::string GetName() { return name; }
	void AddTuples(std::set<Tuple> tuplesIn);
	bool HasTuple(Tuple);
private:
	std::set<Tuple> tuples;
	std::string name;
	Scheme scheme;
};
#endif