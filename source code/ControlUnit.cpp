#include "ControlUnit.h"

ControlUnit::ControlUnit() {
}
/*
*Constructor for ControlUnit
*/
ControlUnit::ControlUnit(MUX &mux1, MUX &mux2, MUX &mux3, MUX &mux4, MUX &mux5, DataMemory &datamem,ALUControl &alucon,RegisterFile &regfile)
{
	Opcode = bitset<6>(0);
	RegDst=bitset<1>(0);
	Jump=bitset<1>(0);
	Branch=bitset<1>(0);
	MemRead=bitset<1>(0);
	MemToReg=bitset<1>(0);
	ALUOp0=bitset<1>(0);
	ALUOp1=bitset<1>(0);
	MemWrite=bitset<1>(0);
	ALUSrc=bitset<1>(0);
	RegWrite=bitset<1>(0);
	Controlregfile=regfile;
	Controldatamem=datamem;
	ControlAlu=alucon;
	Mux1=mux1;
	Mux2=mux2;
	Mux3=mux3;
	Mux4=mux4;
	Mux5=mux5;

}

void ControlUnit::setControlUnit(bitset<6>op,MUX &Mux1, MUX &Mux2, MUX &Mux3, MUX &Mux4, MUX &Mux5, DataMemory &Controldatamem,ALUControl &ControlAlu,RegisterFile &Controlregfile)
{
	Opcode = op;
	bitset<6>Rtype("000000");
	bitset<6>lw("100011");
	bitset<6>sw("101011");
	bitset<6>beq("000100");
	bitset<6>addi("001000");

	if(Opcode == bitset<6>("000000")) //When Opcode is Rtype
	{
		RegDst=bitset<1>(1);
		Jump=bitset<1>(0);
		Branch=bitset<1>(0);
		MemRead=bitset<1>(0);
		MemToReg=bitset<1>(0);
		ALUOp0=bitset<1>(0);
		ALUOp1=bitset<1>(1);
		MemWrite=bitset<1>(0);
		ALUSrc=bitset<1>(0);
		RegWrite=bitset<1>(1);
		Controldatamem.setMemWrite(0);
		Controldatamem.setMemRead(0);
		Controlregfile.setRegWrite(1);
		ControlAlu.setALUOp(10);
		Mux1.setControl(1);
		Mux2.setControl(0);
		Mux3.setControl(0);
		Mux4.setControl(0);
		Mux5.setControl(0);
	}
	else if (Opcode == bitset<6>("001000")) //When opcode is addi
	{
		RegDst=bitset<1>(0);
		Jump=bitset<1>(0);
		Branch=bitset<1>(0);
		MemRead=bitset<1>(0);
		MemToReg=bitset<1>(0);
		ALUOp0=bitset<1>(0);
		ALUOp1=bitset<1>(0);
		MemWrite=bitset<1>(0);
		ALUSrc=bitset<1>(1);
		RegWrite=bitset<1>(1);

		Controldatamem.setMemWrite(0);
		Controldatamem.setMemRead(0);
		Controlregfile.setRegWrite(bitset<1>("1"));
		ControlAlu.setALUOp(00);
		Mux1.setControl(0);
		Mux2.setControl(0);
		Mux3.setControl(0);
		Mux4.setControl(0);
		Mux5.setControl(1);
	}
	else if (Opcode == bitset<6>("100011")) //When opcode is lw
	{
		RegDst=bitset<1>(0);
		Jump=bitset<1>(0);
		Branch=bitset<1>(0);
		MemRead=bitset<1>(1);
		MemToReg=bitset<1>(1);
		ALUOp0=bitset<1>(0);
		ALUOp1=bitset<1>(0);
		MemWrite=bitset<1>(0);
		ALUSrc=bitset<1>(1);
		RegWrite=bitset<1>(1);

		Controldatamem.setMemWrite(0);
		Controldatamem.setMemRead(1);
		Controlregfile.setRegWrite(1);
		ControlAlu.setALUOp(00);
		Mux1.setControl(0);
		Mux2.setControl(0);
		Mux3.setControl(0);
		Mux4.setControl(1);
		Mux5.setControl(1);

	}
	else if (Opcode == bitset<6> ("101011")) //When Opcode is sw
	{
		RegDst=bitset<1>(0);
		Jump=bitset<1>(0);
		Branch=bitset<1>(0);
		MemRead=bitset<1>(0);
		MemToReg=bitset<1>(0);
		ALUOp0=bitset<1>(0);
		ALUOp1=bitset<1>(0);
		MemWrite=bitset<1>(1);
		ALUSrc=bitset<1>(1);
		RegWrite=bitset<1>(0);

		Controldatamem.setMemWrite(1);
		Controldatamem.setMemRead(0);
		Controlregfile.setRegWrite(0);
		ControlAlu.setALUOp(00);
		Mux1.setControl(0);
		Mux2.setControl(0);
		Mux3.setControl(0);
		Mux4.setControl(0);
		Mux5.setControl(1);

	}
	else if (Opcode == bitset<6>("000100")) //When opcode is beq
	{
		RegDst=bitset<1>(0);
		Jump=bitset<1>(0);
		Branch=bitset<1>(1);
		MemRead=bitset<1>(0);
		MemToReg=bitset<1>(0);
		ALUOp0=bitset<1>(1);
		ALUOp1=bitset<1>(0);
		MemWrite=bitset<1>(0);
		ALUSrc=bitset<1>(0);
		RegWrite=bitset<1>(0);

		Controldatamem.setMemWrite(0);
		Controldatamem.setMemRead(0);
		Controlregfile.setRegWrite(0);
		ControlAlu.setALUOp(01);
		Mux1.setControl(0);
		Mux2.setControl(1);
		Mux3.setControl(0);
		Mux4.setControl(0);
		Mux5.setControl(0);
	}
	else					//When opcode is jump
	{
		RegDst=bitset<1>(0);
		Jump=bitset<1>(1);
		Branch=bitset<1>(0);
		MemRead=bitset<1>(0);
		MemToReg=bitset<1>(0);
		ALUOp0=bitset<1>(0);
		ALUOp1=bitset<1>(0);
		MemWrite=bitset<1>(0);
		ALUSrc=bitset<1>(0);
		RegWrite=bitset<1>(0);

		Controldatamem.setMemWrite(0);
		Controldatamem.setMemRead(0);
		Controlregfile.setRegWrite(0);
		ControlAlu.setALUOp(00);
		Mux1.setControl(0);
		Mux2.setControl(0);
		Mux3.setControl(1);
		Mux4.setControl(0);
		Mux5.setControl(0);

	}


	}

	void ControlUnit::printControlUnitsValue(string outputFile)
	{	//print directly
		if (outputFile==""){
		cout << "-----------------------" << endl;
		cout<< "Control Unit: "<< endl;
		cout << "-----------------------" << endl;
		cout<<"Input opcode: 0x"<< hex << Opcode.to_ulong() <<'\n';
		cout<<"RegDst: 0x"<< hex << RegDst.to_ulong()  <<'\n';
		cout<<"Jump: 0x"<< Jump.to_ulong() << '\n';
		cout<<"Branch: 0x" << Branch.to_ulong() <<'\n';
		cout<<"MemRead: 0x"<<MemRead.to_ulong()<<'\n';
		cout<<"MemToReg: 0x"<<MemToReg.to_ulong()<<'\n';
		cout<<"AluOp0: 0x"<<ALUOp0.to_ulong()<<'\n';
		cout<<"AluOp1: 0x"<<ALUOp1.to_ulong()<<'\n';
		cout<<"MemWrite: 0x"<<MemWrite.to_ulong()<<'\n';
		cout<<"AluSrc: 0x"<<ALUSrc.to_ulong()<<'\n';
		cout<<"RegWrite: 0x"<<RegWrite.to_ulong()<<'\n';
	}
	else{
		//print to the outputFile
		ofstream outFile;
		outFile.open(outputFile,ios_base::app);
		outFile << "-----------------------" << endl;
		outFile<<"Control Unit: "<<endl;
		outFile << "-----------------------" << endl;
		outFile<<"Input opcode: 0x"<< hex << Opcode.to_ulong() <<'\n';
		outFile<<"RegDst: 0x"<< hex << RegDst.to_ulong()  <<'\n';
		outFile<<"Jump: 0x"<< Jump.to_ulong() << '\n';
		outFile<<"Branch: 0x" << Branch.to_ulong() <<'\n';
		outFile<<"MemRead: 0x"<<MemRead.to_ulong()<<'\n';
		outFile<<"MemToReg: 0x"<<MemToReg.to_ulong()<<'\n';
		outFile<<"AluOp0: 0x"<<ALUOp0.to_ulong()<<'\n';
		outFile<<"AluOp1: 0x"<<ALUOp1.to_ulong()<<'\n';
		outFile<<"MemWrite: 0x"<<MemWrite.to_ulong()<<'\n';
		outFile<<"AluSrc: 0x"<<ALUSrc.to_ulong()<<'\n';
		outFile<<"RegWrite: 0x"<<RegWrite.to_ulong()<<'\n';
	}
}

		bitset<1> ControlUnit:: getRegDst()
		{
			return RegDst;
		}


		bitset<1> ControlUnit:: getJump()
		{
			return Jump;
		}


		bitset<1> ControlUnit::getBranch()
		{
			return Branch;
		}

		bitset<1> ControlUnit::getMemRead()
		{
			return MemRead;
		}

		bitset<1> ControlUnit::getMemToReg()
		{
			return MemToReg;
		}

		bitset<1> ControlUnit::getAluOp0()
		{
			return ALUOp0;
		}

		bitset<1> ControlUnit::getAluOp1()
		{
			return ALUOp1;
		}

		bitset<1> ControlUnit::getMemWrite()
		{
			return MemWrite;

		}

		bitset<1> ControlUnit:: getAluSrc()
		{
			return ALUSrc;
		}

		bitset<1> ControlUnit::getRegWrite()
		{
			return RegWrite;
		}
