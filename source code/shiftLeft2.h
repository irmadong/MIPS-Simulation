#ifndef __SHIFTLEFT2_H__
#define __SHIFTLEFT2_H__

#include <iostream>
#include <bitset>
#include <string>
#include <fstream>

using namespace std;

/*
 * This class implements 2 “shift left 2” units components.
 */
class shiftLeft2 {
	private:
		int componentNumber;

	public:
		/*
		 * Default Constructor.
		 */
		shiftLeft2();

		/*
		 * Typical-use Constructor
		 */
		shiftLeft2(int componentNumber);

		/*
		 * The execution method which performs left shift operation on the given input, and writes results to the given output file.
		 */
		bitset<32> execute(bitset<32> input, string outputFile);
};

#endif
