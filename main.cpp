#include <iostream>
#include <fstream>
#include <string>
#include "call_IS.cpp"
#include "DataSegment.cpp"

using namespace std;

queue<string> inst;
int program_temp;

int big_flag;

int main()
{
    ofstream outputFile("outputDataSeg.txt", std::ios::app);
    outputFile<<"TEXT SEGMENT"<<endl;
    string file_name = "inputDataSeg.asm";
    big_flag = 0;
    program_temp = 0;
    program_zero();
    ifstream inputFile(file_name); // Open the input file
    if (!inputFile.is_open())
    {
        cerr << "Failed to open the file." << endl;
        return 1; // Return error if file cannot be opened
    }

    string line;

    while (getline(inputFile, line))
    {

        size_t pos = line.find_first_not_of(" \t");
        if (pos != string::npos)
        {
            line = line.substr(pos);
        }

        if (!line.empty())
        {

            size_t colon_pos = line.find(':');
            if (colon_pos != string::npos)
            {

                string part1 = line.substr(0, colon_pos);

                size_t part1_pos = part1.find_first_not_of(" \t");
                if (part1_pos != string::npos)
                {
                    part1 = part1.substr(part1_pos);
                }
                string line2;
                for (int i = 0; i < colon_pos; i++)
                {

                    if (line[i] == ' ' || i == colon_pos - 1)
                    {
                        if (i == colon_pos - 1 && line[i] != ' ')
                        {
                            line2 += line[i];
                        }

                        break;
                    }
                    line2 += line[i];
                }

                pair<string, int> temp;
                temp.first = line2;
                temp.second = program_temp;

                add_pair(temp);
                line2 += ':';

                string part2 = line.substr(colon_pos + 1);

                size_t part2_pos = part2.find_first_not_of(" \t");
                if (part2_pos != string::npos)
                {
                    part2 = part2.substr(part2_pos);
                }
                if (!part1.empty() && !part2.empty())
                {

                    string instruction;
                    bool firstSpace = true;
                    for (char c : part2)
                    {
                        if (c == ' ')
                        {

                            if (firstSpace)
                            {
                                instruction += c;
                                firstSpace = false;
                            }
                        }
                        else
                        {
                            instruction += c;
                        }
                    }
                    if (instruction[0] != ' ')
                    {
                        //  cout<<"Pushed 1"<<instruction<<endl;
                        if (big_flag == 0)
                        {
                            program_temp += 4;
                            inst.push(instruction);
                        }
                    }
                }
            }
            else
            {
                // Check if it's an instruction line
                bool isInstruction = (line.find('#') == string::npos);
                
                if (isInstruction)
                {
              
                    string instruction;
                    bool firstSpace = true; // Flag to track if the first space is encountered
                    for (char c : line)
                    {
                        if (c == ' ')
                        {
                            // Only add the space if it's the first space encountered
                            if (firstSpace)
                            {
                                instruction += c;
                                firstSpace = false;
                            }
                        }
                        else
                        {
                            instruction += c;
                        }
                    }
                    //cout << instruction << endl;
                    if (instruction[0] != '.')
                    {
                        // cout<<"Pushed"<<instruction<<endl;
                        if (big_flag == 0)
                        {
                            program_temp += 4;
                            inst.push(instruction);
                        }
                    }
                }
                else
                {
                    cout<<line;
                    if(line[0] != '.'){
                        
                        outputFile<<"Invalid Instruction";
                        exit(1);
                    }
                }
            }
        }
    }

    int size = inst.size();

    for (int i = 0; i < size; i++)
    {
        string k = inst.front();
        // cout<<"Instruction is"<<k<<endl;
        inst.pop();
        final_machinecode(k);
    }
    inputFile.close();

    data_main(file_name);

    return 0;
}
