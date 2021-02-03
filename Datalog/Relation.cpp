#include "Relation.h"

Relation::~Relation()
{
}

Relation Relation::SelectValue(std::string indexName, std::string value)
{
	std::set<Tuple> subsetTuples;

	//find index value
	size_t indexVal;
	for (indexVal = 0; indexVal < scheme.GetNames().size(); ++indexVal)
	{
		if (indexName == scheme.GetNames().at(indexVal)) break;
	}


	for (Tuple tuple : tuples)
	{
		if (tuple.at(indexVal) == value) subsetTuples.emplace(tuple);
	}

	return Relation(name, scheme, subsetTuples);
}

Relation Relation::SelectIndex(std::string index1, std::string index2)
{
	std::set<Tuple> subsetTuples;

	//find index value
	size_t indexVal1;
	for (indexVal1 = 0; indexVal1 < scheme.GetNames().size(); ++indexVal1)
	{
		if (index1 == scheme.GetNames().at(indexVal1)) break;
	}
	size_t indexVal2;
	for (indexVal2 = 0; indexVal2 < scheme.GetNames().size(); ++indexVal2)
	{
		if (index2 == scheme.GetNames().at(indexVal2)) break;
	}


	for (Tuple tuple : tuples)
	{
		if (tuple.at(indexVal1) == tuple.at(indexVal2)) subsetTuples.emplace(tuple);
	}

	return Relation(name, scheme, subsetTuples);
}

Relation Relation::Project(std::vector<std::string> indexNames)
{
	Scheme newScheme(indexNames);
	std::set<Tuple> newTuples;

	//copy needed data
	for (Tuple tuple : tuples)
	{
		std::vector<std::string> values;
		for (std::string name : indexNames)
		{
			for (size_t i = 0; i < scheme.GetNames().size(); ++i)
			{
				if (name == scheme.GetNames().at(i)) values.push_back(tuple.at(i));
			}
		}
		newTuples.emplace(Tuple(values));
	}

	return Relation(name, newScheme, newTuples);
}

Relation Relation::Rename(std::vector<std::string> newScheme)
{
	return Relation(name, newScheme, tuples);
}

std::string Relation::ToString()
{
	std::string returnString = name;
	for (Tuple tuple : tuples)
	{
		returnString += tuple.ToString();
	}
	return returnString;
}

Relation Relation::Join(Relation relation)
{
	//make new scheme
	std::vector<std::string> newNames = scheme.GetNames();
	for (std::string name : relation.GetScheme().GetNames())
	{
		bool shouldAdd = true;
		for (std::string existingName : newNames)
		{
			if (existingName == name) shouldAdd = false;
		}
		if (shouldAdd) newNames.push_back(name);
	}
	Scheme newScheme(newNames);

	//make tuples
	std::set<Tuple> newTuples;
	if (scheme.GetNames().size() != 0)
	{
		for (Tuple t1 : tuples)
		{
			for (Tuple t2 : relation.GetTuples())
			{
				if (t1.CanJoin(scheme.GetNames(), t2, relation.GetScheme().GetNames()))
				{
					newTuples.emplace(t1.Join(scheme.GetNames(), t2, relation.GetScheme().GetNames()));
				}
			}
		}
	} else newTuples = relation.GetTuples();

	return Relation(name + relation.GetName(), newScheme, newTuples);
}

bool Relation::HasTuple(Tuple tuple)
{
	return tuples.find(tuple) != tuples.end();
}

void Relation::AddTuples(std::set<Tuple> tuplesIn)
{
	for (Tuple tuple : tuplesIn)
	{
		tuples.emplace(tuple);
	}
}