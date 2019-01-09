#pragma once

// 4 Bit Accumulator
namespace processor
{
	class Accumulator
	{
	public:
		Accumulator() : m_value(0), m_carry(0) {}
		inline char Carry() { return m_carry; }
		inline char Value() { return m_value; }
		inline void SetValue(char value) { m_value = value; }
		inline void Add(char value)
		{
			char result = m_value + value;
			m_value = result;
			m_carry = (result >> 4) & 0x01;
		}

		inline void Sub(char value)
		{
			unsigned char twoComplent = (unsigned char)((~value + 0x01) << 4) >> 4;
			unsigned char result = m_value + twoComplent;
			m_value = (unsigned char)(result << 4) >> 4;
			m_carry = (result >> 4) & 0x01;
		}

	private:
		char m_value;
		char m_carry;
	};
}

