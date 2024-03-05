//commands to compile this file 
//  g++ -o my_program InstructionSet.cpp call_IS.cpp
//  ./my_program

#include <iostream>
#include "InstructionSet.cpp"
using namespace std;


int main() {
    InstructionSet instructionSet;
    RFormatInstruction rFormatInstruction;
    IInstructionFormat iFormatinstruction;
    SInstruction sFormatInstruction;
    // Example usage
    string instructionLine = "lb x14, 43(x15)";

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

    else if(format == "S"){
        string machinecode = sFormatInstruction.generateMachineCode(instructionLine);
        cout<< "Machine Code: "<<machinecode<<endl;
    }

    return 0;
}

