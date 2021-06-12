#include "Encryptor.h"

//how many primes to generate for encryption algorithm to use
//not efficient, but good for testing
Encryptor::Encryptor(size_t x) : NUM_PRIMES(x) //default 200 prime security
{
	primes = GeneratePrimes(x);
	srand(time(NULL));
}
//applies (message^key)%mod for RSA encryption
size_t Encryptor::Crypt(size_t key, long long mod, long long message)
{
	long long xMessage = message;
	for (size_t i = 0; i < key - 1; ++i)
	{
		xMessage *= message;
		xMessage %= mod;
	}
	return xMessage;
}
//generate a random set of keys
void Encryptor::GenerateKeys()
{
	size_t p = primes[(rand() % (NUM_PRIMES / 2)) + (NUM_PRIMES / 2)];
	size_t q = primes[(rand() % (NUM_PRIMES / 2)) + (NUM_PRIMES / 2)];

	//generate public key
	publicMod = p * q;
	size_t phi = (p - 1) * (q - 1);

	size_t publicKey = ((rand() % PUBLIC_KEY_SIZE) + PUBLIC_KEY_MIN) % NUM_PRIMES; //public key random index for prime number
	publicExp = primes[publicKey];

	//make sure publicKey is valid
	for (size_t i = publicKey; (phi % primes[i]) == 0; ++i)
	{
		publicExp = primes[i + 1];
		if (i == NUM_PRIMES) i = PUBLIC_KEY_MIN;
		if (i == publicKey - 1) i = 0; //shouldn't get here if PUBLIC_KEY_MIN is good. Last catch for validity
	}

	//find private key
	//euclids method
	/*
	left  right
	to1 toPr
	*/
	size_t left = phi;
	size_t right = phi;
	int to1 = publicExp;
	int toPr = 1;
	int newto1;
	int newtoPr;

	while (to1 != 1)
	{
		//step on right side
		newtoPr = right - (toPr * (left / to1));
		while (newtoPr < 0) newtoPr += phi;

		//step on left side
		newto1 = left % to1;
		
		//step down
		left = to1;
		right = toPr;
		to1 = newto1;
		toPr = newtoPr;
	}
	privateKey = toPr;
}

//for testing
//reads in a encrypted number and public key from file
//asks for decryption key and applies CRYPT function
void Encryptor::FileReadNum(ifstream& file)
{
	size_t key;
	size_t mod;
	size_t num;

	cout << "Input Key: ";
	cin >> key;
	cin.ignore();

	while (file >> mod)
	{
		file >> num;
		cout << Crypt(key, mod, num) << endl;
	}
}
//writes the public key and a encrypted number to a file
//for testing
void Encryptor::FileWriteNum(ofstream& file)
{
	//get key and message
	size_t key;
	size_t mod;
	size_t userNum;

	cout << "Enter key: ";
	cin >> key;
	cout << "Enter mod: ";
	cin >> mod;
	file << mod << " ";
	cout << "Write number: " << endl;
	cin >> userNum;
	cin.ignore();

	file << Crypt(key, mod, userNum) << endl;
}
//asks for public key info and message
//turns message into a number and writes encrypted date
//also writes public key
void Encryptor::FileWrite(ofstream& file)
{
	//get key and message
	size_t key;
	size_t mod;
	string message;
	size_t numCharsMax = 0;

	cout << "Enter key: ";
	cin >> key;
	cout << "Enter mod: ";
	cin >> mod;
	cin.ignore();
	file << mod << " ";
	cout << "Write message: " << endl;
	getline(cin, message);

	//get number of characters we can map to at once
	size_t maxNum = 1;
	while (maxNum < mod)
	{
		numCharsMax++;
		maxNum *= 95;
	}
	//number of characters we can guarenteed map from
	size_t numCharsMin = numCharsMax-1;

	string currWord;
	for (size_t i = 0; i < message.size(); i += numCharsMin)
	{
		if (message.size() - i > numCharsMin)
		{
			currWord = message.substr(i, numCharsMin);
		}
		else
		{
			currWord = message.substr(i);
			while (currWord.size() < numCharsMin) currWord += " ";
		}
		file << NumToString(Crypt(key, mod, StringToNum(currWord)), numCharsMax);
	}
	file << endl;
}
//asks for private key
//reads in file using stored public key info and private key to decrypt
//file can be written to multiple times with different encryption
//will run crypt on whole file, it's up to the human to see which one makes sense
void Encryptor::FileRead(ifstream& file)
{
	size_t key;
	size_t mod;
	size_t num;
	string currLine;

	cout << "Input Key: ";
	cin >> key;
	cin.ignore();

	size_t numLines = 0;
	while (file >> mod)
	{
		size_t numCharsMax = 0;

		file.ignore();
		getline(file, currLine);

		//get number of characters
		size_t maxNum = 1;
		while (maxNum < mod)
		{
			numCharsMax++;
			maxNum *= 95;
		}

		cout << ++numLines << ": ";
		for (size_t i = 0; i < currLine.size(); i += numCharsMax)
		{
			string currWord;
			if (currLine.size() - i > numCharsMax) currWord = currLine.substr(i, numCharsMax);
			else currWord = currLine.substr(i, currLine.size() - i);
			cout << NumToString(Crypt(key, mod, StringToNum(currWord)), numCharsMax-1);
		}
		cout << endl;
	}
}

//generate a vector of prime numbers x numbers long
size_t* Encryptor::GeneratePrimes(size_t x)
{
	size_t* primeArray = new size_t[x];
	size_t numPrimes = 0;
	for (size_t i = 2; numPrimes < x; ++i)
	{
		bool isPrime = true;
		for (size_t j = 0; j < numPrimes; ++j)
		{
			if (i % primeArray[j] == 0)
			{
				isPrime = false;
				break;
			}
		}
		if (isPrime) primeArray[numPrimes++] = i;
	}
	return primeArray;
}

//uses ascii chars from 32 to 127 as if it was a base 95 system
//converts input string into a number to be used in encryption algorithm
long long Encryptor::StringToNum(string word)
{
	//get each char
	long long charValue = 1;
	long long outNum = 0;
	for (int i = word.length() - 1; i >= 0; --i)
	{
		outNum += ((int)word[i] - 32)* charValue;
		charValue *= 95;
	}
	return outNum;
}

//does the opposite of StringToNum
//if numChars not specified will try to convert the entire input
string Encryptor::NumToString(int num, int numCharsMax)
{
	bool adjust = false;
	if (numCharsMax == 0) adjust = true;

	long long charValue = 1;

	if (adjust)
	{
		while (num >= charValue * 95)
		{
			charValue *= 95;
			++numCharsMax;
		}
		++numCharsMax;
	}
	else
	{
		for (size_t i = 0; i < numCharsMax - 1; ++i)
		{
			charValue *= 95;
		}
	}

	string out = "";
	while (charValue >= 95)
	{
		int currChar = 0;
		currChar = num/charValue;
		num %= charValue;
		charValue /= 95;
		out += (char)(currChar + 32);
	}
	return out + (char)(num + 32);
}
