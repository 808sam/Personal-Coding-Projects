#include "Scanner.h"

Scanner::Scanner() {}
Scanner::~Scanner()
{
	for (Token* token : tokens)
	{
		delete token;
	}
}

void Scanner::Scan(std::ifstream& in)
{
	char currChar;
	size_t currLine = 1;

	do
	{
		currChar = in.get();

		if (currChar == ',') tokens.push_back(new Token(COMMA, ",", currLine));
		else if (currChar == '.') tokens.push_back(new Token(PERIOD, ".", currLine));
		else if (currChar == '?') tokens.push_back(new Token(Q_MARK, "?", currLine));
		else if (currChar == '(') tokens.push_back(new Token(LEFT_PAREN, "(", currLine));
		else if (currChar == ')') tokens.push_back(new Token(RIGHT_PAREN, ")", currLine));
		else if (currChar == ':')
		{
			if (in.peek() == '-')
			{
				in.get();
				tokens.push_back(new Token(COLON_DASH, ":-", currLine));
			}
			else tokens.push_back(new Token(COLON, ":", currLine)); //fixme add comma dash
		}
		else if (currChar == '*') tokens.push_back(new Token(MULTIPLY, "*", currLine));
		else if (currChar == '+') tokens.push_back(new Token(ADD, "+", currLine));
		else if (currChar == '#') ScanComment(in, currLine);
		else if (isalpha(currChar)) ScanID(in, currLine);
		else if (currChar == '\'') ScanString(in, currLine);
		else if (currChar == '\n') ++currLine;
		else if (!iswspace(currChar) && currChar != EOF) tokens.push_back(new Token(UNDEFINED, std::string(1, currChar), currLine));

	} while (currChar != EOF);

	tokens.push_back(new Token(END_OF_FILE, "", currLine));
}

std::string Scanner::ToString()
{
	std::string outString = "";
	for (Token* currToken : tokens)  outString += currToken->ToString() + "\n";
	outString += "Total Tokens = " + std::to_string(tokens.size());
	return outString;
}

void Scanner::ScanString(std::ifstream& in, size_t& currLine)
{
	std::string tokenValue = "'";
	char currChar;
	size_t startLine = currLine;

	while (true)
	{
		currChar = in.get();
		if (currChar == '\'')
		{
			if (in.peek() == '\'')
			{
				tokenValue += "'";
				in.get();
			}
			else
			{
				tokenValue += "'";
				break;
			}
		}
		if (currChar == '\n') ++currLine;
		tokenValue += currChar;
		if (in.peek() == EOF)
		{
			tokens.push_back(new Token(UNDEFINED, tokenValue, startLine));
			return;
		}
	}

	tokens.push_back(new Token(STRING, tokenValue, startLine));
}

//fixme add keywords
void Scanner::ScanID(std::ifstream& in, size_t currLine)
{
	in.unget();
	char currChar = in.get();
	std::string tokenValue = "";

	while (isalnum(currChar))
	{
		tokenValue += currChar;
		currChar = in.get();
	}
	in.unget();

	if (tokenValue == "Schemes") tokens.push_back(new Token(SCHEMES, tokenValue, currLine));
	else if (tokenValue == "Facts") tokens.push_back(new Token(FACTS, tokenValue, currLine));
	else if (tokenValue == "Rules") tokens.push_back(new Token(RULES, tokenValue, currLine));
	else if (tokenValue == "Queries") tokens.push_back(new Token(QUERIES, tokenValue, currLine));
	else
		tokens.push_back(new Token(ID, tokenValue, currLine));
}

void Scanner::ScanComment(std::ifstream& in, size_t& currLine)
{
	size_t startLine = currLine;
	std::string tokenValue = "#";
	char currChar = in.get();

	if (currChar == '|')
	{
		tokenValue += currChar;
		currChar = in.get();
		while (currChar != '|' || in.peek() != '#')
		{
			tokenValue += currChar;

			if (currChar == '\n') ++currLine;
			if (in.peek() == EOF)
			{
				tokens.push_back(new Token(UNDEFINED, tokenValue, startLine));
				return;
			}

			currChar = in.get();
		}

		in.get();
		tokenValue += "|#";
	}
	else
	{
		tokenValue += currChar;
		while (in.peek() != '\n')
		{
			currChar = in.get();
			tokenValue += currChar;
		}
	}

	//taken out so Parser doesn't see comments
	//tokens.push_back(new Token(COMMENT, tokenValue, startLine));
}

std::vector<Token*>& Scanner::GetTokens()
{
	return tokens;
}