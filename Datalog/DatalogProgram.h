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

class DatalogProgram
{
public:
	DatalogProgram();
	~DatalogProgram();
	bool Parse(std::vector<Token*>);
	std::string ToString();

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


	//functions for recursive parse
	std::string Match(TokenType);
	void CheckDomain(std::string);

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