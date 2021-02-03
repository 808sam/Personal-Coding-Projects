#ifndef SCHEME_H
#define SCHEME_H
#include <vector>
#include <string>
class Scheme
{
public:
	Scheme(std::vector<std::string> namesIn) : names(namesIn) {}
	~Scheme();
	size_t GetIndex(std::string name);
	std::vector<std::string> GetNames() { return names; }
private:
	std::vector<std::string> names;
};
#endif