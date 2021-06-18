#include "Database.h"

//creates a relation for each scheme and populates the relation using facts
Database::Database(std::vector<Predicate> schemes, std::vector<Predicate> facts)
{
	while (schemes.size() != 0)
	{
		//get name
		std::string currName = schemes.at(0).GetName();

		//get scheme
		std::vector<std::string> schemeParams;
		for (size_t i = 0; i < schemes.at(0).GetParameters().size(); ++i)
		{
			schemeParams.push_back(schemes.at(0).GetParameters().at(i).GetData());
		}
		Scheme scheme(schemeParams);

		//get Tuples
		std::set<Tuple> tuples;
		for (size_t i = 0; i < facts.size(); ++i)
		{
			if (facts.at(i).GetName() == currName)
			{
				std::vector<std::string> values;
				for (Parameter param : facts.at(i).GetParameters())
				{
					values.push_back(param.GetData());
				}
				tuples.emplace(Tuple(values));
			}
		}

		//add to map
		relationMap.emplace(currName, Relation(currName, scheme, tuples));

		schemes.erase(schemes.begin());
	}
}


Database::~Database()
{
}
//returns the relation with a specific name
Relation Database::GetRelation(std::string name)
{
	return relationMap.at(name);
}

//adds all tuples to the relation given by the name
void Database::AddToRelation(std::string name, std::set<Tuple> tuples)
{
	relationMap.at(name).AddTuples(tuples);
}
