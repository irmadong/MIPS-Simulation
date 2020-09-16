#include "Processor.h"
#include "RegisterFile.h"
#include "ALU.h"
#include "ALUControl.h"
#include "InstructionMemory.h"
#include "DataMemory.h"
#include "ControlUnit.h"
#include "MUX.h"
#include "ProgramCounter.h"
#include "SignExtend.h"
#include "shiftLeft2.h"

void testALU()
{
	cout << "#######################################" << endl;
	cout << "##########    TESTING ALU   ###########" << endl;
	cout << "#######################################" << endl;

	ALU alu1(1);

	cout << "\tTesting constructor" << endl;
	cout << "ALU result: " << alu1.getALUresult() << endl;
	cout << "ALU control line: " << alu1.getALUcontrolLine().to_string() << endl;
	cout << "Zero: " <<  alu1.getZero().to_string() << endl;

	cout << "#######################################" << endl;

	bitset<4> ANDcontrol("0000");
	bitset<4> ORcontrol("0001");
	bitset<4> ADDcontrol("0010");
	bitset<4> SUBcontrol("0110");
	bitset<4> SLTcontrol("0111");
	bitset<4> NORcontrol("1100");

	bitset<32> b1("101101");
	bitset<32> b2("010100011");
	bitset<32> b3(-5);
	bitset<32> b4(10);
	bitset<32> b5(5);

	cout << "\tTesting execute with AND" << endl;
	alu1.setALUcontrolLine(ANDcontrol);
	alu1.execute(b1,b2, "");
	cout << "data1: " << b1 << endl;
	cout << "data2: " << b2 << endl;
	cout << "ALU result: " << alu1.getALUresult() << endl;
	cout << "ALU control line: " << alu1.getALUcontrolLine().to_string() << endl;
	cout << "Zero: " <<  alu1.getZero().to_string() << endl;

	cout << "#######################################" << endl;

	cout << "\tTesting execute with OR" << endl;
	alu1.setALUcontrolLine(ORcontrol);
	alu1.execute(b1,b2, "");
	cout << "data1: " << b1 << endl;
	cout << "data2: " << b2 << endl;
	cout << "ALU result: " << alu1.getALUresult() << endl;
	cout << "ALU control line: " << alu1.getALUcontrolLine().to_string() << endl;
	cout << "Zero: " <<  alu1.getZero().to_string() << endl;


	cout << "#######################################" << endl;

	cout << "\tTesting execute with ADD" << endl;
	alu1.setALUcontrolLine(ADDcontrol);
	alu1.execute(b1,b2, "");
	cout << "data1: " << b1 << endl;
	cout << "data2: " << b2 << endl;
	cout << "ALU result: " << alu1.getALUresult() << endl;
	cout << "ALU control line: " << alu1.getALUcontrolLine().to_string() << endl;
	cout << "Zero: " <<  alu1.getZero().to_string() << endl;
	cout << endl << endl;

	alu1.execute(b3,b4, "");
	cout << "data1: " << (int) b3.to_ulong() << endl;
	cout << "data2: " << (int) b4.to_ulong() << endl;
	cout << "ALU result: " << (int)  alu1.getALUresult().to_ulong() << endl;
	cout << "ALU control line: " << alu1.getALUcontrolLine() << endl;
	cout << "Zero: " <<  alu1.getZero().to_string() << endl;
	cout << endl << endl;


	alu1.execute(b3,b5, "");
	cout << "data1: " << (int) b3.to_ulong() << endl;
	cout << "data2: " << (int) b5.to_ulong() << endl;
	cout << "ALU result: " << (int) alu1.getALUresult().to_ulong() << endl;
	cout << "ALU control line: " << alu1.getALUcontrolLine() << endl;
	cout << "Zero: " <<  alu1.getZero().to_string() << endl;
	cout << endl << endl;


	cout << "#######################################" << endl;

	cout << "\tTesting execute with SUB" << endl;
	alu1.setALUcontrolLine(SUBcontrol);
	alu1.execute(b1,b2, "");
	cout << "data1: " << b1 << endl;
	cout << "data2: " << b2 << endl;
	cout << "ALU result: " << alu1.getALUresult() << endl;
	cout << "ALU control line: " << alu1.getALUcontrolLine().to_string() << endl;
	cout << "Zero: " <<  alu1.getZero().to_string() << endl;
	cout << endl << endl;

	alu1.execute(b3,b4, "");
	cout << "data1: " << (int) b3.to_ulong() << endl;
	cout << "data2: " << (int) b4.to_ulong() << endl;
	cout << "ALU result: " << (int)  alu1.getALUresult().to_ulong() << endl;
	cout << "ALU control line: " << alu1.getALUcontrolLine() << endl;
	cout << "Zero: " <<  alu1.getZero().to_string() << endl;
	cout << endl << endl;


	alu1.execute(b3,b3, "");
	cout << "data1: " << (int) b3.to_ulong() << endl;
	cout << "data2: " << (int) b3.to_ulong() << endl;
	cout << "ALU result: " << (int) alu1.getALUresult().to_ulong() << endl;
	cout << "ALU control line: " << alu1.getALUcontrolLine() << endl;
	cout << "Zero: " <<  alu1.getZero().to_string() << endl;
	cout << endl << endl;


	cout << "#######################################" << endl;

	cout << "\tTesting execute with SLT" << endl;
	alu1.setALUcontrolLine(SLTcontrol);
	alu1.execute(b1,b2, "");
	cout << "data1: " << b1 << endl;
	cout << "data2: " << b2 << endl;
	cout << "ALU result: " << alu1.getALUresult() << endl;
	cout << "ALU control line: " << alu1.getALUcontrolLine().to_string() << endl;
	cout << "Zero: " <<  alu1.getZero().to_string() << endl;
	cout << endl << endl;

	alu1.execute(b3,b4, "");
	cout << "data1: " << (int) b3.to_ulong() << endl;
	cout << "data2: " << (int) b4.to_ulong() << endl;
	cout << "ALU result: " << (int)  alu1.getALUresult().to_ulong() << endl;
	cout << "ALU control line: " << alu1.getALUcontrolLine() << endl;
	cout << "Zero: " <<  alu1.getZero().to_string() << endl;
	cout << endl << endl;

	alu1.execute(b4,b4, "");
	cout << "data1: " << (int) b4.to_ulong() << endl;
	cout << "data2: " << (int) b4.to_ulong() << endl;
	cout << "ALU result: " << (int)  alu1.getALUresult().to_ulong() << endl;
	cout << "ALU control line: " << alu1.getALUcontrolLine() << endl;
	cout << "Zero: " <<  alu1.getZero().to_string() << endl;
	cout << endl << endl;


	cout << "#######################################" << endl;

	cout << "\tTesting execute with NOR" << endl;
	alu1.setALUcontrolLine(NORcontrol);
	alu1.execute(b1,b2, "");
	cout << "data1: " << b1 << endl;
	cout << "data2: " << b2 << endl;
	cout << "ALU result: " << alu1.getALUresult() << endl;
	cout << "ALU control line: " << alu1.getALUcontrolLine().to_string() << endl;
	cout << "Zero: " <<  alu1.getZero().to_string() << endl;

}


int main()
{
	testALU();
}

