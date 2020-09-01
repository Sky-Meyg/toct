#include <iostream>
#include <unordered_map>

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

enum class Rows
{
	USER = 0,
	GROUP = 1,
	EXECUTE = 2,
	COUNT = 3
};

enum class Columns
{
	READ = 0,
	WRITE = 1,
	EXECUTE = 2,
	TOTAL = 3,
	COUNT = 4
};

const unsigned short SYMBOLIC_MASK_MAX_LENGTH=9;

bool toOctal(std::string &input)
{
	if (input.size() > SYMBOLIC_MASK_MAX_LENGTH) input=input.substr(0,SYMBOLIC_MASK_MAX_LENGTH);
	if (input.size() < SYMBOLIC_MASK_MAX_LENGTH) input.append(SYMBOLIC_MASK_MAX_LENGTH-input.size(),'-');
	
	unsigned short output[3]={0,0,0};
	std::string symbolGroups[static_cast<int>(Rows::COUNT)];
	for (int row=0; row < static_cast<int>(Rows::COUNT); row++) symbolGroups[row]=input.substr(static_cast<int>(Rows::COUNT)*row,3);
	for (int row=0; row < static_cast<int>(Rows::COUNT); row++) std::cout << symbolGroups[row] << std::endl; 
	for (int row=0; row < static_cast<int>(Rows::COUNT); row++)
	{
		if (symbolGroups[row][static_cast<int>(Columns::READ)] == 'r') output[row]+=4;
		if (symbolGroups[row][static_cast<int>(Columns::WRITE)] == 'w') output[row]+=2;
		if (symbolGroups[row][static_cast<int>(Columns::EXECUTE)] == 'x') output[row]+=1;
	}

	std::cout << "0";
	for (const unsigned short &octal : output) std::cout << std::to_string(octal);
	std::cout << std::endl;

	return true;
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
	// need at least one command line argument
	if (argc < 2) return raiseError(ErrorCodes::TOO_FEW_ARGUMENTS);
	
	std::string input=argv[1];
	if (input.size() < 1) return raiseError(ErrorCodes::TOO_FEW_ARGUMENTS);
	toOctal(input);
	
	return 0;
}
