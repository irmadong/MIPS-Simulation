#ifndef __REGISTERFILE_CPP__
#define __REGISTERFILE_CPP__

#include <iostream>
#include "RegisterFile.h"

using namespace std;

/*
 * Default constructor
 */
RegisterFile::RegisterFile()
{
  //initialize values in regTable to 0
  for(int i = 0; i < 32; i++) regTable[i] = bitset<32>(0);

	readData1 = bitset<32>(0);
	readData2 = bitset<32>(0);
	regWrite = bitset<1>(0);
}

/*
 * Typical-use Constructor which reads the input memory file, and
 * saves data values from it to mapped index in the register table based on each address
 */
 RegisterFile::RegisterFile(string inputFile)
 {
   for(int i = 0; i < 32; i++)
		regTable[i] = bitset<32>(0);
	ifstream in;
	in.open(inputFile.c_str());     // open the input file

	//if the given inputFile is 'bad', prints error message to the console and terminate the program
	if(in.bad())
	{
		cerr << "Error: RegisterFile cannot open the file '" << inputFile << "' for typical-use constructor" << endl;
		exit(1);
	}
  //if the given inputFile is in good condition, writes results to the inputFile
	else
	{
		string line;                                      //lines in input file
    int regNum;                                       //register number
    char colon;                                       //the separator colon
    long long dataHexValue;                           //data value in register

    //while there is a next line to read
		while(getline(in, line))
		{
			if(line == "" || line[0] == '#') continue;      //skip emtpy lines and lines contain only comments

      line = line.substr(0, line.find("#"));          //exclude the contents of comments of lines contains memory information
			istringstream ss(line);

			ss >> dec >> regNum;                             //read the register number in decimal format and save it to index
			ss >> colon;                                    //read the separator colon
			ss >> hex >> dataHexValue;                       //read data value in hexadecimal format and save it to regHexValue

			regTable[regNum] = bitset<32>(dataHexValue);  //put data value to mapped index from address in register table
		}
	}

	in.close();                                         // close the input file
 }

 /*
 * Accessor method for readData1.
 */
bitset<32> RegisterFile::getReadData1() { return readData1; }

/*
 * Accessor method for readData2.
 */
bitset<32> RegisterFile::getReadData2() { return readData2; }

/*
 * Acessor method for registers at the given index from Register Table
 */
bitset<32> RegisterFile::getRegister(int index) { return regTable[index]; }

/*
 * Accessor method for regWrite.
 */
bitset<1> RegisterFile::getRegWrite() { return regWrite; }

/*
 * Mutator method for regWrite.
 */
void RegisterFile::setRegWrite(bitset<1> other) { regWrite = other; }

/*
 * prints the content of the register table to the given output file.
 */
void RegisterFile::printRegisterFile(string outputFile)
{
  //if outputFile is not given, print the contents of register file to the console
	if(outputFile == "")
	{
    cout << "******************" << endl;
		cout << "Register File: " << endl;
    cout << "******************" << endl;
		for(int i = 0; i < 32; i++)
		{
			cout << dec << i << ":" << hex << setfill('0') << setw(8) << regTable[i].to_ulong() << endl;
		}
	}
  //if outputFile is given, prints the result to the given outputFile
	else
	{
		ofstream out;
		out.open(outputFile.c_str(), ios_base::app);     // open output file

		//if the given outputFile is 'bad', prints error message to the console and terminate the program
		if(out.bad())
		{
			cerr << "Error: RegisterFile cannot open the file '" << outputFile << "' for printing RegisterFile" << endl;
			exit(1);
		}
    	//if the given outputFile is in good condition, writes results to the outputFile
		else
		{
      out << "******************" << endl;
			out << "Register File: " << endl;
      out << "******************" << endl;
			// print register values to output file
			for(int i = 0; i < 32; i++)
			{
				out << dec << i << ":" << hex << setfill('0') << setw(8) << regTable[i].to_ulong() << endl;
			}
		}

		out.close();     // close the output file
	}
}

/*
 * prints the control unit value of regWrite to the given output file.
 */
void RegisterFile::printControlUnits(string outputFile)
{
  //if outputFile is not given, print the contents of data memory to the console

  if(outputFile == "") { cout << "regWrite: " << hex << regWrite.to_ulong() << endl; }
  //if outputFile is given, prints the result to the given outputFile
	else
	{
		ofstream out;
		out.open(outputFile.c_str(),ios_base::app);     // open output file

		//if the given outputFile is 'bad', prints error message to the console and terminate the program
		if(out.bad())
		{
			cerr << "Error: RegisterFile cannot open the file '" << outputFile << "' for printing ControlUnit" << endl;
			exit(1);
		}
    //if the given outputFile is in good condition, writes results to the outputFile
		else { out << "regWrite: " << hex << regWrite.to_ulong() << endl; }

		//out.close();     // close the output file
	}
}

/*
* The execution method which simulates the RegisterFile component based on the control unit value
*/
void RegisterFile::execute(bitset<5> readRegister1, bitset<5> readRegister2, bitset<5> writeRegister, bitset<32> writeData,bool writeStage, string outputFile)
{
  //if readRegister1 is given, get the value of it from register table
  if(readRegister1 != -1)
  	readData1 = regTable[(int) readRegister1.to_ulong()];

  //if readRegister2 is given, get the value of it from register table
	if(readRegister2 != -1) readData2 = regTable[(int) readRegister2.to_ulong()];

  //control unit value of regWrite is on
  if(regWrite.count() == 1 && writeStage == true){
   regTable[(int) writeRegister.to_ulong()] = writeData;

}

  //if outputFile is not given, prints the result to the console
	if(outputFile == "")
	{
    cout << "-------------------------" << endl;
		cout << "Register File Execution: " << endl;
    cout << "-------------------------" << endl;
    //if readRegister1 is given, print both register and data for it
		if(readRegister1 != -1)
		{
			cout << "readRegister1: 0x" << hex << setfill('0') << readRegister1.to_ulong() << endl;
			cout << "readData1: 0x" << hex << setfill('0') << setw(8) << readData1.to_ulong() << endl;
		}

    //if readRegister2 is given, print both register and data for it
		if(readRegister2 != -1)
		{
			cout << "readRegister2: 0x" << hex << setfill('0') << readRegister2.to_ulong() << endl;
			cout << "readData2: 0x" << hex << setfill('0') << setw(8) << readData2.to_ulong() << endl;
		}

    //if control unit value of regWrite is on, print both register and data for writing
	    if(writeStage)
	    {
	      cout << "writeRegister: 0x" << hex << setfill('0') << writeRegister.to_ulong() << endl;
	  		cout << "writeData: 0x" << hex << setfill('0') << setw(8) << writeData.to_ulong() << endl;
	    }
	}
  //if outputFile is given, prints the result to the given outputFile
	else
	{
		ofstream out;
		//out.open(outputFile.c_str(),ios_base::app);     // open output file

		out.open(outputFile.c_str(),ios_base::app);
		//if the given outputFile is 'bad', prints error message to the console and terminate the program
		if(out.bad())
		{
			cerr << "Error: RegisterFile cannot open the file '" << outputFile << "' for execution" << endl;
			exit(1);
		}
    //if the given outputFile is in good condition, writes results to the outputFile
		else
		{
          out << "---------------------------" << endl;
      		out << "Register File Execution: " << endl;
          out << "---------------------------" << endl;
      //if readRegister1 is given, print both register and data for it
  		if(readRegister1 != -1)
  		{
  			out << "readRegister1: 0x" << hex << setfill('0') << readRegister1.to_ulong() << endl;
  			out << "readData1: 0x" << hex << setfill('0') << setw(8) << readData1.to_ulong() << endl;
  		}

      //if readRegister2 is given, print both register and data for it
  		if(readRegister2 != -1)
  		{
  			out << "readRegister2: 0x" << hex << setfill('0') << readRegister2.to_ulong() << endl;
  			out << "readData2: 0x" << hex << setfill('0') << setw(8) << readData2.to_ulong() << endl;
  		}

      //if control unit value of regWrite is on, print both register and data for writing
      if(writeStage)
      {
        	out << "writeRegister: 0x" << hex << setfill('0') << writeRegister.to_ulong() << endl;
    		out << "writeData: 0x" << hex << setfill('0') << setw(8) << writeData.to_ulong() << endl;
      }
		}

		out.close();     // close the output file
	}
}

#endif
