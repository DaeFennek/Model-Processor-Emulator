#pragma once

#include <string>
#include <iostream>
#include <fstream>

#define CMD(LINE, OP, DATA) code[LINE] = OP;\
							data[LINE] = DATA;\
							LINE++;
namespace assembler 
{
	std::string RemoveChar(const std::string& str, char c)
	{
		std::string tmp_str;
		for (unsigned int i = 0; i < str.length(); ++i)
			if (str[i] != c)
				tmp_str += str[i];

		return tmp_str;
	}

	void Compile(const std::string& filePath, char code[], char data[])
	{
		std::ifstream file(filePath);
		std::string line;
		char index = 0;
		while (getline(file, line))
		{
			line = RemoveChar(line, ' ');
			if (line.find("NOP") != std::string::npos || line.find("nop") != std::string::npos)
			{
				CMD(index, 0x00, 0x00);
			}
			else if (line.find("LDA") != std::string::npos || line.find("lda") != std::string::npos)
			{
				if (line.at(3) == '(')
				{
					CMD(index, 0x02, (char)std::stoi(line.substr(4, line.length() - 4)));
				}					
				else	
				{
					CMD(index, 0x01, (char)std::stoi(line.substr(3, line.length() - 3)));
				}					
			}
			else if (line.find("STA") != std::string::npos || line.find("sta") != std::string::npos)
			{				
				CMD(index, 0x03, (char)std::stoi(line.substr(4, line.length() - 4)));
			}
			else if (line.find("ADD") != std::string::npos || line.find("add") != std::string::npos)
			{
				if (line.at(3) == '(')
				{					
					CMD(index, 0x05, (char)std::stoi(line.substr(4, line.length() - 4)));
				}
				else
				{							
					CMD(index, 0x04, (char)std::stoi(line.substr(3, line.length() - 3)));
				}
			}
			else if (line.find("SUB") != std::string::npos || line.find("sub") != std::string::npos)
			{
				if (line.at(3) == '(')
				{					
					CMD(index, 0x07, (char)std::stoi(line.substr(4, line.length() - 4)));
				}
				else
				{					
					CMD(index, 0x06, (char)std::stoi(line.substr(3, line.length() - 3)));
				}
			}
			else if (line.find("JMP") != std::string::npos || line.find("jmp") != std::string::npos)
			{				
				CMD(index, 0x08, (char)std::stoi(line.substr(3, line.length() - 3)));
			}
			else if (line.find("BRZ") != std::string::npos || line.find("brz") != std::string::npos)
			{				
				CMD(index, 0x09, (char)std::stoi(line.substr(3, line.length() - 3)));
			}
			else if (line.find("BRC") != std::string::npos || line.find("brc") != std::string::npos)
			{				
				CMD(index, 0x0A, (char)std::stoi(line.substr(3, line.length() - 3)));
			}
			else if (line.find("BRN") != std::string::npos || line.find("brn") != std::string::npos)
			{
				CMD(index, 0x0B, (char)std::stoi(line.substr(3, line.length() - 3)));
			}
		}
	}
}