#ifndef _COMMAND_H
#define _COMMAND_H

#include <string>
using namespace std;

enum Status { UNKNOWN = -1, SUCCESS, FAIL };
enum Mode { NONE = -1, HELP, ENCRYPT, DECRYPT };

struct _Error_
{
	int code;
	string msg;
};

struct Config
{
	string input;
	string output;
	string key;
	Status status;
	Mode mode;
};

extern _Error_ err;

// Return the config from main arguments
Config GetConfig(int argc, char* argv[]);

#endif // _COMMAND_H