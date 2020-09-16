#ifndef __INSTRUCTIONMEMORY_CPP__
#define __INSTRUCTIONMEMORY_CPP__

#include "InstructionMemory.h"


InstructionMemory::InstructionMemory()
{
  nInstructions = 0;
}


// constructor
InstructionMemory::InstructionMemory(string input)
{
  this->nInstructions = 0;
  readFile(input);
}

// this method reads an input file and stores the instructions of that file into
// the private "instructions" array
void InstructionMemory::readFile(string input)
{
  ifstream in;
  in.open(input.c_str());
  if(in.bad()){
    cerr << "Error: Instruction Memory can not open the input file for readFile1." << endl;
    exit(1);
  }
  else{
    string line;
    int temp = 0;
    while( getline(in, line)){
      if(line == "" || line[0] == '#')
      {
        continue;
      }
      stringInstructions[temp++] = line.substr(0, line.find("#"));
    }
  }

  ASMParser parser = ASMParser(input);

  if (!parser.isFormatCorrect())
  {
    cerr << "Error: Instruction Memory can not open the input file for readFile2." << endl;
    return;
  }

  Instruction i = parser.getNextInstruction();
  string t;

  // iterate through the instructions of the input file
  while (i.getOpcode() != UNDEFINED)
  {
    t = i.getEncoding();
    instructions[nInstructions++] = (bitset<32>)t; // cast the instruction from string to bitset<32> and put in array
    i = parser.getNextInstruction();
  }
}

// method used to print to the output file
void InstructionMemory::print(string output)
{
  // if write_to_file is false, output will be set to "", and thus print to console
  // instead of writing to an ouput file
  if (output == "")
  {
    cout << "******************" << endl;
    cout << "InstructionMemory: " << endl;
    cout << "******************" << endl;
    for (int i = 0; i < nInstructions; i++)
    {
      cout << "0x" << hex << instructions[i].to_ulong() << endl;
    }
  }
  else
  {
    ofstream outputFile;
    outputFile.open(output.c_str(),ios_base::app);
    // check that the file was opened correctly
    if (!outputFile.is_open())
    {
      	cerr << "Error: Insruction Memory cannot open the file " << output << " for printing Instruction Memory" << endl;
        exit(1);
    }
    // write to file
    else
    {
      outputFile << "******************" << endl;
      outputFile << "InstructionMemory: " << endl;
      outputFile << "******************" << endl;
      for (int i = 0; i < nInstructions; i++)
      {
        outputFile << "0x" << hex << instructions[i].to_ulong() << endl;
      }
      //outputFile.close();
    }
  }
}

// instruction getter
bitset<32> InstructionMemory::getInstruction(bitset<32> progCounterValue)
{
  int instructionIndex = (int)(progCounterValue.to_ulong() - 0x400000)/4;
  return instructions[instructionIndex];
}

// determines if the value of the PC points to somewhere that is not
// in the array of instructions (i.e if it is out of bounds)

string InstructionMemory::getInstructionString(bitset<32> programCounter)
{
  int currentInstruction = (int) (programCounter.to_ulong() - 0x400000)/4;
  return stringInstructions[currentInstruction];
}

bool InstructionMemory::isDone(bitset<32> progCounterValue)
{
  int instructionIndex = (int)(progCounterValue.to_ulong() - 0x400000) / 4;

  return(instructionIndex >= nInstructions);

}

#endif
