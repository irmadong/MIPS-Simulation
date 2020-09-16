#ifndef __REGISTERFILE_H__
#define __REGISTERFILE_H__

#include <iostream>
#include <iomanip>
#include <sstream>
#include <fstream>
#include <bitset>
#include <string>

using namespace std;

class RegisterFile
{
  private:
    bitset<32> regTable[32];     //Register Table
    bitset<32> readData1;        //First data to be written into register
		bitset<32> readData2;        //Second data to be written into register
		bitset<1> regWrite;          //control unit value which determines if writes to register

  public:
    /*
		 * Default constructor
		 */
		RegisterFile();

    /*
		 * Typical-use constructor
		 */
		RegisterFile(string inputFile);

    /*
		 * Accessor method for readData1.
		 */
		bitset<32> getReadData1();

    /*
		 * Accessor method for readData2.
		 */
		bitset<32> getReadData2();

    /*
		 * Acessor method for registers at the given index from Register Table
		 */
		bitset<32> getRegister(int index);

    /*
		 * Accessor method for regWrite.
		 */
		bitset<1> getRegWrite();

    /*
		 * Mutator method for regWrite.
		 */
		void setRegWrite(bitset<1> other);

    /*
     * prints the content of the register table to the given output file.
     */
		void printRegisterFile(string outputFile);

    /*
     * prints the control unit value of regWrite to the given output file.
     */
		void printControlUnits(string outputFile);

    /*
    * The execution method which simulates the RegisterFile component based on the control unit value
    */
		void execute(bitset<5> readRegister1, bitset<5> readRegister2, bitset<5> writeRegister, bitset<32> writeData, bool writeStage, string outputFile);
};

#endif
