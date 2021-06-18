#ifndef INTERPRETER_H
#define INTERPRETER_H
#include "Database.h"
#include "DatalogProgram.h"

//evaluates datalog rules and answers queries
class Interpreter
{
public:
	Interpreter(DatalogProgram datLog) : rules(datLog.GetRules()), dataProg(datLog), database(datLog.GetSchemes(), datLog.GetFacts()) {}
	~Interpreter();
	//evaluated all rules and queries, returning a string with the results
	std::string Run();
private:
	std::vector<Rule> rules;
	DatalogProgram dataProg;
	Database database;
	//finds which facts answer a query
	Relation InterpretQuery(Predicate, Relation);
	//evaluates all queries, returning a string with the results
	std::string QueriesEvalToString();
	//evaluates all rules, returning a string with the results
	std::string RulesEvalToString();
};

#endif