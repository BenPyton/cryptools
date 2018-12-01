#include "command.h"

// Global error struct
_Error_ err = { -1, "" };

Config GetConfig(int argc, char* argv[])
{
	Config conf = { "", "", "", SUCCESS, NONE };
	bool input = false;

	// start with 1 to skip the path of the command
	for(int i = 1; i < argc && conf.status == SUCCESS; i++)
	{
		// option flags
		if(argv[i][0] == '-')
		{
			// output option
			if((string)argv[i] == "-o" || (string)argv[i] == "--output")
			{
				// if it's not the last argument
				if(i+1 < argc)
				{
					conf.output = argv[i+1];
					i++;
				}
				else
				{
					err.code = 1;
					err.msg = "Missing output path after " + (string)argv[i];
					conf.status = FAIL;
				}
			}
			// key option
			else if((string)argv[i] == "-k" || (string)argv[i] == "--key")
			{
				// if it's not the last argument
				if(i+1 < argc)
				{
					conf.key = argv[i+1];
					i++;
				}
				else
				{
					err.code = 6;
					err.msg = "Missing key after argument " + (string)argv[i];
					conf.status = FAIL;
				}
			}
			// help option
			else if((string)argv[i] == "-h" || (string)argv[i] == "--help")
			{
				// Display Help
				if(conf.mode == NONE)
				{
					conf.mode = HELP;
				}
				else
				{
					err.code = 5;
					err.msg = "Multiple mode defined.";
					conf.status = FAIL;
				}
			}
			// encrypt option
			else if((string)argv[i] == "-e" || (string)argv[i] == "--encrypt")
			{
				if(conf.mode == NONE)
				{
					conf.mode = ENCRYPT;
				}
				else
				{
					err.code = 5;
					err.msg = "Multiple mode defined.";
					conf.status = FAIL;
				}
			}
			// decrypt option
			else if((string)argv[i] == "-d" || (string)argv[i] == "--decrypt")
			{
				if(conf.mode == NONE)
				{
					conf.mode = DECRYPT;
				}
				else
				{
					err.code = 5;
					err.msg = "Multiple mode defined.";
					conf.status = FAIL;
				}
			}
			// unknown option
			else
			{
				err.code = 2;
				err.msg = "Unknown option " + (string)argv[i];
				conf.status = FAIL;
			}
		}
		// argument without option flag and no input entered
		else if(!input)
		{
			conf.input = argv[i];
			input = true;
		}
		// Argument without option flag and input already entered
		else
		{
			err.code = 3;
			err.msg = "There are more than one input path";
			conf.status = FAIL;
		}
	}

	// test if an input has been entered
	if(!input && conf.mode != HELP)
	{
		err.code = 4;
		err.msg = "Missing input path";
		conf.status = FAIL;
	}
	// Argument key is not present or empty key entered
	else if(conf.key.empty() && conf.mode != HELP)
	{
		err.code = 6;
		err.msg = "Missing key";
		conf.status = FAIL;
	}

	return conf;
}