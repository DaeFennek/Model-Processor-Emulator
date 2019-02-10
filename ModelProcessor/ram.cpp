#include "ram.h"
#include <iomanip>
#include <iostream>

void processor::Ram::Dump()
{
	for (unsigned int i = 0; i < 16; ++i)
		std::cout << std::hex << (int)m_data[i] << " ";
}
