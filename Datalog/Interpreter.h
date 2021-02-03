#ifndef INTERPRETER_H
#define INTERPRETER_H
#include "Database.h"
#include "DatalogProgram.h"
class Interpreter
{
public:
	Interpreter(DatalogProgram datLog) : rules(datLog.GetRules()), dataProg(datLog), database(datLog.GetSchemes(), datLog.GetFacts()) {}
	~Interpreter();
	std::string Run();
private:
	std::vector<Rule> rules;
	DatalogProgram dataProg;
	Database database;
	Relation InterpretQuery(Predicate, Relation);
	std::string QueriesEvalToString();
	std::string RulesEvalToString();
};

#endif