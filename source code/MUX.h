#ifndef __MUX_H__
#define __MUX_H__

#include <iostream>
#include <fstream>
#include <sstream>
#include <bitset>
#include <string>
#include <iomanip>

using namespace std;

class MUX
{

  private:
      bitset<32> selected;
      bitset<1> controlValue;
      int tag;

  public:
      MUX();
      MUX(int tag);
      void setControl(bitset<1> controlValue);
      void select(bitset<32> input1, bitset<32> input2);
      void print(bitset<32> input1, bitset<32> input2, string output);
      bitset<32> getSelected() { return this->selected; } // getter for the input selected by the MUX.
};

#endif
