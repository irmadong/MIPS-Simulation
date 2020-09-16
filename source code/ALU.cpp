#include "ALU.h"


/*
 * Default constructor for ALU class. Sets ALUresult to 0.
 */
ALU::ALU()
{
	ALUresult = bitset<32>(0);
	ALUcontrolLine = bitset<4>(0);
	zero = bitset<1>(0);
}

/*
 * Constructor for ALU class. Sets ALUresult to 0. Sets component number to
 * given integer value.
 */
ALU::ALU(int i)
{
	ALUresult = bitset<32>(0);
	ALUcontrolLine = bitset<4>(0);
	zero = bitset<1>(0);
	componentNumber = i;
}

void ALU::execute(bitset<32> code1, bitset<32> code2, string output)
{
	// the ALU instructions in bit
	bitset<4> AND ("0000");
	bitset<4> OR("0001");
	bitset<4>ADD("0010");
	bitset<4>SUB("0110");
	bitset<4>SLT("0111");
	bitset<4>NOR("1100");

	//SET ZERO




	if(ALUcontrolLine == AND) //and control
	{
		ALUresult = code1 & code2 ;
	}

	else if (ALUcontrolLine == OR) //or control
	{
		ALUresult = code1 | code2;
	}
	else if (ALUcontrolLine == ADD) //add control
	{
		int code1_dec = (int) code1.to_ulong();
		int code2_dec = (int) code2.to_ulong();
		int general = code1_dec + code2_dec;
		ALUresult = bitset<32> (general);
		\


	}
	else if (ALUcontrolLine == SUB) //sub control
	{
		int code1_dec = (int) code1.to_ulong();
		int code2_dec = (int) code2.to_ulong();
		int general = code1_dec - code2_dec;
		ALUresult = bitset<32> (general);



	}
	else if (ALUcontrolLine == SLT){ // slt control

		int code1_dec = (int) code1.to_ulong();
		int code2_dec = (int) code2.to_ulong();

		if(code1_dec < code2_dec)
		{
			ALUresult = bitset<32>(1);
		}
		else
		{
			ALUresult = bitset<32>(0);
		}
	}
	else if(ALUcontrolLine == NOR) //nor control
	{

		ALUresult = ~(code1| code2);
	}



	if(ALUresult.count() == 0)
	{
		zero = bitset<1>(1);
	}
	else
	{
		zero = bitset<1>(0);
	}

	if(output =="")
	{
		cout << "---------------" << endl;
		cout <<"ALU " << componentNumber << endl;
		cout << "---------------" << endl;
		cout << "Code 1: 0x" << hex << setw(8) << code1.to_ulong() << endl;
		cout << "Code 2: 0x" << hex << setw(8) << code2.to_ulong() << endl;
		cout << "ALUResult: 0x" << hex << setw(8) << ALUresult.to_ulong() << endl;
		cout << "Zero: 0x" << hex << zero.to_ulong() << endl;
	}
	else
	{
		//open the output file
		ofstream outputfile;
		outputfile.open(output.c_str(),ios_base::app);

		//Handle the exception
		if(outputfile.bad())
		{
			cerr << "Output file for ALU couldn't be opened!" << endl;
			exit(1);
		}

		else
		{
			outputfile << "---------------" << endl;
			outputfile <<"ALU " << componentNumber << endl;
			outputfile << "---------------" << endl;
			outputfile << "Code 1: 0x" << hex << setw(8) <<  code1.to_ulong() << endl;
			outputfile << "Code 2: 0x" << hex << setw(8) << code2.to_ulong() << endl;
			outputfile << "ALUResult: 0x" << hex << setw(8) << ALUresult.to_ulong() << endl;
			outputfile << "Zero: 0x" << hex << zero.to_ulong() << endl;
		}

		// close the output file
		outputfile.close();

	}




}



/*
 * Accessor method for ALUresult
 */
bitset<32> ALU::getALUresult()
{
	return ALUresult;
}


/*
 * Mutator method for ALUcontrolLine
 */
void ALU::setALUcontrolLine(bitset<4> c)
{
	ALUcontrolLine = c;
}

/*
 * Accessor method for ALUcontrolLine
 */
bitset<4> ALU::getALUcontrolLine()
{
	return ALUcontrolLine;
}


/*
 * Accessor method for zero
 */
bitset<1> ALU::getZero()
{
	return zero;
}
