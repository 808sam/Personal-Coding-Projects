//created by Samuel Owens
//basic tests showing a working RSA encryption with small keys
//not very secure, but a good proof of concept
//when running a.out, include the file you'll be reading and writing to as a parameter




#include <iostream>
#include "Encryptor.h"
#include <fstream>

#define NUM_PRIMES_SECURE 50

using namespace std;

//print option menu to console
void PrintMenu()
{
	cout << "m: menu" << endl;
	cout << "w: write" << endl;
	cout << "r: read" << endl;
	cout << "k: new keys" << endl;
	cout << "d: delete file contents" << endl;
	cout << "c: clear screen" << endl;
	cout << "q: quit" << endl;
}

int main(int argc, char** argv)
{	
	//pick how many primes encryption will calculate
	Encryptor Encoder(NUM_PRIMES_SECURE); //Encryptor defaults to 200 primes 


	//Intro message
	cout << "\n\tRSA Encryption Tests" << endl;
	cout << "Create RSA encryption keys and use those keys to read and write multiple\n"
		<< "encrypted messages to and from the output file. Feel free to check out the\n"
		<< "code to tweak parameters and see how it works\n"
		<< "Have Fun!" << "\n\n";


	string command; //holds the menu choice
	PrintMenu();
	cout << "What would you like to do?" << endl;
	getline(cin, command);

	//loop through menu until user quits
	while (command != "q")
	{
		if (command == "w") //write to file
		{
			ofstream out(argv[1], ios::app);
			Encoder.FileWrite(out);
			out.close();
		}
		else if (command == "r") //read from file
		{
			ifstream in(argv[1]);
			Encoder.FileRead(in);
			in.close();
		}
		else if (command == "k") //generate new keys
		{
			Encoder.GenerateKeys();
			cout << "public Key: " << Encoder.GetPublicExp() << endl 
				<< "public mod: " << Encoder.GetPublicMod() << endl 
				<< "private key: " << Encoder.GetPrivateKey() << endl;
		}
		else if (command == "d") //delete file contents
		{
			ofstream out(argv[1]);
			out.close();
		}
		else if (command == "c") //clear terminal screen
		{
			system("cls"); //try both for different systems
			system("clear");
		}
		else if (command == "e") //export key info, for testing
		{
			ofstream out(argv[2]);
			out << Encoder.GetPublicExp() << endl << Encoder.GetPublicMod();
			ofstream out2(argv[3]);
			out2 << Encoder.GetPublicMod() << endl << Encoder.GetPrivateKey();
			cout << "Exported" << endl;
		}
		else if (command == "i") // instant crypt number, for testing
		{
			//enter key and mod from public key and number to encrypt
			size_t key;
			size_t mod;
			size_t num;

			cout << "Enter key: ";
			cin >> key;
			cout << "Enter mod: ";
			cin >> mod;
			cout << "Enter number: ";
			cin >> num;
			cin.ignore();

			cout << Encoder.Crypt(key, mod, num) << endl;
		}
		else if (command == "wn") //write encrypted number to file, for testing
		{
			ofstream out(argv[1], ios::app);
			Encoder.FileWriteNum(out);
			out.close();
		}
		else if (command == "rn") //read encrypted number from file, for testing
		{
			ifstream in(argv[1]);
			Encoder.FileReadNum(in);
			in.close();
		}
		else if (command != "q") //invalid choice, print menu
		{
			PrintMenu();
		}
		cout << "What would you like to do?" << endl;
		getline(cin, command);
	}
	return 0;
}