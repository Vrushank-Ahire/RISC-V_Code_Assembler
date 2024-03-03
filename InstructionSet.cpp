#include "InstructionSet.h"
using namespace std;
#include <bits/stdc++.h>
#include <unordered_map>
#include <bitset>

InstructionSet::InstructionSet() {
    // Initialize instruction set
    instructionFormats = {
        {"add", "R"},
        {"and", "R"},
        {"or", "R"},
        {"sll", "R"},
        {"slt", "R"},
        {"sra", "R"},
        {"srl", "R"},
        {"sub", "R"},
        {"xor", "R"},
        {"mul", "R"},
        {"div", "R"},
        {"rem", "R"},
        {"addi", "I"},
        {"andi", "I"},
        {"ori", "I"},
        {"lb", "I"},
        {"ld", "I"},
        {"lh", "I"},
        {"lw", "I"},
        {"jalr", "I"},
        {"sb", "S"},
        {"sw", "S"},
        {"sd", "S"},
        {"sh", "S"},
        {"beq", "SB"},
        {"bne", "SB"},
        {"bge", "SB"},
        {"blt", "SB"},
        {"auipc", "U"},
        {"lui", "U"},
        {"jal", "UJ"}
    };

    // Initialize opcode map
    opcodeMap = {
        {"add", "0110011"},
        {"and", "0110011"},
        {"or", "0110011"},
        {"sll", "0110011"},
        {"slt", "0110011"},
        {"sra", "0110011"},
        {"srl", "0110011"},
        {"sub", "0110011"},
        {"xor", "0110011"},
        {"mul", "0110011"},
        {"div", "0110011"},
        {"rem", "0110011"},
        {"addi", "0010011"},
        {"andi", "0010011"},
        {"ori", "0010011"},
        {"lb", "0000011"},
        {"ld", "0000011"},
        {"lh", "0000011"},
        {"lw", "0000011"},
        {"jalr", "1100111"},
        {"sb", "0100011"},
        {"sw", "0100011"},
        {"sd", "0100011"},
        {"sh", "0100011"},
        {"beq", "1100011"},
        {"bne", "1100011"},
        {"bge", "1100011"},
        {"blt", "1100011"},
        {"auipc", "0010111"},
        {"lui", "0110111"},
        {"jal", "1101111"}
    };

    // Initialize funct3 map
    funct3Map = {
        {"add", "000"},
        {"and", "111"},
        {"or", "110"},
        {"sll", "001"},
        {"slt", "010"},
        {"sra", "101"},
        {"srl", "101"},
        {"sub", "000"},
        {"xor", "100"},
        {"mul", "000"},
        {"div", "100"},
        {"rem", "110"},
        {"addi", "000"},
        {"andi", "111"},
        {"ori", "110"},
        {"lb", "000"},
        {"ld", "011"},
        {"lh", "001"},
        {"lw", "010"},
        {"jalr", "000"},
        {"sb", "000"},
        {"sw", "010"},
        {"sd", "011"},
        {"sh", "001"},
        {"beq", "000"},
        {"bne", "001"},
        {"bge", "101"},
        {"blt", "100"},
        {"auipc", "000"},
        {"lui", "000"},
        {"jal", "000"}
    };

    // Initialize funct7 map
    funct7Map = {
        {"add", "0000000"},
        {"and", "0000000"},
        {"or", "0000000"},
        {"sll", "0000000"},
        {"slt", "0000000"},
        {"sra", "0100000"},
        {"srl", "0000000"},
        {"sub", "0100000"},
        {"xor", "0000000"},
        {"mul", "0000001"},
        {"div", "0000001"},
        {"rem", "0000001"}
    };

    // Initialize immediate map
    immediateMap = {
        {"add", false},
        {"and", false},
        {"or", false},
        {"sll", false},
        {"slt", false},
        {"sra", false},
        {"srl", false},
        {"sub", false},
        {"xor", false},
        {"mul", false},
        {"div", false},
        {"rem", false},
        {"addi", true},
        {"andi", true},
        {"ori", true},
        {"lb", true},
        {"ld", true},
        {"lh", true},
        {"lw", true},
        {"jalr", true},
        {"sb", true},
        {"sw", true},
        {"sd", true},
        {"sh", true},
        {"beq", true},
        {"bne", true},
        {"bge", true},
        {"blt", true},
        {"auipc", true},
        {"lui", true},
        {"jal", true}
    };
}

 string InstructionSet::getFormat(const  string& instruction) const {
    auto it = instructionFormats.find(instruction);
    return (it != instructionFormats.end()) ? it->second : "";
}

 string InstructionSet::getOpcode(const  string& instruction) const {
    auto it = opcodeMap.find(instruction);
    return (it != opcodeMap.end()) ? it->second : "";
}

 string InstructionSet::getFunct3(const  string& instruction) const {
    auto it = funct3Map.find(instruction);
    return (it != funct3Map.end()) ? it->second : "";
}

 string InstructionSet::getFunct7(const  string& instruction) const {
    auto it = funct7Map.find(instruction);
    return (it != funct7Map.end()) ? it->second : "";
}

bool InstructionSet::hasImmediate(const  string& instruction) const {
    auto it = immediateMap.find(instruction);
    return (it != immediateMap.end()) ? it->second : false;
}


// Implement methods for each instruction format class
//RFormatInstruction constructor defined 
RFormatInstruction::RFormatInstruction() {
    // Initialize any member variables or perform other setup tasks here if needed
}

// 1->Implement methods for RFormatInstruction class
string RFormatInstruction::generateMachineCode(const string& instructionLine) const {
    // Extract the instruction name from the instruction line
    size_t pos = instructionLine.find(' '); // Find the space after the instruction name
    string instructionName = instructionLine.substr(0, pos); // Extract the instruction name

    // Dynamically extract opcode, funct3, and funct7 based on the instruction name
    string opcode = getOpcode(instructionName);
    string funct3 = getFunct3(instructionName);
    string funct7 = getFunct7(instructionName);

    // Extracting registers from the instruction line
    string registers = instructionLine.substr(pos + 1); // Extract registers part of the instruction

    // Extracting rd, rs1, and rs2
    string rdName = registers.substr(0, registers.find(','));
    registers = registers.substr(registers.find(',') + 1);
    string rs1Name = registers.substr(0, registers.find(','));
    string rs2Name = registers.substr(registers.find(',') + 1);

    // Convert register names to their corresponding register numbers
    int rd = registerMap.at(rdName);
    int rs1 = registerMap.at(rs1Name);
    int rs2 = registerMap.at(rs2Name);

    // Convert register numbers to 5-bit binary representation
    string rdBinary =   bitset<5>(rd).to_string();
    string rs1Binary =  bitset<5>(rs1).to_string();
    string rs2Binary =  bitset<5>(rs2).to_string();

    // Concatenate funct7, rs2, rs1, funct3, rd, opcode to form the machine code
    string machineCode = funct7 + rs2Binary + rs1Binary + funct3 + rdBinary + opcode;

    return machineCode;
}