#ifndef __DATAMEMORY_H__
#define __DATAMEMORY_H__

#include <iostream>
#include <fstream>
#include <sstream>
#include <bitset>
#include <string>
#include <iomanip>

using namespace std;

/*
 * This class implements the Data Memory component.
 */
class DataMemory
{
   private:
     bitset<32> memTable[100];   //memory address table
		 bitset<32> readData;        //data to be written into memory
     bitset<1> memRead;          //control unit value which determines if read memory
		 bitset<1> memWrite;         //control unit value which determines if writes to memory
     long long offset;           //offset helps to convert values
    int size;             //size of memory address table

   public:
     /*
 		  * Default constructor
 		  */
     DataMemory();

     /*
 		  * Typical-use Constructor
 		  */
		 DataMemory(string inputFile);

     /*
      * Accessor method for readData.
      */
     bitset<32> getReadData();

     /*
      * Accessor method for memRead
      */
     bitset<1> getMemRead();

     /*
      * Accessor method for memWrite
      */
     bitset<1> getMemWrite();

     /*
      * Accessor method for memory at the given index from Memory Dddress Table
      */
     bitset<32> getMemValue(int index);

     /*
      * Mutator method for memRead.
      */
     void setMemRead(bitset<1> other);

     /*
      * Mutator method for memWrite.
      */
     void setMemWrite(bitset<1> other);

     /*
      * prints the content of the memory table to the given output file.
      */
     void printDataMemory(string outputFile);

     /*
      * prints the control unit values of memRead and memWrite to the given output file.
      */
     void printControlUnits(string outputFile);

     /*
 		 * The execution method which simulates the Data Memory component based on the control unit values
 		 */
     void execute(bitset<32> address, bitset<32> writeData, string outputFile);
 };

 #endif
