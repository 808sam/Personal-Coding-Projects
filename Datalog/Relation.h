#ifndef RELATION_H
#define RELATION_H
#include <vector>
#include <string>
#include <set>
#include "Tuple.h"
#include "Scheme.h"

//holds a set of tuples to form the "facts" of our database
class Relation
{
public:
	//creates relation with given name, uses scheme for header, and tuples for starting values
	Relation(std::string nameIn, Scheme schemeIn, std::set<Tuple> tuplesIn) : tuples(tuplesIn), name(nameIn), scheme(schemeIn) {}
	//creates empty relation (default constructor)
	Relation() : scheme(std::vector<std::string>(0)) {}
	~Relation();
	
	//returns a relation with the same scheme put only with tuples with given value at index
	Relation SelectValue(std::string index, std::string value);
	
	//returns a relation with the same scheme put only with tuples with the same value at the 2 indecies
	Relation SelectIndex(std::string index1, std::string index2);
	
	//retuns relation with only the specified collumns of the scheme
	Relation Project(std::vector<std::string> indexNames);
	
	//returns a relation with renames scheme values
	Relation Rename(std::vector<std::string> newScheme);
	
	//returns a relation that's the join of this relation and parameter relation
	//will compare tuples for joining based on where the 2 schemes of the relations overlap
	Relation Join(Relation relation);
	
	//returns data of every tuple in relation
	std::string ToString();
	
	//getters
	Scheme GetScheme() { return scheme; }
	std::set<Tuple> GetTuples() { return tuples; }
	std::string GetName() { return name; }

	//adds tuples to the relation
	void AddTuples(std::set<Tuple> tuplesIn);

	//checks if given tuple is in the relation set of tuples
	bool HasTuple(Tuple);
private:
	std::set<Tuple> tuples;
	std::string name;
	Scheme scheme;
};
#endif