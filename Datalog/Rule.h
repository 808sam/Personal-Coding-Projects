#ifndef RULE_H
#define RULE_H

#include "Predicate.h"
#include <vector>
#include <string>

//holds which predicates allow for creation of tuples
//headPred(<params>) :- pred1(<params>), pred2(<params>)
//if tuples for all body preds, rule says can create tuple for headPred
class Rule
{
public:
	Rule(Predicate headIn, std::vector<Predicate> listIn) : headPredicate(headIn), predicateList(listIn) {}
	~Rule();
	
	//prints head predicate to string, ":-", then all predicates in the rules list
	std::string ToString();

	//getters
	Predicate GetHead() { return headPredicate; };
	std::vector<Predicate> GetPreds() { return predicateList; }
private:
	Predicate headPredicate;
	std::vector<Predicate> predicateList;
};

#endif