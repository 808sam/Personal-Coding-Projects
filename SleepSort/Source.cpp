#include <iostream>
#include <vector>
#include <ctime>
#include <chrono>

//O(n*d) sorting algorithm
//d is average value stored in vector
//A terrible algorithm for sorting anything but a realy long list of low integer numbers
using namespace std;

int main()
{
	vector<int> testList = { 3, 1, 2, 6, 3, 4, 2, 9, 7, 4, 2, 6, 2, 5, 2, 3, 6, 1, 3, 5, 1, 3, 2, 6, 4, 8, 2, 9, 1, 3, 3, 4, 5, 9, 3, 5 };

	vector<int> preList = testList;
	vector<int> tempList;
	vector<int> sortList;

	auto startTime = std::chrono::high_resolution_clock::now();

	//copy O(n)
	for (size_t i = 0; i < preList.size(); ++i)
		{
			tempList.push_back(preList.at(i));
		}

	//sleep sort O(n)
	//n * avg(list)
	//not true sleep sort, but as good as I knew how to do
	//instead of spinning off sleep commands, subtracts 1 from each number until it hit's 0
	while (preList.size() > 0)
		{
			for (size_t i = 0; i < tempList.size(); ++i)
			{
				tempList.at(i) -= 1;
				if (tempList.at(i) <= 0)
				{
					sortList.push_back(preList.at(i));
					tempList.erase(tempList.begin() + i);
					preList.erase(preList.begin() + i);
					--i;
				}
			}
		}


	auto endTime= std::chrono::high_resolution_clock::now();
	auto duration = std::chrono::duration_cast<std::chrono::nanoseconds>(endTime - startTime).count();
	cout << "TIME: " << duration << endl;

	//print, Still O(n)!
	for (size_t i = 0; i < sortList.size(); ++i)
	{
		cout << sortList.at(i) << " ";
	}
	cout << endl;


	//bubblesort

	preList = testList;

	startTime = std::chrono::high_resolution_clock::now();

	bool isSorted = false;
	int tempVar;

	while (!isSorted)
	{
		isSorted = true;
		for (size_t i = 0; i < preList.size() - 1; ++i)
		{
			if (preList.at(i) > preList.at(i + 1))
			{
				tempVar = preList.at(i);
				preList.at(i) = preList.at(i + 1);
				preList.at(i + 1) = tempVar;
				isSorted = false;
			}
		}
	}



	endTime = std::chrono::high_resolution_clock::now();
	duration = std::chrono::duration_cast<std::chrono::nanoseconds>(endTime - startTime).count();

	cout << "TIME: " << duration << endl;
	for (size_t i = 0; i < sortList.size(); ++i)
	{
		cout << preList.at(i) << " ";
	}
}