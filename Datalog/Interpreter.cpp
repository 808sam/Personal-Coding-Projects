#include "Interpreter.h"

Interpreter::~Interpreter()
{
}

Relation Interpreter::InterpretQuery(Predicate query, Relation relation = Relation())
{
	//Select
	if (relation.GetName() == "") relation = database.GetRelation(query.GetName());
	for (size_t i = 0; i < relation.GetScheme().GetNames().size(); ++i)
	{
		if (query.at(i).GetType() == STR)
		{
			relation = relation.SelectValue(relation.GetScheme().GetNames().at(i), query.at(i).GetData());
		}
		else if (query.at(i).GetType() == PARAM_ID)
		{
			for (size_t j = i + 1; j < query.GetParameters().size(); ++j)
			{
				if ((query.at(j).GetType() == PARAM_ID) && (query.at(j).GetData() == query.at(i).GetData()))
				{
					relation = relation.SelectIndex(relation.GetScheme().GetNames().at(i), relation.GetScheme().GetNames().at(j));
				}
			}
		}
	}

	//fixme need project in future labs


	//rename
	std::vector<std::string> newScheme;
	for (size_t i = 0; i < query.GetParameters().size(); ++i) newScheme.push_back(query.GetParameters().at(i).GetData());
	relation = relation.Rename(newScheme);

	return relation;
}

std::string Interpreter::Run()
{
	std::string outString = "";
	outString += RulesEvalToString();
	outString += QueriesEvalToString();

	return outString;
}

std::string Interpreter::QueriesEvalToString()
{
	std::string outString = "Query Evaluation\n";
	for (Predicate query : dataProg.GetQueries())
	{
		Relation result = InterpretQuery(query);
		outString += query.ToString();
		if (result.GetTuples().empty()) outString += " No\n";
		else
		{
			//get all iDs
			std::vector<std::string> iDs;
			for (size_t i = 0; i < query.GetParameters().size(); ++i)
			{
				if (query.GetParameters().at(i).GetType() == PARAM_ID)
				{
					bool shouldAdd = true;
					for (size_t j = 0; j < i; ++j)
					{
						if (query.GetParameters().at(i).GetData() == query.GetParameters().at(j).GetData()) shouldAdd = false;
					}
					if (shouldAdd) iDs.push_back(query.GetParameters().at(i).GetData());
				}
			}

			//print matching tuples
			outString += " Yes(" + std::to_string(result.GetTuples().size()) + ")\n";
			for (Tuple tuple : result.GetTuples())
			{
				if (iDs.size() > 0) outString += "  ";
				for (size_t i = 0; i < iDs.size(); ++i)
				{
					outString += iDs.at(i) + "=";
					outString += tuple.at(result.GetScheme().GetIndex(iDs.at(i)));
					if (i != iDs.size() - 1) outString += ", ";
				}
				if (iDs.size() > 0) outString += "\n";
			}
		}
	}
	return outString;
}

std::string Interpreter::RulesEvalToString()
{
	std::string outString = "Rule Evaluation\n";
	bool isNewFact = true;
	size_t numPasses = 0;
	while (isNewFact)
	{
		++numPasses;
		isNewFact = false;
		for (Rule rule : rules)
		{
			outString += rule.ToString() + '\n';
			
			//join all relations in the rule
			Relation joinedRelation;
			for (Predicate pred : rule.GetPreds())
			{
				Relation newRelation = InterpretQuery(pred, database.GetRelation(pred.GetName()));
				joinedRelation = joinedRelation.Join(newRelation);
			}

			//project to head scheme of rule

			joinedRelation = joinedRelation.Project(rule.GetHead().GetValues());

			//print each new fact
			for (Tuple tuple : joinedRelation.GetTuples())
			{
				if (!database.GetRelation(rule.GetHead().GetName()).HasTuple(tuple))
				{
					outString += "  ";
					for (size_t i = 0; i < rule.GetHead().GetParameters().size(); ++i)
					{
						outString += database.GetRelation(rule.GetHead().GetName()).GetScheme().GetNames().at(i) + '=';
						outString += tuple.at(i);
						if (i != rule.GetHead().GetParameters().size() - 1) outString += ", ";
						else outString += "\n";
					}
					isNewFact = true;
				}
			}
			database.AddToRelation(rule.GetHead().GetName(), joinedRelation.GetTuples());
		}
	}

	outString += "\nSchemes populated after " + std::to_string(numPasses) + " passes through the Rules.\n\n";
	return outString;
}