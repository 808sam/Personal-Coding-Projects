#ifndef DATABASE_H
#define DATABASE_H
#include "Relation.h"
#include <map>
#include <string>
#include <vector>
#include "Predicate.h"

class Database
{
public:
	Database(std::vector<Predicate> shemes, std::vector<Predicate> facts);
	~Database();
	Relation GetRelation(std::string name);
	void AddToRelation(std::string, std::set<Tuple>);
private:
	std::map<std::string, Relation> relationMap;
};
#endif