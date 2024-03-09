// commands to compile this file
//   g++ -o my_program InstructionSet.cpp call_IS.cpp
//   ./my_program

#include <iostream>
#include "InstructionSet.cpp"
using namespace std;
#include "output.mc"

int program_counter;

void program_zero()
{
    program_counter = 0;
}

string program_hex()
{
    
    int temp = program_counter;
    string final = "";
    while (temp > 0)
    {
        int mod = temp % 16;
        if (mod <= 9)
        {
            final = (char)(mod + '0') + final;
        }

        else
        {
            final = (char)('A' + mod - 10) + final;
        }

        temp /= 16;
    }
    if (final.length() == 0)
    {
        return "0";
    }
    return final;
}

string to_hex(string input)
{
    string final;

    // outputFile<<input<<endl;
    for (int i = 0; i < 32; i++)
    {
        int temp = 0;
        for (int j = 0; j < 4; j++)
        {
            //  outputFile<<i+j<<endl;
            temp *= 2;
            temp += input[i + j] - '0';
            // outputFile<<temp<<endl;
        }

        // outputFile<<temp<<endl;

        if (temp <= 9)
        {
            char k = temp + '0';
            final += k;
        }

        else
        {
            final += (char)('A' + temp - 10);
        }

        i = i + 3;
    }

    return final;
}

int get_program()
{
    return program_counter;
}

string final_machinecode(string line)
{
    // outputFile<<line<<endl;
    cout<<line<<endl;
    ofstream outputFile("outputDataSeg.txt", std::ios::app);
    if (line[0] == '.')
    {
        return "";
    }

    InstructionSet instructionSet;
    RFormatInstruction rFormatInstruction;
    IInstructionFormat iFormatinstruction;
    SInstruction sFormatInstruction;
    SBInstruction sbinstruction;
    UInstruction uinstruction;
    UJInstruction ujinstruction;

    string instructionLine = line;
    string format;
    // outputFile<<"Instruction = "<<instructionLine<<endl;
    try {
        format = instructionSet.getFormat(instructionLine);
        if(format == "ERROR")
            throw runtime_error("Wrong Format");
    } catch(const runtime_error& e) {  
        cerr << "Error: Invalid Instruction entered." << endl;
        exit(1);
    }
    

    // outputFile<<"FORMAT = "<<format<<endl;
    string machineCode;
    // outputFile<<instructionLine;
    if (format == "R")
    {
        machineCode = rFormatInstruction.generateMachineCode(instructionLine);
        // outputFile << "0x"<<program_counter<<"Machine Code: " << machineCode << endl;
        outputFile << "0x" << program_hex() << " " << to_hex(machineCode) << endl;
        program_counter += 4;
    }

    else if (format == "I")
    {
        machineCode = iFormatinstruction.generateMachineCode(instructionLine);
        // outputFile << "0x"<<program_counter<<"Machine Code: " << machineCode << endl;
        outputFile << "0x" << program_hex() << " " << to_hex(machineCode) << endl;
        program_counter += 4;
    }

    else if (format == "S")
    {
        machineCode = sFormatInstruction.generateMachineCode(instructionLine);
        // outputFile<< "0x"<<program_counter<<"Machine Code: "<<machineCode<<endl;
        outputFile << "0x" << program_hex() << " " << to_hex(machineCode) << endl;
        program_counter += 4;
    }

    else if (format == "SB")
    {
        machineCode = sbinstruction.generateMachineCode(instructionLine, program_counter);
        // outputFile<<"0x"<<program_counter<<"Machine Code: "<<machineCode<<endl;

        outputFile << "0x" << program_hex() << " " << to_hex(machineCode) << endl;
        program_counter += 4;
    }

    else if (format == "U")
    {
        machineCode = uinstruction.generateMachineCode(instructionLine);
        outputFile << "0x" << program_hex() << " " << to_hex(machineCode) << endl;
        program_counter += 4;
    }

    else if (format == "UJ")
    {
        machineCode = ujinstruction.generateMachineCode(instructionLine, program_counter);

        outputFile << "0x" << program_hex() << " " << to_hex(machineCode) << endl;
        program_counter += 4;
    }
    //  "output.mc" << machineCode << endl;

    return "";
}
