#include <iostream>
#include <unordered_map>
#include <unordered_set>
#include "library.h"

namespace tOct
{
	const Notation identifyInput(const std::string &input)
	{
		std::unordered_set<char> symbolicValues({SYMBOLIC_EMPTY});
		for (const std::pair<const Columns,char> &value : symbolicColumns) symbolicValues.insert(value.second);
		std::unordered_set<char> octalValues({OCTAL_EMPTY+CHAR_ZERO,(OCTAL_READ+OCTAL_WRITE)+CHAR_ZERO,(OCTAL_READ+OCTAL_WRITE+OCTAL_EXECUTE)+CHAR_ZERO,(OCTAL_READ+OCTAL_EXECUTE)+CHAR_ZERO,(OCTAL_WRITE+OCTAL_EXECUTE)+CHAR_ZERO});
		for (const std::pair<const Columns,char> &value : symbolicColumns) symbolicValues.insert(value.second+CHAR_ZERO);

		std::unordered_set<char> *values=nullptr;
		Notation result=Notation::INVALID;
		for (const char candidate : input)
		{
			if (!values)
			{
				if (symbolicValues.find(candidate) != symbolicValues.end())
				{
					values=&symbolicValues;
					result=Notation::SYMBOLIC;
					continue;
				}
				
				if (octalValues.find(candidate) != octalValues.end())
				{
					values=&octalValues;
					result=Notation::OCTAL;
					continue;
				}
				
				return Notation::INVALID;
			}
			else
			{
				if (values->find(candidate) == values->end()) return Notation::INVALID;
			}
		}
		return result;
	}
	
	Grid& iterateGrid(Grid &grid,const std::function<void(int row,int column,unsigned short &value)> &Operation)
	{
		for (int row=0; row < static_cast<int>(Rows::COUNT); row++)
		{
			for (int column=0; column < static_cast<int>(Columns::COUNT); column++)
			{
				Operation(row,column,grid[row][column]);
			}
		}
		return grid;
	}

	void iterateGrid(const Grid &grid,const std::function<void(int row,int column,const unsigned short &value)> &Operation)
	{
		for (int row=0; row < static_cast<int>(Rows::COUNT); row++)
		{
			for (int column=0; column < static_cast<int>(Columns::COUNT); column++)
			{
				Operation(row,column,grid[row][column]);
			}
		}
	}

	const Grid parseOctal(std::string input)
	{
		if (input.size() > OCTAL_MASK_MAX_LENGTH) input=input.substr(0,OCTAL_MASK_MAX_LENGTH); // TODO: error handle a mask that is too long
		// if (input.size() < OCTAL_MASK_MAX_LENGTH) { } // TODO: handle an octal mask that is too short
		input=input.substr(1,3); // TODO: // handle setuid/setgid/sticky bit
		Grid output;
		return iterateGrid(output,[&input](int row,int column,unsigned short &gridValue) {
			Columns columnType=static_cast<Columns>(column);
			if (octalColumns.at(columnType) <= input[row]-CHAR_ZERO)
			{
				input[row]-=octalColumns.at(columnType);
				gridValue=octalColumns.at(columnType);
			}
			else
			{
				gridValue=0;
			}
		});
	}

	const Grid parseSymbolic(std::string input)
	{
		if (input.size() > SYMBOLIC_MASK_MAX_LENGTH) input=input.substr(0,SYMBOLIC_MASK_MAX_LENGTH);
		if (input.size() < SYMBOLIC_MASK_MAX_LENGTH) input.append(SYMBOLIC_MASK_MAX_LENGTH-input.size(),'-');

		Grid output;
		return iterateGrid(output,[&input](int row,int column,unsigned short &gridValue) {
			char candidate=input[column+(static_cast<int>(Rows::COUNT)*row)];
			Columns columnType=static_cast<Columns>(column);
			if (candidate == symbolicColumns.at(columnType))
			{
				gridValue=octalColumns.at(columnType);
			}
			else
			{
				if (candidate == SYMBOLIC_EMPTY)
					gridValue=0;
				// TODO: handle situation where symbol is neither set nor '-'
				/*else
					return false;*/
			}
		});
	}

	std::string toOctal(const Grid &input)
	{
		std::string output;
		output+='0'; // TODO: this is setuid/setgid/sticky bit
		for (int row=0; row < static_cast<int>(Rows::COUNT); row++)
		{
			unsigned short total=0;
			for (int column=0; column < static_cast<int>(Columns::COUNT); column++) total+=input[row][column]; // TODO: add some error handling for invalid values
			output+=std::to_string(total);
		}
		return output;
	}
	

	std::string toSymbolic(const Grid &input)
	{
		std::string output;
		iterateGrid(input,[&output](int row,int column,const unsigned short &gridValue) {
			Columns columnType=static_cast<Columns>(column);
			if (gridValue == octalColumns.at(columnType))
				output+=symbolicColumns.at(columnType);
			else
				output+=SYMBOLIC_EMPTY;
		});
		return output;
	}
}
