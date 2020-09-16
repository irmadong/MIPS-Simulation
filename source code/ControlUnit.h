#ifndef __CONTROLUNIT_H__
#define __CONTROLUNIT_H__

#include "RegisterFile.h"
#include "DataMemory.h"
#include "MUX.h"
#include "ALUControl.h"

#include <bitset>
#include <string>
#include <iostream>
#include <fstream>
#include <sstream>
#include <iomanip>

class ControlUnit{
	private: 
		bitset<6>Opcode;
		bitset<1>RegDst;
		bitset<1>Jump;
		bitset<1>Branch;
		bitset<1>MemRead;
		bitset<1>MemToReg;
		bitset<1>ALUOp0;
		bitset<1>ALUOp1;
		bitset<1>MemWrite;
		bitset<1>ALUSrc;
		bitset<1>RegWrite;
		MUX Mux1;
		MUX Mux2;
		MUX Mux3;
		MUX Mux4;
		MUX Mux5;
		DataMemory Controldatamem;
		ALUControl ControlAlu;
		RegisterFile Controlregfile;
	public:
		ControlUnit(); // Default constructor

		ControlUnit(MUX &mux1, MUX &mux2, MUX &mux3, MUX &mux4, MUX &mux5, DataMemory &datamem,ALUControl &alucon,RegisterFile &regfile);  //Regular constructor for ControlUnit

		void setControlUnit(bitset<6>op,MUX &mux1, MUX &mux2, MUX &mux3, MUX &mux4, MUX &mux5, DataMemory &datamem,ALUControl &alucon,RegisterFile &regfile);  //Setter for the control units and the MUX, Datamemory, ALUcontrol and RegisterFile

		void printControlUnitsValue(string outputFile);  //Print the value of control units

		bitset<1> getRegDst();// Getter for regDst

		bitset<1> getJump();// Getter for jump

		bitset<1> getBranch();//Getter for branch

		bitset<1> getMemRead();//Getter for memRead

		bitset<1> getMemToReg();//Getter for memToReg

		bitset<1> getAluOp0();//Getter for aluOp0

		bitset<1> getAluOp1();//Getter for aluOp1

		bitset<1> getMemWrite();//Getter for memWrite

		bitset<1> getAluSrc();//Getter for aluSrc

		bitset<1> getRegWrite();//Getter for regWrite





};
#endif
