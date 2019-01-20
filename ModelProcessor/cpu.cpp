#include <thread>
#include <chrono>
#include <iostream>
#include "cpu.h"

processor::CPU::CPU() : m_zeroRegister(0), m_carryRegister(0), m_negativeRegister(0), m_progamCounterRegister(0),
	m_instructionRegister(0), m_dataRegister(0)
{	
}

void processor::CPU::Execute(char instruction, char data)
{	
	switch (instruction)
	{
		case 0x00: // NOP
			++m_progamCounterRegister;
			break;
		case 0x01: // LDA n
			m_accu.SetValue(data);	
			m_zeroRegister = m_accu.Value() == 0;
			m_carryRegister = m_accu.Carry();
			m_negativeRegister = (m_accu.Value() >> 3) & 0x01;
			++m_progamCounterRegister;
			break;
		case 0x02: // LDA (n)
			m_accu.SetValue(m_dataRam.DataAt(data));
			m_zeroRegister = m_accu.Value() == 0;
			m_carryRegister = m_accu.Carry();
			m_negativeRegister = (m_accu.Value() >> 3) & 0x01;
			++m_progamCounterRegister;
			break;
		case 0x03: // STA (n)
			m_dataRam.SetDataAt(data, m_accu.Value());			
			++m_progamCounterRegister;
			break;
		case 0x04: // ADD n
			m_accu.Add(data);	
			m_zeroRegister = m_accu.Value() == 0;
			m_carryRegister = m_accu.Carry();
			m_negativeRegister = 0x00;
			++m_progamCounterRegister;
			break;
		case 0x05: // ADD (n)
			m_accu.Add(m_dataRam.DataAt(data));		
			m_zeroRegister = m_accu.Value() == 0;
			m_carryRegister = m_accu.Carry();
			m_negativeRegister = 0x00;
			++m_progamCounterRegister;
			break;
		case 0x06: // SUB n
			m_accu.Sub(data);		
			m_zeroRegister = m_accu.Value() == 0;
			m_carryRegister = m_accu.Carry();
			m_negativeRegister = (m_accu.Value() >> 3) & 0x01;
			++m_progamCounterRegister;
			break;
		case 0x07: // SUB (n)
			m_accu.Sub(m_dataRam.DataAt(data));
			m_zeroRegister = m_accu.Value() == 0;
			m_carryRegister = m_accu.Carry();
			m_negativeRegister = (m_accu.Value() >> 3) & 0x01;
			++m_progamCounterRegister;
			break;		
		case 0x08: // JMP n
			m_progamCounterRegister = data;
			break;
		case 0x09: // BRZ n
			if (m_zeroRegister)						
				m_progamCounterRegister += data;
			else
				++m_progamCounterRegister;							
			break;
		case 0x0A: // BRC n
			if (m_carryRegister) 			
				m_progamCounterRegister += data;				
			else
				++m_progamCounterRegister;
			break;
		case 0x0B: // BRN n
			if (m_negativeRegister) 			
				m_progamCounterRegister += data;
			else
				++m_progamCounterRegister;
			break;
		default:
			break;
	}
}

void processor::CPU::Fetch()
{
	m_instructionRegister = m_codeRam.DataAt(m_progamCounterRegister);
	m_dataRegister = m_dataRam.DataAt(m_progamCounterRegister);
}


void processor::CPU::Run(char code[], char data[])
{
	m_codeRam.Load(code);
	m_dataRam.Load(data);	

	using namespace std::chrono_literals;
	while (m_progamCounterRegister < 16)
	{
		Fetch();
		Execute(m_instructionRegister, m_dataRegister);
		std::this_thread::sleep_for(1s);

		std::cout << "Accumulator Value: " << (int)m_accu.Value() << std::endl
			<< "Carry: " << (int)m_carryRegister << std::endl
			<< "Zero: " << (int)m_zeroRegister << std::endl
			<< "Negative: " << (int)m_negativeRegister << std::endl
			<< "PC: " << (int)m_progamCounterRegister << std::endl
			<< "Instruction: " << (int)m_instructionRegister << std::endl
			<< "Data: " << (int)m_dataRegister << std::endl
			<< "+++++++++++++++++++++++++++++++++++++++++++++" << std::endl;
	}		

	std::cout << "Data Memory: ";
	m_dataRam.Dump();
}
