#ifndef __SHIFTLEFT2_CPP__
#define __SHIFTLEFT2_CPP__

#include <iostream>
#include "shiftLeft2.h"

using namespace std;

/*
 * Default Constructor.
 */
shiftLeft2::shiftLeft2()
{
	componentNumber = 0;
}

/*
 * Typical-use Constructor
 */
shiftLeft2::shiftLeft2(int componentNumber)
{
	this->componentNumber = componentNumber;
}

/*
 * The execution method which performs left shift operation on the given input, and writes results to the given output file.
 */
bitset<32> shiftLeft2::execute(bitset<32> input, string outputFile)
{
	bitset<32> answer = input << 2;    //shift left the given input 2 bits

	//if outputFile is not given, prints the result to the console
	if(outputFile == "")
	{
		cout << "\tShift Left" << componentNumber << endl;
		cout << "Input: 0x" << input.to_ulong() << endl;
		cout << "Result: 0x" << answer.to_ulong() << endl;
	}
	//if outputFile is given, prints the result to the given outputFile
	else
	{
		//open the given outputFile
		ofstream out;
		out.open(outputFile.c_str(), ios_base::app);

		//if the given outputFile is 'bad', prints error message to the console and terminate the program
		if(out.bad())
		{
			cerr << "Error: LeftShift2 cannot open the file '" << outputFile << "''" << endl;
			exit(1);
		}

		//if outputFile is in good condition, writes results to the outputFile
		else
		{
			out << "\tSign Extend" << endl;
			out << "Input: 0x" << input.to_ulong() << endl;
			out << "Result: 0x" << answer.to_ulong() << endl;
		}

		out.close();     //close the outputFile
	}

	return answer;     //return the result
}

#endif
