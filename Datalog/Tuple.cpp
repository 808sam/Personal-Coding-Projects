#include "Tuple.h"


Tuple::~Tuple()
{
}

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

bool Tuple::operator<(Tuple const& tuple) const 
{
	return values < tuple.GetValues();
}


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