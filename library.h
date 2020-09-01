#pragma once

#include <vector>

namespace tOct
{
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
		COUNT = 3
	};
	
	const char SYMBOLIC_READ='r';
	const char SYMBOLIC_WRITE='w';
	const char SYMBOLIC_EXECUTE='x';
	const char SYMBOLIC_EMPTY='-';
	const std::unordered_map<Columns,char> symbolicValues={
		{ Columns::READ, SYMBOLIC_READ },
		{ Columns::WRITE, SYMBOLIC_WRITE },
		{ Columns::EXECUTE, SYMBOLIC_EXECUTE }
	};
	const unsigned short OCTAL_READ=4;
	const unsigned short OCTAL_WRITE=2;
	const unsigned short OCTAL_EXECUTE=1;
	const unsigned short OCTAL_EMPTY=0;
	const std::unordered_map<Columns,unsigned short> octalValues={
		{ Columns::READ, OCTAL_READ },
		{ Columns::WRITE, OCTAL_WRITE },
		{ Columns::EXECUTE, OCTAL_EXECUTE }
	};

	const unsigned short SYMBOLIC_MASK_MAX_LENGTH=9;
	const unsigned short OCTAL_MASK_MAX_LENGTH=4;
	
	typedef std::array<std::array<unsigned short,static_cast<int>(Columns::COUNT)>,static_cast<int>(Rows::COUNT)> Grid;

	const Grid parseOctal(std::string input);
	bool toOctal(std::string &input);
	bool toSymbolic(std::string &input);
}