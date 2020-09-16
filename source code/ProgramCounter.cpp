#ifndef __PROGRAMCOUNTER_CPP__
#define __PROGRAMCOUNTER_CPP__

#include <iostream>
#include "ProgramCounter.h"

using namespace std;

/*
 * Default constructor which initialize PC with 0x400000
 */
ProgramCounter::ProgramCounter()
{
	pc = bitset<32>(0x400000);
}

/*
 * Mutator method for PC which updates pc as the given input 'other'.
 */
void ProgramCounter::setPC(bitset<32> other)
{
	this->pc = other;
}

/*
 * Accessor method for PC.
 */
bitset<32> ProgramCounter::getPC()
{
	return pc;
}

/*
 * This method prints the PC to the given output file
 */
void ProgramCounter::printPC(string outputFile)
{
	//if outputFile is not given, prints the result to the console
	if(outputFile == "")
	{
		cout << "-----------------------" << endl;
		cout <<"Program Counter" << endl;
		cout << "-----------------------" << endl;
		cout << "PC: 0x" << hex << setfill('0') << setw(8) << pc.to_ulong() << endl;
	}
	//if outputFile is given, prints the result to the given outputFile
	else
	{
		ofstream out;
		out.open(outputFile.c_str(),ios_base::app);     //open the given outputFile

		//if the given outputFile is 'bad', prints error message to the console and terminate the program
		if(out.bad())
		{
			cerr << "Error: ProgramCounter cannot open the file '" << outputFile << "'" << endl;
			exit(1);
		}
		//if the given outputFile is in good condition, writes results to the outputFile
		else
		{
			out << "-----------------------" << endl;
			out <<"Program Counter" << endl;
			out << "-----------------------" << endl;
			out << "PC: 0x" << hex << setfill('0') << setw(8) << pc.to_ulong() << endl;
		}

		out.close();     //close the outputFile
	}
}

#endif
