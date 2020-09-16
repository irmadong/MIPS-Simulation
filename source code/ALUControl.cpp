#include "ALUControl.h"

/*
 * Default constructor of the class. Sets the initial values
 * for ALUOp and opcode (zero).
 */
ALUControl::ALUControl()
{
	ALUOp = bitset<2>(0);
	opcode = bitset<6>(0);
}


/*
 * Mutator method for the opcode field.
 */
void ALUControl::setOpcode(bitset<6> c)
{
	opcode = c;
}

/*
 * Accessor method for the opcode field.
 */
bitset<6> ALUControl::getOpcode()
{
	return opcode;
}

/*
 * Mutator method for ALUOp field.
 */
void ALUControl::setALUOp(bitset<2> c)
{
	this->ALUOp = c;
}

/*
 * Accessor method for ALUOp field.
 */
bitset<2> ALUControl::getALUOp()
{
	return ALUOp;
}

/*
 * Sets the control line of given ALU with using the current
 * opcode and ALUOp control value.
 */
void ALUControl::setALUControl(ALU &alu){
    // lw & sw instruction
	if(ALUOp == bitset<2>("00"))
	{
		// set ALU to add operation
		alu.setALUcontrolLine(bitset<4>("0010"));
	}
	// beq instruction
	else if(ALUOp == bitset<2>("01"))
	{
		// set ALU to sub operation
		alu.setALUcontrolLine(bitset<4>("0110"));
	}
	// r-type operation
	else if(ALUOp == bitset<2>("10"))
	{
		// set ALU to corresponding operation depending
		// on the opcode

		// add instruction
		if(opcode == bitset<6>("100000"))
		{
			// set ALU to add operation
			alu.setALUcontrolLine(bitset<4>("0010"));
		}
		else if(opcode == bitset<6>("100010"))
		{
			// set ALU to sub operation
			alu.setALUcontrolLine(bitset<4>("0110"));
		}
		else if(opcode == bitset<6>("101010"))
		{
			// set ALU to slt operation
			alu.setALUcontrolLine(bitset<4>("0111"));
		}
	}
}


/*
 * This method prints the control values to the given output file.
 */
void ALUControl::printControlUnitValues(string output)
{
	// if output file is not given, print to cout
	if(output == "")
	{
		cout << "\tALUControl Values" << endl;
		cout << "ALUOp: 0x"  << hex << ALUOp.to_ulong() << endl;
		cout << "Opcode: 0x"  << hex << opcode.to_ulong() << endl;
	}
	else
	{

		// open output file
		ofstream out;
		out.open(output.c_str(),ios_base::app);

		// terminate if the output file is "bad"
		if(out.bad())
		{
			cerr << "Output file for ALUControl couldn't be opened!" << endl;
			exit(1);
		}

		else
		{
			out << "\tALUControl Values" << endl;
			out << "ALUOp: 0x"  << hex << ALUOp.to_ulong() << endl;
			out << "Opcode: 0x"  << hex << opcode.to_ulong() << endl;
		}

		// close the output file
		out.close();
	}
}
