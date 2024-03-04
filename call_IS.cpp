//commands to compile this file 
//  g++ call_IS.cpp
//  ./axe

#include <iostream>
#include "InstructionSet.cpp"
using namespace std;


int main() {
    InstructionSet instructionSet;
    RFormatInstruction rFormatInstruction;
    IInstructionFormat iFormatinstruction;
    // Example usage
    string instructionLine = "jalr  x13  ,  324 (x16)";

    cout<<"Instruction = "<<instructionLine<<endl;
    string format = instructionSet.getFormat(instructionLine);
    cout<<"FORMAT = "<<format<<endl;

    if(format == "R"){
        string machineCode = rFormatInstruction.generateMachineCode(instructionLine);
        cout << "Machine Code: " << machineCode << endl;
    }
    
    else if(format == "I"){
        string machineCode = iFormatinstruction.generateMachineCode(instructionLine);
        cout << "Machine Code: " << machineCode << endl;
    }

    return 0;
}

