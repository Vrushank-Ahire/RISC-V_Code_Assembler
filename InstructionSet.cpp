#include "InstructionSet.h"
#include <bits/stdc++.h>
using namespace std;
#include <unordered_map>
#include <bitset>

vector <pair<string, int>> labels;

void add_pair(pair<string, int> temp){
    labels.push_back(temp);
}

string comp(int temp_immediate){

    cout<<endl<<temp_immediate<<endl;

    string temp = bitset<12>(temp_immediate).to_string();
    cout<<temp<<endl;
    for(int i = 0; i<12; i++){
        if(temp[i] == '0'){
            temp[i] = '1';
        }

        else if(temp[i] == '1'){
            temp[i] = '0';
        }
    }
    char to_carry = '1';
    for(int i = 11; i>=0; i--){
        if(to_carry == '1' && temp[i] == '1'){
            temp[i] = '0';
        }

        else if((to_carry == '1' && temp[i] == '0') || (to_carry == '0' && temp[i] == '1')){
            temp[i] = '1';
            to_carry = '0';
        }

        else{
            temp[i] = '0';
            to_carry = '0';
        }
    }
    
   // cout<<temp<<endl;
    return temp;
}

int find_prog_count(string input){
    int size = labels.size();
    for(int i = 0; i<size; i++){
       // cout<<labels[i].second<<endl;
       // cout<<labels[i].first<<endl;
        if(input == labels[i].first){
         //   cout<<"The returned value is "<<labels[i].second<<endl;
            return labels[i].second;
        }
    }
}

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

string InstructionSet::getFormat(string instruction) {
    int pos = instruction.find(' ');

    string instruction_name = instruction.substr(0, pos);

    auto it = instructionFormats.find(instruction_name);
    return (it != instructionFormats.end()) ? it->second : "";
}

string InstructionSet::getOpcode(const  string& instruction) {
    auto it = opcodeMap.find(instruction);
    return (it != opcodeMap.end()) ? it->second : "";
}

 string InstructionSet::getFunct3(const  string& instruction) {
    auto it = funct3Map.find(instruction);
    return (it != funct3Map.end()) ? it->second : "";
}

 string InstructionSet::getFunct7(const  string& instruction) {
    auto it = funct7Map.find(instruction);
    return (it != funct7Map.end()) ? it->second : "";
}

bool InstructionSet::hasImmediate(const  string& instruction) {
    auto it = immediateMap.find(instruction);
    return (it != immediateMap.end()) ? it->second : false;
}

RFormatInstruction::RFormatInstruction() {

}

string RFormatInstruction::generateMachineCode(const string& instructionLine) {
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

IInstructionFormat::IInstructionFormat(){
    
}

string IInstructionFormat::generateMachineCode(string Instructionline){

    
    string instruction_name;
    int pos = 0;
    while(Instructionline[pos]==' '){
        pos++;
    }

    while(Instructionline[pos]!= ' '){
        instruction_name += Instructionline[pos];
        pos++;
    }

   // cout<<instruction_name;
    string opcode = getOpcode(instruction_name);
    string funct3 = getFunct3(instruction_name);

    if(instruction_name == "andi" || instruction_name == "ori" || instruction_name == "addi"){
        string rs1;

        while(Instructionline[pos] != ','){
            
            if(Instructionline[pos]!= ' ')
                rs1 += Instructionline[pos];

            pos++;
        }

        int intrs1 = registerMap.at(rs1);
       // cout<<intrs1;

        string rs1Binary =  bitset<5>(intrs1).to_string();
       // cout<<rs1Binary;

       string rs2;
        pos++;
        while(Instructionline[pos] != ','){    
            if(Instructionline[pos]!= ' ')
                rs2 += Instructionline[pos];
            
          //  cout<<"*";
            pos++;
        }

        int intrs2 = registerMap.at(rs2);
        string rs2Binary =  bitset<5>(intrs2).to_string();

        int size = Instructionline.size();
        int immediate = 0;
        int k = 1;
        for(int i = pos+1; i<size; i++){
            if(Instructionline[i] != ' '){
                immediate *= 10;
                immediate += Instructionline[i] - 48;
                k=0;
                continue;
            }

            if(k == 0){
                break;
            }
        }

        string immediate_ = bitset<12>(immediate).to_string();

        string final = immediate_ + rs2Binary + funct3 + rs1Binary + opcode;

        return final; 
    }

    if(instruction_name == "lb" || instruction_name == "ld" || instruction_name == "lh" || instruction_name == "lw" || instruction_name == "jalr"){
        string rs1;

        while(Instructionline[pos] != ','){
            
            if(Instructionline[pos]!= ' ')
                rs1 += Instructionline[pos];

            pos++;
        }

        int intrs1 = registerMap.at(rs1);

        string rs1Binary =  bitset<5>(intrs1).to_string();

        string final = "";

        pos++;

        int immediate = 0;
        while(Instructionline[pos] != '('){
            if(Instructionline[pos] != ' '){
                immediate *= 10;
                immediate += Instructionline[pos] - 48;
            }

            pos++;
        }

        string immediate_ = bitset<12>(immediate).to_string();

        pos++;

        string rd;
        while(Instructionline[pos] != ')'){
            if(Instructionline[pos] != ' '){
                rd += Instructionline[pos];
            }
            pos++;
        }

        int intrs2 = registerMap.at(rd);

        string rs2Binary = bitset<5>(intrs2).to_string();

        final = immediate_ + rs2Binary + funct3 + rs1Binary + opcode;
        return final; 
    }

    return "";
}


SInstruction::SInstruction(){
    
}

string SInstruction::generateMachineCode(string Instructionline){
    string instruction_name;
    int pos = 0;
    while(Instructionline[pos]==' '){
        pos++;
    }

    while(Instructionline[pos]!= ' '){
        instruction_name += Instructionline[pos];
        pos++;
    }

    
    string opcode = getOpcode(instruction_name);
    string funct3 = getFunct3(instruction_name);
    
    string rs1;

    while(Instructionline[pos] != ','){
        if(Instructionline[pos]!= ' ')
            rs1 += Instructionline[pos];

        pos++;
    }

    int intrs1 = registerMap.at(rs1);

    string rs1Binary =  bitset<5>(intrs1).to_string();

    string final = "";

    pos++;

    int immediate = 0;
    while(Instructionline[pos] != '('){
        if(Instructionline[pos] != ' '){
            immediate *= 10;
            immediate += Instructionline[pos] - 48;
        }

        pos++;
    }

    string immediate_ = bitset<12>(immediate).to_string();

    pos++;

    string rd;
    while(Instructionline[pos] != ')'){
        if(Instructionline[pos] != ' '){
            rd += Instructionline[pos];
        }
        pos++;
    }

    int intrs2 = registerMap.at(rd);
    
    string rs2Binary = bitset<5>(intrs2).to_string();

    string immediate_1 = immediate_.substr(0,7);

    string immediate_2 = immediate_.substr(7,13);

    final = immediate_1 + rs1Binary + rs2Binary + funct3 + immediate_2 + opcode;

    return final; 
    
};

SBInstruction::SBInstruction(){
    
}

string SBInstruction::generateMachineCode(string Instructionline, int prog_counter){
    string instruction_name;
    int pos = 0;
    while(Instructionline[pos]==' '){
        pos++;
    }

    while(Instructionline[pos]!= ' '){
        instruction_name += Instructionline[pos];
        pos++;
    }

    
    string opcode = getOpcode(instruction_name);
    string funct3 = getFunct3(instruction_name);


    
    string rs1;

    while(Instructionline[pos] != ','){
        if(Instructionline[pos]!= ' ')
            rs1 += Instructionline[pos];

        pos++;
    }

    int intrs1 = registerMap.at(rs1);

    string rs1Binary =  bitset<5>(intrs1).to_string();

    string final = "";

    pos++;

    string rs2;

    while(Instructionline[pos] != ','){
        if(Instructionline[pos]!= ' ')
            rs2 += Instructionline[pos];

        pos++;
    }

    int intrs2 = registerMap.at(rs2);

    string rs2Binary =  bitset<5>(intrs2).to_string();

    pos++;

    int size = Instructionline.length();
    int work = 0;

    string temp_label;
    while(pos<size){
        if(Instructionline[pos] == ' ' && work == 0){
            continue;
        }
        
        else if(Instructionline[pos] == ' ' && work == 1){
            break;
        }
        work = 1;
        temp_label += Instructionline[pos];
        pos++;
    }

   // cout<<temp_label<<endl;

    int to_jump = find_prog_count(temp_label);
    int immediate = to_jump - prog_counter;

  //  cout<<immediate<<"= added"<<endl;
    
    string part1, part2;
    if(immediate<0)
    {
        // int temp_immediate = -1*immediate;
        // string imm = comp(temp_immediate);
       // immediate++;
       immediate = -1 * immediate - 1;
       //cout<<immediate;
        int temp_imm = ~immediate + 1;
       // cout<<"TEMP IMM"<<temp_imm;
        bitset<12> offset(temp_imm) ;
        string imm = offset.to_string() ;
        part1 = imm.substr(0,7);
        part2 = imm.substr(7);
    }
    else
    {
        bitset<12> offset(immediate) ;
        string imm = offset.to_string() ;
        part1 = imm.substr(0,7);
        part2 = imm.substr(7);
    }

    


    final = part1 + rs2Binary + rs1Binary + funct3 + part2 + opcode;

    return final; 
    
};



UInstruction::UInstruction()
{
}
string UInstruction::generateMachineCode(string Instructionline)
{

    string instruction_name;
    int pos = 0;
    while (Instructionline[pos] == ' ')
    {
        pos++;
    }

    while (Instructionline[pos] != ' ')
    {
        instruction_name += Instructionline[pos];
        pos++;
    }

    //cout<<instruction_name;
    string opcode = getOpcode(instruction_name);
   // cout<<opcode;
    if (instruction_name == "auipc" || instruction_name == "lui")
    {
        string rs1;

        while (Instructionline[pos] != ',')
        {

            if (Instructionline[pos] != ' ')
                rs1 += Instructionline[pos];

            pos++;
        }

        int intrs1 = registerMap.at(rs1);
        //cout<<intrs1;

        string rs1Binary = bitset<5>(intrs1).to_string();
        // cout<<rs1Binary;

        int size = Instructionline.size();
        int immediate = 0;
        int enterflag = 0;
        int bin = 0;
        int bin_size = 0;
        int hex = 0;
        int hex_size = 0;
        int integer = 0;
        string if_bin = "";
        string if_hex = "";
        string if_int="";
        unordered_map<char,string> hexMap = {
            {'0', "0000"},
            {'1', "0001"},
            {'2', "0010"},
            {'3', "0011"},
            {'4', "0100"},
            {'5', "0101"},
            {'6', "0110"},
            {'7', "0111"},
            {'8', "1000"},
            {'9', "1001"},
            {'A', "1010"},
            {'B', "1011"},
            {'C', "1100"},
            {'D', "1101"},
            {'E', "1110"},
            {'F', "1111"},
            {'a', "1010"},
            {'b', "1011"},
            {'c', "1100"},
            {'d', "1101"},
            {'e', "1110"},
            {'f', "1111"}
            };
        for (int i = pos + 1; i < size; i++)
        {
            if (Instructionline[i] != ' ')
            {
                if (enterflag == 0)
                {
                    if (Instructionline[i + 1] == 'b')
                    {
                        enterflag = 1;
                        bin = 1;
                        bin_size = 0;
                    }
                    else if (Instructionline[i + 1] == 'x')
                    {
                      //  cout<<"ENTERED THIS";
                        enterflag = 1;
                        hex = 1;
                        hex_size = 0;
                    }
                    else
                    {
                        
                        enterflag = 1;
                        integer=1;
                        for (int j = i; j < size; j++)
                        {
                            if (Instructionline[j] != ' ')
                            {
                                immediate *= 10;
                                immediate += Instructionline[j] - 48;
                            }
                        }
                         if_int = bitset<20>(immediate).to_string();

                        break;
                    }
                }
                if (enterflag == 1)
                {
                    if (bin == 1)
                    {
                        if (bin_size == 0)
                        {
                            i = i + 2;
                            if_bin += Instructionline[i];
                            bin_size += 1;
                        }
                        else
                        {
                            if (bin_size <= 20)
                            {
                                if_bin += Instructionline[i];
                                bin_size += 1;
                            }
                        }
                    }
                    else if(hex==1)
                    {
                        if (hex_size == 0)
                        {
                            i = i + 2;
                            
                            if_hex+=hexMap.at(Instructionline[i]);
                            hex_size+=1;
                        }
                        else
                        {
                            if (hex_size <= 5)
                            {
                                if_hex+=hexMap.at(Instructionline[i]);
                                hex_size+=1;
                            }
                        }
                    }
                    
                }
                
            }
        }


        string final="";
        if(bin==1)
        {
            if(bin_size<20)
            {
                for(int i=20-bin_size;i>=1;i--)
                {
                    if_bin='0'+if_bin;
                }
                
            }
            final=if_bin;
        }  
        if(hex==1)
        {
            if(hex_size<5)
            {
                for(int i=5-hex_size;i>=1;i--)
                {
                    if_hex="0000"+if_hex;
                  //  cout<<"*";

                }  
            }
            final=if_hex;
            
        }
        if(integer==1)
        {
            final=if_int;
        }

     //   cout<<"*";
        
        string final_x = final+ rs1Binary + opcode;

        return final_x;
    }
    }