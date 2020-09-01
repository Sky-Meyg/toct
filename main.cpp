#include <iostream>
#include <unordered_map>
#include "library.h"

enum class ErrorCodes
{
	UNKNOWN = -1,
	OK = 0,
	TOO_FEW_ARGUMENTS,
	MIXED,
	INVALID_SYMBOL
};

const std::unordered_map<ErrorCodes,std::string> ErrorStrings = {
	{ ErrorCodes::UNKNOWN, "An unrecognized error occurred" },
	{ ErrorCodes::TOO_FEW_ARGUMENTS, "Too few arguments specified, please specify an octal or symbolic mask" },
	{ ErrorCodes::MIXED, "Mix of symbolic, octal, and or other data detected" },
	{ ErrorCodes::INVALID_SYMBOL, "An invalid symbolic or octal string was specified" }
};

const int raiseError(const ErrorCodes requestedCode)
{
	int returnCode;
	if (ErrorStrings.find(requestedCode) == ErrorStrings.end())
	{
		std::cout << ErrorStrings.at(ErrorCodes::UNKNOWN);
		returnCode=static_cast<int>(ErrorCodes::UNKNOWN);
	}
	else
	{
		std::cout << ErrorStrings.at(requestedCode);
		returnCode=static_cast<int>(requestedCode);
	}
	std::cout << std::endl;
	return returnCode;
}

int main(int argc,char *argv[])
{
	// need at least one command line argument
	if (argc < 2) return raiseError(ErrorCodes::TOO_FEW_ARGUMENTS);
	
	std::string input=argv[1];
	if (input.size() < 1) return raiseError(ErrorCodes::TOO_FEW_ARGUMENTS);
	//toOctal(input);
	//tOct::toSymbolic(input);
	std::cout << tOct::toOctal(tOct::parseOctal(input)) << std::endl;
	
	return 0;
}
