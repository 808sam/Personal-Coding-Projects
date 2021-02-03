#include "Predicate.h"



Predicate::Predicate(PredicateType typeIn, std::string IdIn, std::vector<Parameter> parametersIn) : type(typeIn), name(IdIn), parameters(parametersIn) {}



Predicate::~Predicate()
{
}

std::string Predicate::ToString()
{
	std::string returnString = name + "(";
	for (size_t i = 0; i < parameters.size(); ++i)
	{
		returnString += parameters.at(i).ToString();
		if (i != parameters.size() - 1) returnString += ",";
		else returnString += ")";
	}

	switch (type)
	{
	case PRED_FACT:
		returnString += ".";
		break;
	case PRED_QUERY:
		returnString += "?";
		break;
	default:
		break;
	}

	return returnString;
}

std::vector <std::string> Predicate::GetValues()
{
	std::vector<std::string> values;
	for (Parameter param : parameters)
	{
		values.push_back(param.GetData());
	}
	return values;
}