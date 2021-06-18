#include "DatalogProgram.h"



DatalogProgram::DatalogProgram()
{
}
DatalogProgram::~DatalogProgram()
{
}

//goes through tokens vector determining rules, schemes, facts, and queries
//also will build up the domain of ID's seen
//starts recurrsive calls based on Datalog Grammer
bool DatalogProgram::Parse(std::vector<Token*> tokens)
{
	currToken = tokens.begin();

	try
	{
		Match(SCHEMES); Match(COLON); Scheme(); SchemeList();
		Match(FACTS); Match(COLON); FactList();
		Match(RULES); Match(COLON); RuleList();
		Match(QUERIES); Match(COLON); Query(); QueryList();

		if ((*currToken)->type != END_OF_FILE) throw currToken;
		return true;
	}
	catch (std::vector<Token*>::iterator e)
	{
		std::cout << "Failure!" << std::endl;
		std::cout << "  " << (*e)->ToString() << std::endl;
		return false;
	}
}

//prints out the Schemes, Facts, Rules, and Queries
std::string DatalogProgram::ToString()
{
	std::string outString = "Schemes(" + std::to_string(schemes.size()) + "):\n";
	for (Predicate scheme : schemes)
	{
		outString += "  " + scheme.ToString() + "\n";
	}

	outString += "Facts(" + std::to_string(facts.size()) + "):\n";
	for (Predicate fact : facts)
	{
		outString += "  " + fact.ToString() + "\n";
	}

	outString += "Rules(" + std::to_string(rules.size()) + "):\n";
	for (Rule rule : rules)
	{
		outString += "  " + rule.ToString() + "\n";
	}

	outString += "Queries(" + std::to_string(queries.size()) + "):\n";
	for (Predicate query : queries)
	{
		outString += "  " + query.ToString() + "\n";
	}

	outString += "Domain(" + std::to_string(domain.size()) + "):\n";
	for (std::string word : domain)
	{
		outString += "  " + word + "\n";
	}

	return outString;
}


//used for checking simple single character tokens with set values
std::string DatalogProgram::Match(TokenType type)
{
	std::string value;
	if ((*currToken)->type == type)
	{
		value = (*currToken)->value;
		++currToken;
	}
	else throw currToken;
	return value;
}

//checks if a string is in the Domain, if not it is added
void DatalogProgram::CheckDomain(std::string str) {
	for (size_t i = 0; i < domain.size(); ++i)
	{
		if (domain.at(i) > str)
		{
			domain.insert(domain.begin() + i, str);
			return;
		}
		else if (domain.at(i) == str) return;
	}
	domain.push_back(str);
}

//all following functions implement the grammer we were given
//if you want to, the grammer shouldn't be too difficult to rederive, just look at the function calls
//left as an exersize for the reader XD
void DatalogProgram::SchemeList()
{
	if ((*currToken)->type == ID)
	{
		Scheme(); SchemeList();
	}
}
void DatalogProgram::FactList()
{
	if ((*currToken)->type == ID)
	{
		Fact(); FactList();
	}
}
void DatalogProgram::RuleList()
{
	if ((*currToken)->type == ID)
	{
		RuleParse(); RuleList();
	}
}
void DatalogProgram::QueryList()
{
	if ((*currToken)->type == ID)
	{
		Query(); QueryList();
	}
}
void DatalogProgram::Scheme()
{
	std::string schemeId = Match(ID);
	Match(LEFT_PAREN);
	Parameter firstParam = Parameter(PARAM_ID, Match(ID));
	std::vector<Parameter> paramList = IdList();
	Match(RIGHT_PAREN);

	paramList.insert(paramList.begin(), firstParam);
	schemes.push_back(Predicate(PRED_SCHEME, schemeId, paramList));
}
void DatalogProgram::Fact()
{
	std::string factId = Match(ID);
	Match(LEFT_PAREN);
	Parameter firstParam = Parameter(STR, Match(STRING));
	std::vector<Parameter> paramList = StringList();
	paramList.insert(paramList.begin(), firstParam);

	for (Parameter param : paramList)
	{
		CheckDomain(param.ToString());
	}

	Match(RIGHT_PAREN);
	Match(PERIOD);

	facts.push_back(Predicate(PRED_FACT, factId, paramList));
}
void DatalogProgram::RuleParse()
{
	Predicate headPred = HeadPredicate(PRED_RULE);
	Match(COLON_DASH);
	Predicate firstPred = PredicateParse(PRED_RULE);
	std::vector<Predicate> predList = PredicateList(PRED_RULE);
	Match(PERIOD);

	predList.insert(predList.begin(), firstPred);
	rules.push_back(Rule(headPred, predList));
}
void DatalogProgram::Query()
{
	queries.push_back(PredicateParse(PRED_QUERY));
	Match(Q_MARK);
}
Predicate DatalogProgram::HeadPredicate(PredicateType predType)
{
	std::string predId = Match(ID);
	Match(LEFT_PAREN);
	Parameter firstParam = Parameter(PARAM_ID, Match(ID));
	std::vector<Parameter> predParams = IdList();
	predParams.insert(predParams.begin(), firstParam);
	Match(RIGHT_PAREN);
	return Predicate(predType, predId, predParams);
}
Predicate DatalogProgram::PredicateParse(PredicateType predType)
{
	std::string predId = Match(ID);
	Match(LEFT_PAREN);
	Parameter firstParam = ParameterParse();
	std::vector<Parameter> paramList = ParameterList();
	Match(RIGHT_PAREN);
	paramList.insert(paramList.begin(), firstParam);
	return Predicate(predType, predId, paramList);
}
std::vector<Predicate> DatalogProgram::PredicateList(PredicateType predType)
{
	std::vector<Predicate> outVect;
	if ((*currToken)->type == COMMA)
	{
		Match(COMMA);
		Predicate newPred = PredicateParse(predType);
		outVect = PredicateList(predType);
		outVect.insert(outVect.begin(), newPred);
	}
	return outVect;
}
std::vector<Parameter> DatalogProgram::ParameterList()
{
	std::vector<Parameter> outVect;
	if ((*currToken)->type == COMMA)
	{
		Match(COMMA);
		Parameter newParam = ParameterParse();
		outVect = ParameterList();
		outVect.insert(outVect.begin(), newParam);
	}
	return outVect;
}
std::vector<Parameter> DatalogProgram::StringList()
{
	std::vector<Parameter> outVect;
	if ((*currToken)->type == COMMA)
	{
		Match(COMMA);

		Parameter newParam = Parameter(STR, (*currToken)->value);
		Match(STRING);

		outVect = StringList();
		outVect.insert(outVect.begin(), newParam);
	}
	return outVect;
}
std::vector<Parameter> DatalogProgram::IdList()
{
	std::vector<Parameter> outVect;
	std::string idVal;
	if ((*currToken)->type == COMMA)
	{
		Match(COMMA);
		idVal = Match(ID);
		outVect = IdList();

		outVect.insert(outVect.begin(), Parameter(PARAM_ID, idVal));
	}
	return outVect;
}
Parameter DatalogProgram::ParameterParse()
{
	if ((*currToken)->type == STRING)
	{
		return Parameter(STR, Match(STRING));
	}
	else if ((*currToken)->type == ID)
	{
		return Parameter(PARAM_ID, Match(ID));
	}
	else if ((*currToken)->type == LEFT_PAREN)
	{
		return Parameter(EXP, Expression());
	}
	else throw currToken;
}

//final datalog program doesn't actually use Expressions for anything
//Expression and Operator were just added to be a challenge on one of the Labs
std::string DatalogProgram::Expression()
{
	Match(LEFT_PAREN);
	std::string outString = "(" + ParameterParse().ToString();
	outString += Operator();
	outString += ParameterParse().ToString() + ")";
	Match(RIGHT_PAREN);

	return outString;
}
//parse for + or * operator
std::string DatalogProgram::Operator()
{
	if ((*currToken)->type == ADD)
	{
		++currToken;
		return "+";
	}
	else if ((*currToken)->type == MULTIPLY)
	{
		++currToken;
		return "*";
	}
	else throw currToken;
}