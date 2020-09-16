#ifndef __DATAMEMORY_CPP__
#define __DATAMEMORY_CPP__

#include "DataMemory.h"

/*
 * Default constructor
 */
DataMemory::DataMemory()
{
  //initialize values in memTable to 0
  for(int i = 0; i < 100; i++) memTable[i] = bitset<32>(0);

  readData = bitset<32>(0);
  memRead = bitset<1>(0);
  memWrite = bitset<1>(0);
offset = -1;
  size = 0;
}

/*
 * Typical-use Constructor which reads the input memory file, and
 * saves data values from it to mapped index in the memory address table based on each address
 */
DataMemory::DataMemory(string inputFile)
{
  	offset = -1;
	size = 0;
	for(int i = 0; i < 100; i++){//initialize all values to 0
		memTable[i] = bitset<32>(0);
	}
	ifstream in;
	in.open(inputFile.c_str());                   //open the inputFile

  //if the given inputFile is 'bad', prints error message to the console and terminate the program
	if(in.bad())
	{
		cerr << "Error: DataMemory cannot open the file '" << inputFile << "' for typical-use constructor" << endl;
		exit(1);
	}
  //if the given inputFile is in good condition, writes results to the inputFile
	else
	{
		string line;                                 //lines in the input memory file
    long long hexAddress;                        //memory address
    char colon;                                  //the separator colon
    long long dataHexValue;                      //data value in memory address
    int index;                                   //index of memory address table

    //while there is a next line to read
		while(getline(in, line))
		{
			if(line == "" || line[0] == '#') continue;  //skip emtpy lines and lines contain only comments

			line = line.substr(0, line.find("#"));      //exclude the contents of comments of lines contains memory information
			istringstream ss(line);                     //using istringstream for converting contents of line to numbers

			ss >> hex >> hexAddress;                    //read address in hexadecimal format and save it to hexAddress
			ss >> colon;                                //read the separator colon, save it to colon
			ss >> hex >> dataHexValue;                  //read data value in hexadecimal format and save it to dataHexValue

			if(offset == -1) offset = hexAddress;       //updates offset to hexAddress if it is on the first line

			index = (hexAddress-offset)/4;              //map address in memory file to index of memory address table
			memTable[index] = bitset<32>(dataHexValue); //put data value to mapped index from address in memory address table
			size++;
		}
	}

	in.close();                                     //close the inputFile
}

/*
 * Accessor method for readData.
 */
bitset<32> DataMemory::getReadData() { return readData; }

/*
 * Accessor method for memRead
 */
bitset<1> DataMemory::getMemRead() { return memRead; }

/*
 * Accessor method for memWrite
 */
bitset<1> DataMemory:: getMemWrite() { return memWrite; }

/*
 * Accessor method for memory at the given index from Memory Dddress Table
 */
bitset<32> DataMemory:: getMemValue(int index) { return memTable[index]; }

/*
 * Mutator method for memRead.
 */
void DataMemory::setMemRead(bitset<1> other) { memRead = other; }

/*
 * Mutator method for memWrite.
 */
void DataMemory::setMemWrite(bitset<1> other) { memWrite = other; }

/*
 * prints the content of the memory table to the given output file.
 */
void DataMemory::printDataMemory(string outputFile)
{
  //if outputFile is not given, print the contents of data memory to the console
  if(outputFile == "")
	{
    cout << "******************" << endl;
		cout << "Data Memory:" << endl;
    cout << "******************" << endl;
		for(int i = 0; i < size; i++)
		{
			cout << hex << offset+(i*4) << ":"<< setfill('0') << setw(8) << memTable[i].to_ulong() << endl;
		}
	}
  //if outputFile is given, prints the result to the given outputFile
	else
	{
		ofstream out;
		out.open(outputFile.c_str(), ios_base::app);     //open the output file

		//if the given outputFile is 'bad', prints error message to the console and terminate the program
		if(out.bad())
		{
			cerr << "Error: Data Memory cannot open the file '" << outputFile << "' for printing Data Memory" << endl;
			exit(1);
		}
    //if the given outputFile is in good condition, writes results to the outputFile
		else
		{
      out << "***************" << endl;
			out << "Data Memory:" << endl;
      out << "***************" << endl;

			// print register values to output file
			for(int i = 0; i < size; i++)
			{
				out << hex << offset+(i*4) << ":"<< setfill('0') << setw(8) << memTable[i].to_ulong() << endl;
			}
		}

		out.close();     //close the output file
	}
}

/*
 * prints the control unit values of memRead and memWrite to the given output file.
 */
void DataMemory::printControlUnits(string outputFile)
{
  //if outputFile is not given, print the contents of data memory to the console
  if(outputFile == "")
	{
		cout<<"memRead: "<<getMemRead()<<endl;
		cout<<"memWrite: "<<getMemWrite()<<endl;
	}
  //if outputFile is given, prints the result to the given outputFile
	else
	{
		ofstream out;
		out.open(outputFile.c_str(),ios_base::app);     // open output file

		//if the given outputFile is 'bad', prints error message to the console and terminate the program
		if(out.bad())
		{
			cerr << "Error: ProgramCounter cannot open the file '" << outputFile << "' for printing control unit values" << endl;
			exit(1);
		}
    //if the given outputFile is in good condition, writes results to the outputFile
		else
		{
        out<<"memRead: "<<getMemRead()<<endl;
  		out<<"memWrite: "<<getMemWrite()<<endl;
		}

		out.close();     // close the output file
	}
}

/*
* The execution method which simulates the Data Memory component based on the control unit values
*/
void DataMemory::execute(bitset<32> address, bitset<32> writeData, string outputFile)
{
  int index;                                   //index of memTable
  long long longlongAddr=address.to_ullong();   //convert writeData to long long vairable

  //control unit value of memWrite is on
  if(getMemWrite()==1)
  {
  	index = (longlongAddr-offset)/4;            //map address to index of memTable
  	memTable[index]=writeData;                 //write to that index of memTable
  	readData=memTable[index];                  //updates readData
  }

  //control unit value of MemRead is on
  if(getMemRead() == 1)
  {
  		index = (longlongAddr-offset)/4; //map address to index of memTable
  		readData=memTable[index];         //updates readData
  }

  //if outputFile is not given, prints the result to the console

  if(outputFile == "")
	{
    cout << "----------------------" << endl;
		cout << "Data Memory Execution:" << endl;
    cout << "----------------------" << endl;
		cout << "Address: 0x" << hex <<  address.to_ulong() << endl;
    if(getMemRead()==1)
		{
			cout << "ReadData: 0x" << hex << readData.to_ulong() << endl;
		}
		if(getMemWrite()==1)
		{
			cout << "WriteData: 0x" << hex << writeData.to_ulong() << endl;
		}
	}
  //if outputFile is given, prints the result to the given outputFile
	else
	{
		ofstream out;
		out.open(outputFile.c_str(),ios_base::app);     // open output file


		//if the given outputFile is 'bad', prints error message to the console and terminate the program
		if(out.bad())
		{
			cerr << "Error: DataMemory cannot open the file '" << outputFile << "' for execution" << endl;
			exit(1);
		}
    //if the given outputFile is in good condition, writes results to the outputFile
		else
		{
      out << "----------------------" << endl;
    	out << "Data Memory Execution:" << endl;
      out << "----------------------" << endl;
  		out << "Address: 0x" << hex <<  address.to_ulong() << endl;

      if(getMemRead()==1)
  		{
  			out << "ReadData: 0x" << hex << readData.to_ulong() << endl;
  		}
  		if(getMemWrite()==1)
  		{
  			out << "WriteData: 0x" << hex << writeData.to_ulong() << endl;
  		}
		}

		out.close();     // close the output file
	}
}
#endif
