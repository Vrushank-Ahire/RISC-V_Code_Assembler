//commands to compile this file 
//  g++ -o my_program InstructionSet.cpp call_IS.cpp
//  ./my_program

#include <iostream>
#include "InstructionSet.cpp"
using namespace std;
#include "output.mc"

int program_counter;

void program_zero(){
    program_counter = 0;
}

string final_machinecode(string line) {
    //cout<<line<<endl;
    if(line[0] == '.'){
        cout<<"Directive"<<endl;
        return "" ;
    }
    cout<<"*";
    InstructionSet instructionSet;
    RFormatInstruction rFormatInstruction;
    IInstructionFormat iFormatinstruction;
    SInstruction sFormatInstruction;
    // Example usage
    string instructionLine = "add x14,x15,x17";
    instructionLine = line;
    cout<<"Instruction = "<<instructionLine<<endl;
    string format = instructionSet.getFormat(instructionLine);
    cout<<"FORMAT = "<<format<<endl;
    string machineCode;

    if(format == "R"){
        program_counter += 4;
        machineCode = rFormatInstruction.generateMachineCode(instructionLine);
        cout << "0x"<<program_counter<<"Machine Code: " << machineCode << endl;
    }
    
    else if(format == "I"){
        program_counter += 4;

        machineCode = iFormatinstruction.generateMachineCode(instructionLine);
        cout << "0x"<<program_counter<<"Machine Code: " << machineCode << endl;
    }

    else if(format == "S"){
        program_counter += 4;

        machineCode = sFormatInstruction.generateMachineCode(instructionLine);
        cout<< "0x"<<program_counter<<"Machine Code: "<<machineCode<<endl;
    }
    
  //  "output.mc" << machineCode << endl;

    
    return "";
}

