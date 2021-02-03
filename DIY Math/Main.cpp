#include <iostream>
#include "Matrix.h"
#include <vector>

using namespace std;

vector<int> PolyMult(vector<int> a, vector<int> b)
{
	vector<int> product;
	for (size_t i = 0; i < a.size() + b.size() - 1; ++i)
	{
		product.push_back(0);
	}
	for (size_t i = 0; i < a.size(); ++i)
	{
		for (size_t j = 0; j < b.size(); ++j)
		{
			product.at(i + j) += a.at(i) * b.at(j);
		}
	}
	return product;
}
/*bool PolyDiv(vector<int>& numerator, vector<int> denominator)
{
	bool isDivisible = false;
	for (size_t i = 0; i < numerator.size() - denominator.size(); ++i)
	{

	}
}*/

int main()
{
	vector<int> a = { 1, -1 };
	vector<int> b = { 1, 1 };
	cout << a.at(0) << endl;
	vector<int> c = PolyMult(a, b);
	for (int i = 0; i < c.size(); ++i)
	{
		cout << c.at(i) << " ";
	}
	cout << endl;
	system("pause");
	return 0;
}