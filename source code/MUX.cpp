#ifndef __MUX_CPP__
#define __MUX_CPP__

#include "MUX.h"

MUX::MUX()
{
  tag = 0;
  controlValue = 0;
}

// constructor
MUX::MUX(int tag)
{
  this->tag = tag;
  this->controlValue = 0;
}

// setter for the control value of the MUX
void MUX::setControl(bitset<1> controlValue)
{
  this->controlValue = controlValue;
}


// this method is for selection between two inputs based on the control value of the MUX.
void MUX::select(bitset<32> input1, bitset<32> input2)
{
  // selection between input1 and input2
  if (controlValue == bitset<1>(0))
  {
    this->selected = input1;
  }
  else
  {
    this->selected = input2;
  }
}


void MUX::print(bitset<32> input1, bitset<32> input2, string output)
{
  // if write_to_file is false, output will be set to "", and thus print to console
  // instead of writing to an ouput file
  if (output == "")
  {
    cout << "---------------" << endl;
    cout << "MUX " << this->tag << endl;
    cout << "---------------" << endl;
    cout << "input1: 0x" << hex << setfill('0') << setw(8) << input1.to_ulong() << endl;
    cout << "input2: 0x" << hex << setfill('0') << setw(8) << input2.to_ulong() << endl;
    cout << "Control value: " << hex << controlValue.to_ulong() << endl;
    cout << "Selected input: 0x" << hex << setfill('0') << setw(8) << selected.to_ulong() << endl;
  }
  else
  {
    ofstream outputFile;
    outputFile.open(output.c_str(),ios_base::app);
    // check that the file was opened correctly
    if (!outputFile.is_open())
    {
      cerr << "MUX's outputfile could not be opened." << endl;
    }
    // write to file
    else
    {
      outputFile << "---------------" << endl;
      outputFile << "MUX " << this->tag << endl;
      outputFile << "---------------" << endl;
      outputFile << "input1: 0x" << hex << setfill('0') << setw(8) << input1.to_ulong() << endl;
      outputFile << "input2: 0x" << hex << setfill('0') << setw(8) << input2.to_ulong() << endl;
      outputFile << "Control value: " << controlValue << endl;
      outputFile << "Selected input: 0x" << hex << setfill('0') << setw(8) << selected.to_ulong() << endl;
      outputFile.close();
    }
  }
}
#endif
