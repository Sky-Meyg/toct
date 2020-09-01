#include <iostream>
#include <unordered_map>

enum class ErrorCodes
{
	UNKNOWN = -1,
	OK = 0,
	TOO_FEW_ARGUMENTS
};

typedef std::unordered_map<ErrorCodes,std::string> ErrorStringMap;
const std::unordered_map<ErrorCodes,std::string> ErrorStrings = {
	{ ErrorCodes::UNKNOWN, "An unrecognized error occurred" },
	{ ErrorCodes::TOO_FEW_ARGUMENTS, "Too few arguments specified, please specify an octal or symbolic mask" }
};

bool toOctal()
{
}

bool toSymbolic()
{
}

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
	if (argc < 2) return raiseError(ErrorCodes::TOO_FEW_ARGUMENTS);
	return 0;
}
