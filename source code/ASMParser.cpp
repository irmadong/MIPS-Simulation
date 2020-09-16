#include "ASMParser.h"

ASMParser::ASMParser(string filename)
  // Specify a text file containing MIPS assembly instructions. Function
  // checks syntactic correctness of file and creates a list of Instructions.
{
  Instruction i;
  myFormatCorrect = true;
  int counter = 0;
  myLabelAddress = 0x400000;
  ifstream in;
  in.open(filename.c_str());
  if(in.bad()){
    myFormatCorrect = false;
  }

  else{
    string line;
    while( getline(in, line)){
      if(line == "" || line[0] == '#')
      {
        continue;
      }
      string opcode("");
      string operand[80];
      int operand_count = 0;

      getTokens(line, opcode, operand, operand_count);

      if(opcode.length() == 0 && operand_count != 0){
        // No opcode but operands
        myFormatCorrect = false;
        break;
      }

      Opcode o = opcodes.getOpcode(opcode);
      if(o == UNDEFINED){
        // invalid opcode specified
        myFormatCorrect = false;
        break;
      }
      bool success = getOperands(i, o, operand, operand_count);
      if(!success){
        myFormatCorrect = false;
        break;
      }
      if(i.getOpcode() == BEQ)
      {
        int beqPC = 0x400000 + (counter*4);
        beqPC += 4;
        int beqAddress = i.getImmediate();
        int relativeAddress = (beqAddress - beqPC) >> 2;
        i.setValues(i.getOpcode(), i.getRS(), i.getRT(), i.getRD(), relativeAddress);
      }

      string encoding = encode(i);
      i.setEncoding(encoding);

      myInstructions.push_back(i);
      counter++;
    }
  }


  myIndex = 0;
}


Instruction ASMParser::getNextInstruction()
  // Iterator that returns the next Instruction in the list of Instructions.
{
  if(myIndex < (int)(myInstructions.size())){
    myIndex++;
    return myInstructions[myIndex-1];
  }

  Instruction i;
  return i;

}

void ASMParser::getTokens(string line,
			       string &opcode,
			       string *operand,
			       int &numOperands)
  // Decomposes a line of assembly code into strings for the opcode field and operands,
  // checking for syntax errors and counting the number of operands.
{
    // locate the start of a comment
    string::size_type idx = line.find('#');
    if (idx != string::npos) // found a ';'
	line = line.substr(0,idx);
    int len = line.length();
    opcode = "";
    numOperands = 0;

    if (len == 0) return;
    int p = 0; // position in line

    // line.at(p) is whitespace or p >= len
    while (p < len && isWhitespace(line.at(p)))
	p++;
    // opcode starts
    while (p < len && !isWhitespace(line.at(p)))
    {
	opcode = opcode + line.at(p);
	p++;
    }
    //    for(int i = 0; i < 3; i++){
    int i = 0;
    while(p < len){
      while ( p < len && isWhitespace(line.at(p)))
	p++;

      // operand may start
      bool flag = false;
      while (p < len && !isWhitespace(line.at(p)))
	{
	  if(line.at(p) != ','){
	    operand[i] = operand[i] + line.at(p);
	    flag = true;
	    p++;
	  }
	  else{
	    p++;
	    break;
	  }
	}
      if(flag == true){
	numOperands++;
      }
      i++;
    }


    idx = operand[numOperands-1].find('(');
    string::size_type idx2 = operand[numOperands-1].find(')');

    if (idx == string::npos || idx2 == string::npos ||
	((idx2 - idx) < 2 )){ // no () found
    }
    else{ // split string
      string offset = operand[numOperands-1].substr(0,idx);
      string regStr = operand[numOperands-1].substr(idx+1, idx2-idx-1);

      operand[numOperands-1] = offset;
      operand[numOperands] = regStr;
      numOperands++;
    }



    // ignore anything after the whitespace after the operand
    // We could do a further look and generate an error message
    // but we'll save that for later.
    return;
}

bool ASMParser::isNumberString(string s)
  // Returns true if s represents a valid decimal integer
{
  if(s.compare(0,2,"0x") == 0 || s.compare(0,2, "0X") == 0)
  {
    return true;
  }

    int len = s.length();
    if (len == 0) return false;
    if ((isSign(s.at(0)) && len > 1) || isDigit(s.at(0)))
    {
	// check remaining characters
	for (int i=1; i < len; i++)
	{
	    if (!isdigit(s.at(i))) return false;
	}
	return true;
    }
    return false;
}


int ASMParser::cvtNumString2Number(string s)
  // Converts a string to an integer.  Assumes s is something like "-231" and produces -231
{
    if(s.compare(0,2,"0x") == 0 || s.compare(0,2, "0X") == 0)
    {
      stringstream string_stream;
      string_stream << s;
      long long value;
      string_stream >> hex >> value;
      return (int) value;
    }
    if (!isNumberString(s))
    {
	cerr << "Non-numberic string passed to cvtNumString2Number"
		  << endl;
	return 0;
    }
    int k = 1;
    int val = 0;
    for (int i = s.length()-1; i>0; i--)
    {
	char c = s.at(i);
	val = val + k*((int)(c - '0'));
	k = k*10;
    }
    if (isSign(s.at(0)))
    {
	if (s.at(0) == '-') val = -1*val;
    }
    else
    {
	val = val + k*((int)(s.at(0) - '0'));
    }
    return val;
}


bool ASMParser::getOperands(Instruction &i, Opcode o,
			    string *operand, int operand_count)
  // Given an Opcode, a string representing the operands, and the number of operands,
  // breaks operands apart and stores fields into Instruction.
{

  if(operand_count != opcodes.numOperands(o))
  {
    return false;
  }

  int rs, rt, rd, imm;
  imm = 0;
  rs = rt = rd = NumRegisters;

  int rs_p = opcodes.RSposition(o);
  int rt_p = opcodes.RTposition(o);
  int rd_p = opcodes.RDposition(o);
  int imm_p = opcodes.IMMposition(o);

  if(rs_p != -1){
    rs = registers.getNum(operand[rs_p]);
    if(rs == NumRegisters)
      return false;
  }

  if(rt_p != -1){
    rt = registers.getNum(operand[rt_p]);
    if(rt == NumRegisters)
      return false;

  }

  if(rd_p != -1){
    rd = registers.getNum(operand[rd_p]);
    if(rd == NumRegisters)
      return false;

  }

  if(imm_p != -1){

    if(isNumberString(operand[imm_p])){  // does it have a numeric immediate field?
      imm = cvtNumString2Number(operand[imm_p]);

    }
    else{
      if(opcodes.isIMMLabel(o)){  // Can the operand be a label?
	// Assign the immediate field an address
      stringstream str;
      str << operand[imm_p];
      str >> hex >> imm;
      }
      else  // There is an error
	      return false;
    }

  }

  i.setValues(o, rs, rt, rd, imm);

  return true;
}


string ASMParser::convertToBinary(int decimal, int stringSize)
// Given a decimal integer and the desired bit size,
// returns a string that is the binary representation of that integer
{
  bitset <26> bits(decimal);
  return bits.to_string().substr(26-stringSize,stringSize);
}


string ASMParser::encode(Instruction i)
  // Given a valid instruction, returns a string representing the 32 bit MIPS binary encoding
  // of that instruction.
{
  Opcode instrOpcode = i.getOpcode();
  InstType instrType = opcodes.getInstType(instrOpcode);
  string result = "";


  switch(instrType) {

    case RTYPE:
    {
      // RTYPE (register) - opcode 000000
      // [opcode (6 bits)] [rs (5 bits)] [rt (5 bits)] [rd (5 bits)] [shamt (5 bits)] [funct (6 bits)]

      // Append the opcode to the beginning of the result string
      result.append( opcodes.getOpcodeField(instrOpcode) );

      // Append rs to the string (directly after opcode)
      bitset<5> rs_bit_r(i.getRS());
      result.append( rs_bit_r.to_string());

      // Append rt to the string (directly after rs)
      bitset<5> rt_bit_r(i.getRT());
      result.append( rt_bit_r.to_string());


      // Append rd to the string (directly after rt)
      bitset<5> rd_bit_r(i.getRD());
      result.append( rd_bit_r.to_string());


      // Append shamt to the string (directly after rd)
      bitset<5> imm_bit_r(i.getImmediate());
      result.append( imm_bit_r.to_string());

      // Append funct code to the string (directly after shamt)
      result.append( opcodes.getFunctField(instrOpcode) );
      break;
    }

    case ITYPE:
    {
      // ITYPE () data transfer
      // [opcode (6 bits)] [rs (5 bits)] [rt (5 bits)] [address (16 bits)]

      // Append the opcode to the beginning of the result string
      result.append( opcodes.getOpcodeField(instrOpcode) );

      // Append rs to the string (directly after opcode)
      bitset<5> rs_bit_i(i.getRS());
      result.append( rs_bit_i.to_string());

      // Append rt to the string (directly after rs)
      bitset<5> rt_bit_i(i.getRT());
      result.append( rt_bit_i.to_string());

      // Append shamt to the string (directly after rd)
      bitset<16> imm_bit_i(i.getImmediate());
      result.append( imm_bit_i.to_string());
      break;
    }

    case JTYPE:
    {
      // JTYPE (jump) - opcode 00001x (NOT branch)
      // [opcode (6 bits)] [address (26 bits)]

      // Append the opcode to the beginning of the result string
      result.append( opcodes.getOpcodeField(instrOpcode) );

      // Append shamt to the string (directly after rd)

      bitset<26> imm_bit_j(i.getImmediate()>>2);
      result.append( imm_bit_j.to_string());
      break;
    }


  }


  return result;
}
