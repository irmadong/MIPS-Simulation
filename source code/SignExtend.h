#ifndef __SIGNEXTEND_H__
#define __SIGNEXTEND_H__

#include <iostream>
#include <fstream>
#include <sstream>
#include <bitset>
#include <string>
#include <iomanip>

using namespace std;

class SignExtend {
	public:
		SignExtend();

		void print(bitset<16> input, bitset<32> extended, string output);
		bitset<32> extend(bitset<16> input);
};


#endif
