#include "Rule.h"




Rule::~Rule()
{
}

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