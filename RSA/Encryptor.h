#ifndef ENCRYPTOR_H
#define ENCRYPTOR_H
#include <stdlib.h>
#include <time.h>
#include <fstream>
#include <iostream>
#include <sstream>
using namespace std;

class Encryptor
{
public:
	//arbitrary choices for testing size
	//sets min and max number of primes I'll pick from for incryption
	//kept low for easy testing
	const int PUBLIC_KEY_SIZE = 15;
	const int PUBLIC_KEY_MIN = 3;
	//how many primes to generate for encryption algorithm to use
	//not efficient, but good for testing
	Encryptor(size_t x = 200);
	//frees up memeory
	~Encryptor() { delete[] primes; }

	//getters
	size_t GetPublicMod() { return publicMod; }
	size_t GetPublicExp() { return publicExp; }
	size_t GetPrivateKey() { return privateKey; }

	//applies (message^key)%mod for RSA encryption
	size_t Crypt(size_t key, long long mod, long long message);
	//generate a random set of keys for RSA encryption
	//includes modulo and exponents for public and private key
	void GenerateKeys();

	/*for testing*/
	//reads in a encrypted number and public key from file
	//asks for decryption key and applies CRYPT function
	void FileReadNum(ifstream& file);
	//writes the public key and a encrypted number to a file
	//for testing
	void FileWriteNum(ofstream& file);

	//asks for public key info and message
	//turns message into a number and writes encrypted date
	//also writes public key
	void FileWrite(ofstream& file);
	//asks for private key
	//reads in file using stored public key info and private key to decrypt
	//file can be written to multiple times with different encryption
	//will run crypt on whole file, it's up to the human to see which one makes sense
	void FileRead(ifstream& file);

	//for text read and write if can make them work
	string NumToString(int num, int numChars = 0);
	long long StringToNum(string word);

private:
	size_t* primes;
	size_t privateKey;
	size_t publicMod;
	size_t publicExp;
	const size_t NUM_PRIMES;
	//generates a list of x prime numbers
	size_t* GeneratePrimes(size_t x);
};
#endif
