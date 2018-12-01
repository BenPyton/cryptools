#include <iostream>
#include <fstream>
#include "command.h"
#include "aes.h"
#include <ctime>

using namespace std;

int main (int argc, char* argv[])
{
	Config c = GetConfig(argc, argv);

	// The command line has no error
	if(c.status == SUCCESS)
	{
		Matrix key;
		key = str2mat(c.key);
		float totalTime = clock();
		// REAL PROGRAM
		switch(c.mode)
		{
		case HELP:
			// display help
			cout << "Display help here" << endl;
			break;
		case ENCRYPT:
			if(c.output.empty())
			{
				c.output = c.input + ".encrypted";
			}
			if(EncryptFile(c.input, c.output, key))
			{
				totalTime = clock() - totalTime;
				cout << "Done." << endl;
				cout << c.output << " generated in " << totalTime / CLOCKS_PER_SEC << "s." << endl;
			}
			else
			{
				cout << "[Error] Unable to open file " << c.input << endl;
			}
			// encrypt input data
			break;
		case DECRYPT:
			if(c.output.empty())
			{
				c.output = c.input + ".decrypted";
			}

			if(DecryptFile(c.input, c.output, key))
			{
				totalTime = clock() - totalTime;
				cout << "Done." << endl;
				cout << c.output << " generated in " << totalTime / CLOCKS_PER_SEC << "s." << endl;
			}
			else
			{
				cout << "[Error] Unable to open file " << c.input << endl;
			}
			// decrypt input data
			break;
		default:
			cout << "[Error] No mode provided" << endl;
			break;
		}
		
	}
	else
	{
		cerr << "[ERROR] code " << err.code << " : " << err.msg;
	}
}








