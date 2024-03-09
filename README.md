# RISC-V Code Assembler

## Overview

This repository contains a RISC-V assembly instruction processing system composed of multiple modules: `InstructionSet.h`, `InstructionSet.cpp`, `main.cpp`, `call_IS.cpp`, and `DataSegment.cpp`. The system reads RISC-V assembly instructions from standard input, processes them according to their type, and generates machine code output to standard output.

## Modules

### InstructionSet.h

This header file defines a class called `InstructionSet`, facilitating the handling of various instruction formats in assembly language. It provides functions to extract format details such as opcode, funct3, and funct7, as well as methods to check if an instruction has an immediate value. Additionally, it declares subclasses for specific instruction formats (R, I, S, U, SB, UJ), each inheriting from `InstructionSet` to efficiently manage instructions of their respective formats.

### InstructionSet.cpp

This source file implements the functionalities declared in `InstructionSet.h`. It defines the constructor and member functions of the `InstructionSet` class, including methods for retrieving instruction format details and checking for immediate values. Furthermore, it provides the implementation for specific instruction format classes like `RFormatInstruction`, `IInstructionFormat`, etc., offering functionality to generate machine code for instructions of each format.

### main.cpp

Serving as the core of the assembly process, this file orchestrates the entire compilation process. It reads input from an assembly file (`input.asm`), preprocesses each line, generates machine code using the instruction set classes, and writes the output to a file (`output.mc`). It controls the overall flow of the assembly process, managing file input/output and invoking relevant functions for instruction processing.

### call_IS.cpp

This file demonstrates the utilization of the instruction set classes. It preprocesses input lines, invokes appropriate instruction format classes based on the detected format, generates machine code for each instruction, and displays the machine code alongside the instruction line.

### DataSegment.cpp

This file manages operations related to the data segment in the assembly code. It handles data storage, initialization, and access within the data segment, providing functionality to manage variables, constants, and arrays effectively during assembly.

## Usage

1. Write RISC-V assembly instructions and provide them as standard input to the program. This should be provided in a file named `input.asm`.

2. Compile the program using:
   
    ```bash
    g++ main.cpp
    ```

3. Run the compiled program:
   
    ```bash
    ./a.exe               # For Windows
    ./a.out               # For Linux and Ubuntu systems
    ```

4. Check the standard output for the generated machine code in `output.mc`.

## Collaborators

- Ahire Vrushank (2022csb1002@iitrpr.ac.in)
- Patel Ayush (2022csb1101@iitrpr.ac.in)
- Pranav Menon (2022csb1329@iitrpr.ac.in)
