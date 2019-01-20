#include <iostream>
#include "cpu.h"
#include "assembler.h"

int main(int argv, char** argc)
{
	char data[16] = { 0 };
	char code[16] = { 0 };
	assembler::Compile("assembly.asm", code, data);
	processor::CPU cpu;
	cpu.Run(code, data);
	std::cin.get();
	return 0;
}