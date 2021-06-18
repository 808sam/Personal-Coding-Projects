#include "Scheme.h"


Scheme::~Scheme()
{
}

//takes the name of an element in the scheme and returns that elements index
size_t Scheme::GetIndex(std::string name)
{
	for (size_t i = 0; i < names.size(); ++i)
	{
		if (names.at(i) == name) return i;
	}
	return -1;
}