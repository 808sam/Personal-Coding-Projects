#include "Rule.h"




Rule::~Rule()
{
}

//prints head predicate to string, ":-", then all predicates in the rules list
std::string Rule::ToString()
{
	std::string outString = headPredicate.ToString();
	outString += " :- ";
	for (Predicate pred : predicateList)
	{
		outString += pred.ToString() + ",";
	}
	outString.replace(outString.size() - 1, 1, ".");
	return outString;
}