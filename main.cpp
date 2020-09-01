#include <iostream>
#include <unordered_set>
#include <unistd.h>
#include "library.h"

enum class ErrorCodes
{
	UNKNOWN = -1,
	OK = 0,
	TOO_FEW_ARGUMENTS,
	MIXED,
	INVALID_SYMBOL,
	INTERNAL_LIBRARY
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

const tOct::Notation identifyInput(const std::string &input)
{
	std::unordered_set<char> symbolicValues({tOct::SYMBOLIC_EMPTY});
	for (const std::pair<const tOct::Columns,char> &value : tOct::symbolicColumns) symbolicValues.insert(value.second);
	std::unordered_set<char> octalValues({
		tOct::numberToCharacter(tOct::OCTAL_EMPTY),
		tOct::numberToCharacter(tOct::OCTAL_READ+tOct::OCTAL_WRITE),
		tOct::numberToCharacter(tOct::OCTAL_READ+tOct::OCTAL_WRITE+tOct::OCTAL_EXECUTE),
		tOct::numberToCharacter(tOct::OCTAL_READ+tOct::OCTAL_EXECUTE),
		tOct::numberToCharacter(tOct::OCTAL_WRITE+tOct::OCTAL_EXECUTE)
	});
	for (const std::pair<const tOct::Columns,unsigned short> &value : tOct::octalColumns) octalValues.insert(tOct::numberToCharacter(value.second));

	std::unordered_set<char> *values=nullptr;
	tOct::Notation result=tOct::Notation::INVALID;
	for (const char candidate : input)
	{
		if (!values)
		{
			if (symbolicValues.find(candidate) != symbolicValues.end())
			{
				values=&symbolicValues;
				result=tOct::Notation::SYMBOLIC;
				continue;
			}
			
			if (octalValues.find(candidate) != octalValues.end())
			{
				values=&octalValues;
				result=tOct::Notation::OCTAL;
				continue;
			}
			
			return tOct::Notation::INVALID;
		}
		else
		{
			if (values->find(candidate) == values->end()) return tOct::Notation::INVALID;
		}
	}
	return result;
}

int main(int argc,char *argv[])
{
	// need at least one command line argument
	if (argc < 2) return raiseError(ErrorCodes::TOO_FEW_ARGUMENTS);
	
	std::string input=argv[1];
	if (input.size() < 1) return raiseError(ErrorCodes::TOO_FEW_ARGUMENTS);
	
	bool terminal=isatty(fileno(stdout));
	try
	{
		switch (identifyInput(input))
		{
			case tOct::Notation::INVALID:
				return raiseError(ErrorCodes::INVALID_SYMBOL);
			case tOct::Notation::OCTAL:
			{
				const tOct::Grid grid=tOct::parseOctal(input);
				if (terminal)
					std::cout << tOct::toSymbolic(grid) << std::endl;
				else
					std::cout << tOct::toScripted(grid);
				break;
			}
			case tOct::Notation::SYMBOLIC:
			{
				const tOct::Grid grid=tOct::parseSymbolic(input);
				if (terminal)
					std::cout << tOct::toOctal(grid) << std::endl;
				else
					std::cout << tOct::toScripted(grid);
				break;
			}
		}
	}
	
	catch (std::runtime_error &exception)
	{
		std::cout << exception.what() << std::endl;
		return static_cast<int>(ErrorCodes::INTERNAL_LIBRARY);
	}
	
	return static_cast<int>(ErrorCodes::OK);
}
