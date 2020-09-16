#ifndef __PROGRAMCOUNTER_H__
#define __PROGRAMCOUNTER_H__

#include <iostream>
#include <fstream>
#include <bitset>
#include <string>
#include <iomanip>

using namespace std;

/*
 * This class implements the PC component.
 */
class ProgramCounter {
	private:
		bitset<32> pc;

	public:
		/*
		 * Default constructor
		 */
		ProgramCounter();

		/*
		 * Mutator method for PC.
		 */
		void setPC(bitset<32> c);

		/*
		 * Accessor method for PC.
		 */
		bitset<32> getPC();

		/*
		 * This method prints the PC to the given output file
		 */
		void printPC(string outputFile);
};

#endif
