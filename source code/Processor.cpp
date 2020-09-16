
#include "Processor.h"
using namespace std;
Processor::Processor(string filename)
{
	// open the input file
	ifstream in;
	in.open(filename.c_str());
	int i =0;

// Handle the exception
if(in.bad())
	{

		cerr << "Error:configfile cannot be opened" << endl;

		cerr << "Error:configurationuration file cannot be opened" << endl;

		exit(1);
	}
	else
	{
		string inputline;
		string delimiter = "=";
		while(getline(in, inputline))
		{
       // remove whitespace
		  inputline.erase(remove(inputline.begin(), inputline.end(), ' '), inputline.end());

			// ignore empty and comment inputlines
			if(inputline == "" || inputline[0] == '#')
				continue;

			inputline = inputline.substr(0, inputline.find("#"));
			string param = inputline.substr(0, inputline.find(delimiter));
			string val = inputline.substr(inputline.find(delimiter)+1, inputline.size());
			configFile[param] = val;
			i++;
		}
	}

	// close the input file
	in.close();


	// if write to file is false, set output file to empty string
  if(configFile["write_to_file"] == "false")
	{
		configFile["output_file"] = "";

	cout<<"The output_file is " << configFile["output_file"]<<endl;
  }
	// clear any content in the output file
	else
	{
		ofstream out;

		out.open(configFile["output_file"], ofstream::out | ofstream::trunc);
		out.close();
	}

	regFile = RegisterFile(configFile["register_file_input"]);

  ALU1 = ALU(1);
	ALU2 = ALU(2);
	ALU3 = ALU(3);

	aluCon = ALUControl();

	instMem = InstructionMemory(configFile["program_input"]);

	dataMem = DataMemory(configFile["memory_contents_input"]);

	Multiplexer1 = MUX(1);
	Multiplexer2 = MUX(2);
	Multiplexer3 = MUX(3);
	Multiplexer4 = MUX(4);
	Multiplexer5 = MUX(5);

	conUnit = ControlUnit(Multiplexer1, Multiplexer2, Multiplexer3, Multiplexer4, Multiplexer5, dataMem, aluCon,regFile);

	pc = ProgramCounter();

	signEx = SignExtend();

	Shift_left1 = shiftLeft2(1);
	Shift_left2 = shiftLeft2(2);
}


/*
 * The main function of the program. Until program termination,
 * in a while loop, this method fetches the instruction from
 * instruction memory with respect to current program counter
 * and executes it./Users/jd8zv/Desktop/test/ProgramCounter.cpp
 */
void Processor::run()
{
	// ALU1 & ALU2 only perform addition
	ALU1.setALUcontrolLine(bitset<4>("0010"));
	ALU2.setALUcontrolLine(bitset<4>("0010"));

	// run simulation until all instructions are run
	while(!instMem.isDone(pc.getPC()))
	{
		// fetch the instrution
		currentInstruction = instMem.getInstruction(pc.getPC());

		//print the instruction
		if(configFile["output_file"] == "")
		{

			cout << "CURRENT INSTRUCTION: " << instMem.getInstructionString(pc.getPC()) << endl;
		}
		else
		{
			// open output file
			ofstream out;
			out.open(configFile["output_file"],ios_base::app);

			// terminate if the output file is "bad"
			if(out.bad())
			{
				cerr << "Output file for Registers couldn't be opened!" << endl;
				exit(1);
			}

			else
			{
				out << "CURRENT INSTRUCTION: " << instMem.getInstructionString(pc.getPC()) << endl;
			}

			// close the output file
			//out.close();
		}

		// print PC
		pc.printPC(configFile["output_file"]);

		// split instruction to its parts
		bitset<6> inst_31_26(0);
		for(int i = 26; i <=31; i++)
			inst_31_26[i-26] = currentInstruction[i];

		bitset<5> inst_25_21(0);
		for(int i = 21; i <=25; i++)
			inst_25_21[i-21] = currentInstruction[i];

		bitset<5> inst_20_16(0);
		for(int i = 16; i <=20; i++)
			inst_20_16[i-16] = currentInstruction[i];

		bitset<5> inst_15_11(0);
		for(int i = 11; i <=15; i++)
			inst_15_11[i-11] = currentInstruction[i];

		bitset<16> inst_15_0(0);
		for(int i = 0; i <=15; i++)
			inst_15_0[i-0] = currentInstruction[i];

		bitset<6> inst_5_0(0);
		for(int i = 0; i <=5; i++)
			inst_5_0[i-0] = currentInstruction[i];

		bitset<26> inst_25_0(0);
		for(int i = 0; i <=25; i++)
			inst_25_0[i-0] = currentInstruction[i];

		bitset<32> inst_15_0_extended = signEx.extend(inst_15_0);
		signEx.print(inst_15_0, inst_15_0_extended, configFile["output_file"]);

		// (Instruction Decode) Passing the opcode to Control Unit, the Control Unit
		// then updates the control vALUes of other components with respect to this opcode.
		conUnit.setControlUnit(inst_31_26,  Multiplexer1, Multiplexer2, Multiplexer3, Multiplexer4, Multiplexer5, dataMem, aluCon,regFile);

		conUnit.printControlUnitsValue(configFile["output_file"]);

		// (Instruction Decode) Passing the required bits to Register File and executing
		// read operation
		regFile.execute(inst_25_21, inst_20_16, bitset<5>(-1), bitset<32>(-1),false,configFile["output_file"]);
		bitset<32> readData1 = regFile.getReadData1();
		bitset<32> readData2 = regFile.getReadData2();

		// (Execute) Taking the 15-0 bits of the instructions and results from
		// the Register File, passing the vALUes and executing the specified operation
		// using ALU3 with the help of ALU Control and MUX5

		aluCon.setOpcode(inst_5_0);

		aluCon.setALUControl(ALU3);

		aluCon.printControlUnitValues(configFile["output_file"]);

		Multiplexer5.select(readData2, inst_15_0_extended);
		Multiplexer5.print(readData2, inst_15_0_extended, configFile["output_file"]);
		bitset<32> Multiplexer5_res = Multiplexer5.getSelected();

		ALU3.execute(readData1, Multiplexer5_res, configFile["output_file"]);

		bitset<32> ALUResult = ALU3.getALUresult();
		bitset<1> zero = ALU3.getZero();


		// (Memory Access) Passing the ALU result and write data to Data Memory object
		// and executing its operation.
		dataMem.execute(ALUResult, readData2, configFile["output_file"]);

		bitset<32> readData = dataMem.getReadData();

		// (Writeback) Taking the result from the Data memory and writing data back
		// to registers with the help of MUX4 and MUX1.
		Multiplexer1.select(bitset<32>(inst_20_16.to_string()), bitset<32>(inst_15_11.to_string()));
		Multiplexer1.print(bitset<32>(inst_20_16.to_string()), bitset<32>(inst_15_11.to_string()), configFile["output_file"]);
		bitset<5> writeRegister(0);

		for(int i = 0; i < 5; i++) writeRegister[i] = Multiplexer1.getSelected()[i];

		Multiplexer4.select(ALUResult, readData);
		Multiplexer4.print(ALUResult, readData, configFile["output_file"]);
		bitset<32> writeData = Multiplexer4.getSelected();
		regFile.execute(bitset<5>(-1), bitset<5>(-1), writeRegister, writeData,true, configFile["output_file"]);

		// (PC update) Updating the PC with the help of ALU1, ALU2, MUX2 and MUX3
		// with respect to instruction.

		// calculate PC+4
		ALU1.execute(pc.getPC(), bitset<32>(4),configFile["output_file"]);
		bitset<32> ALU1_result = ALU1.getALUresult();

		// Shift-left 1
		bitset<32> temp = bitset<32>(inst_25_0.to_string());
		temp = Shift_left1.execute(temp, configFile["output_file"]);
		bitset<28> inst_25_0_shifted;
		for(int i = 0; i < 28; i++)
			inst_25_0_shifted[i] = temp[i];

		//calculate jump address
		bitset<32> jump_address(0);

		for(int i = 31; i >= 28; i--)
			jump_address[i] = ALU1_result[i];
		for(int i = 27; i >= 0; i--)
			jump_address[i] = inst_25_0_shifted[i];

		// Shift-left 2
		bitset<32> inst_15_0_extended_shifted = Shift_left2.execute(inst_15_0_extended, configFile["output_file"]);

		// calculate branch address
		ALU2.execute(ALU1_result, inst_15_0_extended_shifted, configFile["output_file"]);

		bitset<32> ALU2_result = ALU2.getALUresult();

		//cout << "Branch address: " << ALU2_result << endl;
		//cout << "branch : " << hex << ALU2_result.to_ulong() << endl;

		// choose between branch, jump and PC+4

		Multiplexer2.setControl((zero & conUnit.getBranch()));
		Multiplexer2.select(ALU1_result, ALU2_result);
		Multiplexer2.print(ALU1_result, ALU2_result, configFile["output_file"]);

		bitset<32> Multiplexer2_res = Multiplexer2.getSelected();

		Multiplexer3.select(Multiplexer2_res, jump_address);
		Multiplexer3.print(Multiplexer2_res, jump_address, configFile["output_file"]);

		bitset<32> Multiplexer3_res = Multiplexer3.getSelected();

		// update PC
		pc.setPC(Multiplexer3_res);

		if(configFile["print_memory_contents"]=="true")
		{
				regFile.printRegisterFile(configFile["output_file"]);
				dataMem.printDataMemory(configFile["output_file"]);
				instMem.print(configFile["output_file"]);
		}

		if(configFile["output_file"] == "")
		{
			cout << "#######################################################" << endl;
		}
		else
		{
			// open output file
			ofstream out;
			out.open(configFile["output_file"].c_str(),ios_base::app);

			// terminate if the output file is "bad"
			if(out.bad())
			{
				cerr << "Output file for Registers couldn't be opened!" << endl;
				exit(1);
			}

			else
			{
				out << "#######################################################" << endl;
			}

			// close the output file
			//out.close();
		}
		if(configFile["output_mode"] == "single_step")
		{
			cout << "Press enter to continue" << endl;
			cin.ignore();
		}
	}
}


/*
 * Accessor method for config map
 */
map<string,string> Processor::getConfig()
{
	return configFile;
}
