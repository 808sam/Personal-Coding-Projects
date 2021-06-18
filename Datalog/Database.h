#ifndef DATABASE_H
#define DATABASE_H
#include "Relation.h"
#include <map>
#include <string>
#include <vector>
#include "Predicate.h"

//stores all relations in a map
class Database
{
public:
	//creates a relation for each scheme and populates the relation using facts
	Database(std::vector<Predicate> schemes, std::vector<Predicate> facts);
	~Database();
	//returns the relation with a specific name
	Relation GetRelation(std::string name);
	//adds all tuples to the relation given by the name
	void AddToRelation(std::string name, std::set<Tuple> tuples);
private:
	std::map<std::string, Relation> relationMap;
};
#endif