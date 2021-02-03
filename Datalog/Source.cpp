#include <fstream>
#include <iostream>
#include "Interpreter.h"

using namespace std;

int main(int argc, char** argv)
{
	//setup
	ifstream inFile;
	inFile.open(argv[1]);
	Scanner myScanner;
	myScanner.Scan(inFile);
	DatalogProgram myParser;
	myParser.Parse(myScanner.GetTokens());

	Interpreter interpreter(myParser);
	cout << interpreter.Run();

	inFile.close();
	return 0;
}   