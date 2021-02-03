#ifndef SCANNER_H
#define SCANNER_H

#include <string>
#include <vector>
#include <fstream>

enum TokenType { COMMA, PERIOD, Q_MARK, LEFT_PAREN, RIGHT_PAREN, COLON, COLON_DASH, MULTIPLY, ADD, SCHEMES, FACTS, RULES, QUERIES, ID, STRING, COMMENT, UNDEFINED, END_OF_FILE };
const std::vector<std::string> TOKEN_IDS = { "COMMA", "PERIOD", "Q_MARK", "LEFT_PAREN", "RIGHT_PAREN", "COLON","COLON_DASH", "MULTIPLY", "ADD", "SCHEMES", "FACTS", "RULES", "QUERIES", "ID", "STRING", "COMMENT", "UNDEFINED", "EOF" };
const std::vector<std::string> KEYWORDS = { "SCHEMES", "FACTS", "RULES", "QUERIES" };

struct Token
{
	Token(TokenType typeIn, std::string valueIn, size_t lineIn) : type(typeIn), value(valueIn), line(lineIn) {}
	TokenType type;
	std::string value;
	size_t line;
	std::string ToString()
	{
		return "(" + TOKEN_IDS.at(type) + ",\"" + value + "\"," + std::to_string(line) + ")";
	}
};


class Scanner
{
public:
	Scanner();
	~Scanner();
	void Scan(std::ifstream&);
	std::vector<Token*>& GetTokens();
	std::string ToString();

private:
	std::vector<Token*> tokens;

	void ScanString(std::ifstream&, size_t&);
	void ScanID(std::ifstream&, size_t);
	void ScanComment(std::ifstream&, size_t&);
};


#endif