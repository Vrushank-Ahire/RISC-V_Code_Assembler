//commands to compile this file 
//  g++ -o my_program InstructionSet.cpp call_IS.cpp
//  ./my_program

#include <iostream>
#include "InstructionSet.h"
using namespace std;


int main() {
    InstructionSet instructionSet;
    RFormatInstruction rFormatInstruction;

    // Example usage
    string instructionLine = "add x5,x6,x9";
    string machineCode = rFormatInstruction.generateMachineCode(instructionLine);
    cout << "Machine Code: " << machineCode << endl;

    return 0;
}

