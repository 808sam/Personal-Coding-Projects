//Scans the input file and breaks it up into separate tokens

#ifndef SCANNER_H
#define SCANNER_H

#include <string>
#include <vector>
#include <fstream>

enum TokenType { COMMA, PERIOD, Q_MARK, LEFT_PAREN, RIGHT_PAREN, COLON, COLON_DASH, MULTIPLY, ADD, SCHEMES, FACTS, RULES, QUERIES, ID, STRING, COMMENT, UNDEFINED, END_OF_FILE };
const std::vector<std::string> TOKEN_IDS = { "COMMA", "PERIOD", "Q_MARK", "LEFT_PAREN", "RIGHT_PAREN", "COLON","COLON_DASH", "MULTIPLY", "ADD", "SCHEMES", "FACTS", "RULES", "QUERIES", "ID", "STRING", "COMMENT", "UNDEFINED", "EOF" };
const std::vector<std::string> KEYWORDS = { "SCHEMES", "FACTS", "RULES", "QUERIES" };

//holds the info for a single token including line number, token type, and token value
struct Token
{
	Token(TokenType typeIn, std::string valueIn, size_t lineIn) : type(typeIn), value(valueIn), line(lineIn) {}
	TokenType type;
	std::string value;
	size_t line;
	//prints out values for Token
	std::string ToString()
	{
		return "(" + TOKEN_IDS.at(type) + ",\"" + value + "\"," + std::to_string(line) + ")";
	}
};

//breaks up input text into tokens
class Scanner
{
public:
	Scanner();
	~Scanner();

	//loops through input file determining what each token is
	void Scan(std::ifstream&);

	//Getter
	std::vector<Token*>& GetTokens();

	//Prints out each token
	std::string ToString();

private:
	//holds the tokens found by Scan()
	std::vector<Token*> tokens;

	//All 3 scan functions below take the input file and the current line number
	//scans a string token and pushes it onto tokens vector
	void ScanString(std::ifstream&, size_t&);

	//scans a ID token and pushes it onto tokens vector
	//will also check for keywods Schemes, Facts, Rules, and Queries
	void ScanID(std::ifstream&, size_t);
	
	//scans a Comment token and pushes it onto tokens vector
	void ScanComment(std::ifstream&, size_t&);
};


#endif