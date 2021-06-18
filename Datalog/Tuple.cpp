#include "Tuple.h"


Tuple::~Tuple()
{
}

//print each element in the tuple as a comma separated list in parenthesis
std::string Tuple::ToString()
{
	std::string outString = "";
	outString += '(';
	for (size_t i = 0; i < values.size(); ++i)
	{
		outString += values.at(i);
		if (i != values.size() - 1) outString += ", ";
	}
	outString += ')';
	return outString;
}

//uses vector comparisons to define < for tuple
//defined so computer can know how to add tuples to a set
bool Tuple::operator<(Tuple const& tuple) const 
{
	return values < tuple.GetValues();
}

//takes this tuples scheme, another tuples and it's scheme
//returns true if both tuples have the same value everywhere the schemes match
bool Tuple::CanJoin(std::vector<std::string> myScheme, Tuple tupleIn, std::vector<std::string> otherScheme)
{
	for (size_t i = 0; i < myScheme.size(); ++i)
	{
		for (size_t j = 0; j < otherScheme.size(); ++j)
		{
			if (myScheme.at(i) == otherScheme.at(j))
			{
				if (values.at(i) != tupleIn.GetValues().at(j))
				{
					return false;
				}
			}
		}
	}
	return true;
}

//Joins 2 tuples together based on the given scheme
//no check if values are the same, first tuple will overwright second
Tuple Tuple::Join(std::vector<std::string> myScheme, Tuple tupleIn, std::vector<std::string> otherScheme)
{
	std::vector<std::string> newValues(values);
	for (size_t i = 0; i < otherScheme.size(); ++i)
	{
		bool shouldAdd = true;
		for (std::string name : myScheme)
		{
			if (name == otherScheme.at(i)) shouldAdd = false;
		}
		if (shouldAdd) newValues.push_back(tupleIn.GetValues().at(i));
	}

	return Tuple(newValues);
}