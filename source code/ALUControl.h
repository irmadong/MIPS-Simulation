#ifndef __ALUCONTROL_H__
#define __ALUCONTROL_H__

#include "ALU.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include <bitset>
#include <string>
#include <iomanip>

using namespace std;

/*
 * This class implements the component that is responsible for controlling 
 * the ALU component. It decodes the ALU control value passed from the control unit 
 * and then sets the given ALU to do the corresponding operation.
 */
class ALUControl {
	private:
		bitset<2> ALUOp;
		bitset<6> opcode;

	public:
		/*
		 * Default constructor of the class. Sets the initial values
		 * for ALUOp and opcode (zero).
		 */
		ALUControl();
		/*
		 * Mutator method for the opcode field.
		 */
		void setOpcode(bitset<6> c);

		/*
		 * Accessor method for the opcode field.
		 */
		bitset<6> getOpcode();

		/*
		 * Mutator method for ALUOp field.
		 */
		void setALUOp(bitset<2> c);

		/*
		 * Accessor method for ALUOp field.
		 */
		bitset<2> getALUOp();

		/*
		 * Sets the control line of given ALU with using the current
		 * opcode and ALUOp control value.
		 */
		void setALUControl(ALU &alu);

		/*
		 * This method prints the control values to the given output file.
		 */
		void printControlUnitValues(string output);



};


#endif
