#pragma once

#include <string>
#include <unordered_map>
#include <functional>

namespace tOct
{
	enum class Notation
	{
		INVALID,
		SYMBOLIC,
		OCTAL,
		SCRIPT
	};

	enum class Rows
	{
		USER = 0,
		GROUP = 1,
		OTHER = 2,
		COUNT = 3
	};

	enum class Columns
	{
		READ = 0,
		WRITE = 1,
		EXECUTE = 2,
		COUNT = 3
	};
	
	const unsigned short CHAR_ZERO=48;
	const char SYMBOLIC_READ='r';
	const char SYMBOLIC_WRITE='w';
	const char SYMBOLIC_EXECUTE='x';
	const char SYMBOLIC_EMPTY='-';
	const std::unordered_map<Columns,char> symbolicColumns={
		{ Columns::READ, SYMBOLIC_READ },
		{ Columns::WRITE, SYMBOLIC_WRITE },
		{ Columns::EXECUTE, SYMBOLIC_EXECUTE }
	};
	const unsigned short OCTAL_READ=4;
	const unsigned short OCTAL_WRITE=2;
	const unsigned short OCTAL_EXECUTE=1;
	const unsigned short OCTAL_EMPTY=0;
	const std::unordered_map<Columns,unsigned short> octalColumns={
		{ Columns::READ, OCTAL_READ },
		{ Columns::WRITE, OCTAL_WRITE },
		{ Columns::EXECUTE, OCTAL_EXECUTE }
	};
	const char SCRIPTED_USER='u';
	const char SCRIPTED_GROUP='g';
	const char SCRIPTED_OTHER='o';
	const std::unordered_map<Rows,char> scriptedRows={
		{ Rows::USER, SCRIPTED_USER },
		{ Rows::GROUP, SCRIPTED_GROUP },
		{ Rows::OTHER, SCRIPTED_OTHER },
	};

	const unsigned short SYMBOLIC_MASK_MAX_LENGTH=9;
	const unsigned short OCTAL_MASK_MAX_LENGTH=4;
	
	typedef std::array<std::array<unsigned short,static_cast<int>(Columns::COUNT)>,static_cast<int>(Rows::COUNT)> Grid;

	const char numberToCharacter(const unsigned int number) { return number+CHAR_ZERO; }
	const unsigned short characterToNumber(const char character) { return character-CHAR_ZERO; }
	const Notation identifyInput(const std::string &input);
	
	const Grid parseOctal(std::string input);
	const Grid parseSymbolic(std::string input);
	std::string toOctal(const Grid &input);
	std::string toSymbolic(const Grid &input);
	std::string toScripted(const Grid &input);
	
	const std::string ERROR_SYMBOLIC_INVALID="Invalid character encountered parsing symbolic notation";
	const std::string ERROR_OCTAL_INVALID="Invalid character encountered parsing octal notation";
}
