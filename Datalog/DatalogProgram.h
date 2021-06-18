#ifndef DATLOG_PROGRAM_H
#define DATLOG_PROGRAM_H

#include <vector>
#include <string>
#include <iostream>
#include <stack>

#include "Scanner.h"
#include "Predicate.h"
#include "Rule.h"
#include "Parameter.h"


//build up data from token
//stores all schemes, facts, rules, and queries
class DatalogProgram
{
public:
	DatalogProgram();
	~DatalogProgram();
	//goes through tokens vector determining rules, schemes, facts, and queries
	//also will build up the domain of ID's seen
	bool Parse(std::vector<Token*>);
	//prints out the Schemes, Facts, Rules, and Queries
	std::string ToString();

	//getters
	std::vector<Predicate> GetSchemes() { return schemes; }
	std::vector<Predicate> GetFacts() { return facts; }
	std::vector<Rule> GetRules() { return rules; }
	std::vector<Predicate> GetQueries() { return queries; }
	std::vector<std::string> GetDomain() { return domain; }
private:
	std::vector<Predicate> schemes;
	std::vector<Predicate> facts;
	std::vector<Rule> rules;
	std::vector<Predicate> queries;
	std::vector<std::string> domain;

	std::vector<Token*>::iterator currToken;


	//used for checking simple single character tokens with set values
	std::string Match(TokenType);
	//checks if a string is in the Domain, if not it is added
	void CheckDomain(std::string);

	//functions for recursive parse
	//based on Datalog grammer
	void SchemeList();
	void FactList();
	void RuleList();
	void QueryList();

	void Scheme();
	void Fact();
	void RuleParse();
	void Query();

	Predicate HeadPredicate(PredicateType);
	Predicate PredicateParse(PredicateType);

	std::vector<Predicate> PredicateList(PredicateType);
	std::vector<Parameter> ParameterList();
	std::vector<Parameter> StringList();
	std::vector<Parameter> IdList();

	Parameter ParameterParse();
	std::string Expression();
	std::string Operator();
};
#endif