#ifndef __ALU_H__
#define __ALU_H__

#include <iostream>
#include <fstream>
#include <sstream>
#include <bitset>
#include <string>
#include <iomanip>
using namespace std;
class ALU {
	private: 
		bitset<32> ALUresult; // the field to hold the result of ALU calculation 
		bitset<4> ALUcontrolLine; // the control line to 
		bitset<1> zero;           // ZERO 
		int componentNumber;      // the marker of the ALU
		
	public:
		ALU();  // It is the default constructor of ALU and the ALUresult is set to be 0

		
		ALU(int i); // Constructor for ALU class. It sets the ALUresult to 0. Then mark the ALU.

		
		void execute(bitset<32> code1, bitset<32> code2, string output); // Do the execution for data1 and data2 based on ALUcontrolLine and give the output.
		
		bitset<32> getALUresult(); //The method gets the ALUresult after the calculation.

		
		void setALUcontrolLine(bitset<4> c); // Setter for ALUcontrolLine

		
		bitset<4> getALUcontrolLine(); //Getter for ALUcontrolLine

		
		bitset<1> getZero(); //Getter for zero
};
#endif
