#ifndef __SIGNEXTEND_CPP__
#define __SIGNEXTEND_CPP__

#include "SignExtend.h"

// constructor
SignExtend::SignExtend() {}

/* this method takes a 16bit input, sign extends it and returns it,
while also writing to the given output file as a string */
bitset<32> SignExtend::extend(bitset<16> input)
{
  bitset<32> extended(0);

  for (int i = 0; i < 16; i++)
  {
    extended[i] = input[i];
  }

  for (int i = 16; i < 32; i++)
  {
    extended[i] = extended[15];
  }
  return extended;
}

void SignExtend::print(bitset<16> input, bitset<32> extended, string output)
{
  // if write_to_file is false, output will be set to "", and thus print to console
  // instead of writing to an ouput file
  if (output == "")
  {
    cout << "Sign Extend" << endl;
    cout << "Input: 0x" << hex << input.to_ulong() << endl;
    cout << "Result: 0x" << hex << extended.to_ulong() << endl;
  }
  // write to file
  else
  {
    ofstream outputFile;
    outputFile.open(output.c_str(),ios_base::app);

    if (!outputFile.is_open())
    {
      cerr << "SignExtend's ouputfile could not be opened." << endl;
    }
    else
    {
      outputFile << "Sign Extend" << endl;
      outputFile << "Input: 0x" << hex << input.to_ulong() << endl;
      outputFile << "Result: 0x" << hex << extended.to_ulong() << endl;
      outputFile.close();
    }
  }
}

#endif
