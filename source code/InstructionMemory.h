#ifndef __INSTRUCTIONMEMORY_H__
#define __INSTRUCTIONMEMORY_H__

#include <iostream>
#include <fstream>
#include <sstream>
#include <bitset>
#include <string>
#include "ASMParser.h"
#include "Instruction.h"
#include "Opcode.h"
#include "RegisterTable.h"

using namespace std;

class InstructionMemory
{

   private:
        int nInstructions;
        bitset<32> instructions[999];
        string stringInstructions[100];

   public:
   	   InstructionMemory();
       InstructionMemory(string input);
       void readFile(string input);
       void print(string output);
       bitset<32> getInstruction(bitset<32> progCounterValue);
       bool isDone(bitset<32> progCounterValue);
       string getInstructionString(bitset<32> programCounter);



};

#endif
