#pragma once

#include <cstring>

namespace processor
{
	class Ram
	{
		public:
			Ram() {}

			inline void Load(char data[]) { std::memcpy(m_data, data, 16); }
			inline char DataAt(char addr) { return m_data[addr]; }
			inline void SetDataAt(char addr, char value) { m_data[addr] = value; }
		private:
			char m_data[16] = { 0 };
	};
}
