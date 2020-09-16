OBJS = main.o Processor.o RegisterFile.o MUX.o DataMemory.o ControlUnit.o ALUControl.o ALU.o InstructionMemory.o RegisterTable.o Opcode.o Instruction.o ASMParser.o ProgramCounter.o SignExtend.o shiftLeft2.o # all object files
EXECS = simExec

CC = g++
LD = $(CC)

CCFLAGS = -Wall -Wno-deprecated $(INCDIR) -g -c -std=c++11
LDFLAGS = -Wall -Wno-deprecated -g -std=c++11

all: $(EXECS)
simExec: $(OBJS)
	$(LD) $(LDFLAGS) $(OBJS) -o simExec
main.o: main.cpp Processor.h
	$(CC) $(CCFLAGS) main.cpp
Processor.o: Processor.cpp RegisterFile.h ALU.h ALUControl.h InstructionMemory.h DataMemory.h ControlUnit.h MUX.h SignExtend.h ProgramCounter.h
	$(CC) $(CCFLAGS) Processor.cpp
RegisterFile.o: RegisterFile.cpp
	$(CC) $(CCFLAGS) RegisterFile.cpp
MUX.o: MUX.cpp
	$(CC) $(CCFLAGS) MUX.cpp
SignExtend.o: SignExtend.cpp
	$(CC) $(CCFLAGS) SignExtend.cpp
shiftLeft2.o: shiftLeft2.cpp
	$(CC) $(CCFLAGS) shiftLeft2.cpp
ProgramCounter.o: ProgramCounter.cpp
	$(CC) $(CCFLAGS) ProgramCounter.cpp
DataMemory.o: DataMemory.cpp
	$(CC) $(CCFLAGS) DataMemory.cpp
ControlUnit.o: ControlUnit.cpp ALUControl.h MUX.h DataMemory.h RegisterFile.h
	$(CC) $(CCFLAGS) ControlUnit.cpp
ALUControl.o: ALUControl.cpp ALU.h
	$(CC) $(CCFLAGS) ALUControl.cpp
ALU.o: ALU.cpp
	$(CC) $(CCFLAGS) ALU.cpp
InstructionMemory.o: InstructionMemory.cpp ASMParser.h Instruction.h Opcode.h RegisterTable.h
	$(CC) $(CCFLAGS) InstructionMemory.cpp
ASMParser.o: ASMParser.cpp Instruction.h Opcode.h RegisterTable.h
	$(CC) $(CCFLAGS) ASMParser.cpp
Instruction.o: Instruction.cpp Opcode.h RegisterTable.h
	$(CC) $(CCFLAGS) Instruction.cpp
Opcode.o: Opcode.cpp
	$(CC) $(CCFLAGS) Opcode.cpp
RegisterTable.o: RegisterTable.cpp
	$(CC) $(CCFLAGS) RegisterTable.cpp

clean:
	/bin/rm -f $(OBJS) $(EXECS)
