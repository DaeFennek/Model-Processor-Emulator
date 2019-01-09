#pragma once

#include "accumulator.h"
#include "ram.h"

namespace processor
{
	class CPU
	{
		public:
			CPU();
			void Run(char code[], char data[]);

		private:
			void Execute(char instruction, char data);
			void Fetch();

		private:
			Accumulator m_accu;
			Ram m_dataRam;
			Ram m_codeRam;
			char m_zeroRegister, m_carryRegister, m_negativeRegister;
			char m_progamCounterRegister, m_instructionRegister, m_dataRegister;
	};
}

