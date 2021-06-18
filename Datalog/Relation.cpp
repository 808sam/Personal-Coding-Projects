#include "Relation.h"

Relation::~Relation()
{
}

//returns a relation with the same scheme put only with tuples with given value at index
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

//returns a relation with the same scheme put only with tuples with the same value at the 2 indecies
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

//retuns relation with only the specified collumns of the scheme
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

//returns a relation with renames scheme values
Relation Relation::Rename(std::vector<std::string> newScheme)
{
	return Relation(name, newScheme, tuples);
}

//returns a relation that's the join of this relation and parameter relation
//will compare tuples for joining based on where the 2 schemes of the relations overlap
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

//returns data of every tuple in relation
std::string Relation::ToString()
{
	std::string returnString = name;
	for (Tuple tuple : tuples)
	{
		returnString += tuple.ToString();
	}
	return returnString;
}

//adds tuples to the relation
void Relation::AddTuples(std::set<Tuple> tuplesIn)
{
	for (Tuple tuple : tuplesIn)
	{
		tuples.emplace(tuple);
	}
}

//checks if given tuple is in the relation set of tuples
bool Relation::HasTuple(Tuple tuple)
{
	return tuples.find(tuple) != tuples.end();
}