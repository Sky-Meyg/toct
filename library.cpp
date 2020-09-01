#include <iostream>
#include <unordered_map>
#include "library.h"

namespace tOct
{
	const Grid parseOctal(std::string input)
	{
		if (input.size() > SYMBOLIC_MASK_MAX_LENGTH) input=input.substr(0,SYMBOLIC_MASK_MAX_LENGTH);
		if (input.size() < SYMBOLIC_MASK_MAX_LENGTH) input.append(SYMBOLIC_MASK_MAX_LENGTH-input.size(),'-');

		Grid output;
		for (int row=0; row < static_cast<int>(Rows::COUNT); row++)
		{
			for (int column=0; column < static_cast<int>(Columns::COUNT); column++)
			{
				char candidate=input[column+(static_cast<int>(Rows::COUNT)*row)];
				Columns columnType=static_cast<Columns>(column);
				unsigned short &gridValue=output[row][static_cast<int>(columnType)];
				if (candidate == symbolicValues.at(columnType))
				{
					gridValue=octalValues.at(columnType);
				}
				else
				{
					if (candidate == SYMBOLIC_EMPTY)
						gridValue=0;
					else
						return false;
				}
			}
		}		
		return output;
	}

	bool toOctal(const Grid &input)
	{		
		unsigned short output[3]={0,0,0};
		std::string symbolGroups[static_cast<int>(Rows::COUNT)];
		//for (int row=0; row < static_cast<int>(Rows::COUNT); row++) symbolGroups[row]=input.substr(static_cast<int>(Rows::COUNT)*row,3);
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

	bool toSymbolic(std::string &input)
	{
		if (input.size() > OCTAL_MASK_MAX_LENGTH) input=input.substr(input.size()-OCTAL_MASK_MAX_LENGTH,OCTAL_MASK_MAX_LENGTH);
		if (input.size() < OCTAL_MASK_MAX_LENGTH)
		{
			return false; // return error string here
		}

		std::string symbolGroups[static_cast<int>(Rows::COUNT)];
		for (int row=0; row < static_cast<int>(Rows::COUNT); row++)
		{
			int octal=input[row+1]-48;
			std::cout << octal << std::endl;
			// even means we know we don't have an execute bit set
			if (octal % 2 == 0)
			{
				if (octal > 2)
				{
					if (octal > 4)
						symbolGroups[row]="rw-";
					else
						symbolGroups[row]="-w-";
				}
				else
				{
					symbolGroups[row]="r--";
				}
			}
			else
			{
			}
		}
		
		for (const std::string &group : symbolGroups) std::cout << group;
		std::cout << std::endl;
		return true;
	}
}
