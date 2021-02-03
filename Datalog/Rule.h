#ifndef RULE_H
#define RULE_H

#include "Predicate.h"
#include <vector>
#include <string>

class Rule
{
public:
	Rule(Predicate headIn, std::vector<Predicate> listIn) : headPredicate(headIn), predicateList(listIn) {}
	~Rule();
	std::string ToString();
	Predicate GetHead() { return headPredicate; };
	std::vector<Predicate> GetPreds() { return predicateList; }
private:
	Predicate headPredicate;
	std::vector<Predicate> predicateList;
};

#endif