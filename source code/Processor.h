#ifndef __PROCESSOR_H__
#define __PROCESSOR_H__

#include "ProgramCounter.h"
#include "InstructionMemory.h"
#include "RegisterFile.h"
#include "DataMemory.h"
#include "ALU.h"
#include "MUX.h"
#include "shiftLeft2.h"
#include "ControlUnit.h"
#include "ALUControl.h"
#include "SignExtend.h"

#include <iostream>
#include <fstream>
#include <sstream>
#include <map>
#include <bitset>
#include <string>
#include <algorithm>
#include <vector>
using namespace std;
/*
 * Simulation class which simulates the operation of a five stage single cycle nonpipelined processor.
 */
class Processor
{
	private:
		ProgramCounter pc;
        InstructionMemory instMem;
		RegisterFile regFile;
        DataMemory dataMem;
		ALU ALU1;
		ALU ALU2;
		ALU ALU3;
        MUX Multiplexer1;
		MUX Multiplexer2;
		MUX Multiplexer3;
		MUX Multiplexer4;
		MUX Multiplexer5;
		shiftLeft2 Shift_left1;
		shiftLeft2 Shift_left2;
        ControlUnit conUnit;
        ALUControl aluCon;
        SignExtend signEx;
		bitset<32> currentInstruction;
		map<string, string> configFile;

	public:
    /*
		 * Typical-use constructor
		 */
		Processor(string inputFile);

    /*
		 * The execution method which simulates the operation of a five stage single cycle nonpipelined processor.
		 */
		void run();

    /*
		 * Accessor method for the configuration file
		 */
		map<string,string> getConfig(); 
};

#endif
