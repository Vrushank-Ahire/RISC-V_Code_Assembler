# RISC-V_Code_Assembler
This README provides an overview of the RISC-V assembly instruction processing system composed of multiple modules: InstructionSet.h, call_IS.cpp, input.asm, and outputDataSeg.txt , InstructionSet.cpp

Overview

The system is designed to read RISC-V assembly instructions from standard input, process them according to their type, and generate machine code output to standard output.


main.cpp

This file implements the main program logic for processing RISC-V assembly instructions. It includes 'InstructionSet.h' and reads input assembly lines, determines their format, and generates corresponding machine code. The program provides a streamlined approach for converting assembly code to machine code efficiently.


InstructionSet.h

 This header file defines classes for handling RISC-V assembly instructions. It contains methods for retrieving instruction formats, opcodes, and generating machine code. Separate classes for different instruction formats, like R, I, S, etc., ensure modular and efficient processing of assembly instructions.


InstructionSet.cpp

 This file contains the implementation of the InstructionSet class, which serves as a base class for various RISC-V instruction formats. It defines methods to retrieve the format, opcode, funct3, and funct7 of an instruction, as well as to check if the instruction has an immediate value. It also initializes maps for storing instruction formats, opcodes, and other related information.


call_IS.cpp:

This file serves as the entry point for the RISC-V assembly instruction processing program. It includes the necessary header files, such as InstructionSet.cpp, and defines the main logic for converting assembly instructions to machine code.The 'final_machinecode' function processes each line of assembly code, determines its format, and calls the appropriate method to generate machine code. Additionally, it maintains a program counter to track the memory addresses of instructions.



DataSegment.cpp:

This file likely contains the implementation of a class or functions related to handling the data segment of an assembly program. It might include functionalities for reading and writing data, managing memory allocation for variables, and handling data-related directives like .data. The exact implementation details would depend on the specific requirements of the assembly language being targeted.



Usage

1.Write RISC-V assembly instructions and provide them as standard input to the program.This has to be provided in file 'input.asm'.

2.Compile the program using.
                     
      g++ main.cpp

3.Run the compiled program. 

      ./a.exe               # For windows
      ./a.out               # For linux and ubuntu systems

4.Check the standard output for the generated machine code in 'output.mc'.
