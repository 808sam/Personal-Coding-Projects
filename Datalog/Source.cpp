//created by Samuel Owens for CS 235 class @ BYU
//working Datalog Interpreter
//put the file you want as input as a parameter, prints to console

#include <fstream>
#include <iostream>
#include "Interpreter.h"

using namespace std;

int main(int argc, char** argv)
{
	//get input file
	ifstream inFile;
	inFile.open(argv[1]);

	//scan for tokens
	Scanner myScanner;
	myScanner.Scan(inFile);

	//parse for schemes/facts/rules/queries
	DatalogProgram myParser;
	myParser.Parse(myScanner.GetTokens());

	//use rules to populate relations and answer queries
	Interpreter interpreter(myParser);
	cout << interpreter.Run();

	inFile.close();
	return 0;
}   