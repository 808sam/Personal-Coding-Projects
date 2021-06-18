#ifndef SCHEME_H
#define SCHEME_H
#include <vector>
#include <string>

//the "blueprint" for which tuples the program can use
//schemeName(param1,param2...,paramN)
class Scheme
{
public:
	Scheme(std::vector<std::string> namesIn) : names(namesIn) {}
	~Scheme();
	
	//takes the name of an element in the scheme and returns that elements index
	size_t GetIndex(std::string name);

	//getter
	std::vector<std::string> GetNames() { return names; }
private:
	std::vector<std::string> names;
};
#endif