#include <iostream>
#include <sstream>

using namespace std;

enum place {LEFT, MIDDLE, RIGHT};
ostream& operator<<(ostream& out, place in)
{
	switch (in)
	{
	case LEFT:
		out << "LEFT";
		break;
	case MIDDLE:
		out << "MIDDLE";
		break;
	case RIGHT:
		out << "RIGHT";
		break;
	}
	return out;
}
string moveStack(size_t num, place start = LEFT, place finish = RIGHT, place other = MIDDLE)
{
	ostringstream out;
	if (num == 1){ 
		out << "MOVE 1 FROM " << start << " TO " << finish << endl;
		return out.str();
	}
	out << moveStack(num - 1, start, other, finish);
	out << "MOVE " << num << " FROM " << start << " TO " << finish << endl;
	out << moveStack(num - 1, other, finish, start);
	return out.str();
}


int main()
{
	cout << moveStack(13);
	system("pause");
	return 0;
}