#include <iostream>
#include <bits/stdc++.h>
using namespace std;

int data_ptr = 268435456; // 0x10000000 initially (here, in decimal)

string hexa_decimal(int input)
{

    string final;
    if (input == 0)
    {
        return "0";
    }
    while (input > 0)
    {
        int temp = input % 16;

        if (temp <= 9)
        {
            final = (char)('0' + temp) + final;
        }

        else
        {
            final = (char)('A' + temp - 10) + final;
        }

        input /= 16;
    }

    return final;
}

void processAsciiz(const string &line, map<string, int> &data_mp, ofstream &outputFile)
{
    string label = line.substr(0, line.find(":"));
    string data = line.substr(line.find_first_of('"') + 1, line.find_last_of('"') - line.find_first_of('"') - 1);

    int address = data_ptr;
    data_mp[label] = address;

    for (char c : data)
    {
        outputFile << "0x" << hexa_decimal(data_ptr) << " 0x" << hexa_decimal((static_cast<int>(c))) << endl;
        data_ptr++;
        address++;
    }

    outputFile << "0x" << hexa_decimal(data_ptr) << " 0x" << hexa_decimal(0) << endl;
    data_ptr++;
}

// Function to process .byte instruction

void processByte(const string &line, map<string, int> &data_mp, ofstream &outputFile)
{

    string label = line.substr(0, line.find(":")); // Extract label
    string line2 = line.substr(line.find(':') + 1, line.size() - 1);
    int i = 0;
    while (line2[i] != 'e')
    {
        i++;
    }
    i++;
    while (line2[i] == ' ')
    {
        i++;
    }
    for (int j = i; j < line2.size(); j++)
    {
        if (line2[j] == ' ' || line2[j] == ',')
        {
            continue;
        }
        if (line2[j] == '\'')
        {
            j++;
            int value = (int)(line2[j]);
            outputFile << "0x" << hexa_decimal(data_ptr) << " 0x" << hexa_decimal(value) << endl;
            data_mp[label] = data_ptr;
            data_ptr++;
            j++;
        }
        else
        {
            int asci = (int)(line2[j]) - 48;
            if (line2[j + 1] == ',' || line2[j + 1] == ' ' || line2[j + 1] == '\0')
            {
            }
            else
            {
                j++;
                int sec_asci = (int)(line2[j]) - 48;
                if (sec_asci >= 0 && sec_asci <= 5)
                {
                    asci = 10 * asci + sec_asci;
                }
            }
            outputFile << "0x" << hexa_decimal(data_ptr) << " 0x" << hexa_decimal(asci) << endl;
            data_mp[label] = data_ptr;
            data_ptr++;
        }
    }
}

// Function to process .half instruction
void processHalf(const string &line, map<string, int> &data_mp, ofstream &outputFile)
{
    string label = line.substr(0, line.find(":")); // Extract label
    string line2 = line.substr(line.find(':') + 1, line.size() - 1);
    string dataStr = line2.substr(line2.find_first_of("1234567890")); // Extract data part of the line

    // Tokenize the data string based on commas
    stringstream ss(dataStr);
    string token;
    while (getline(ss, token, ','))
    {
        // Convert token to integer
        int value = stoi(token);

        // Store value in memory
        outputFile << "0x" << hexa_decimal(data_ptr) << " 0x" << hexa_decimal(value) << endl;
        data_mp[label] = data_ptr;
        data_ptr += 2; // Assuming 2 bytes per half-word
    }
}

// Function to process .word instruction
void processWord(const string &line, map<string, int> &data_mp, ofstream &outputFile)
{
    string label = line.substr(0, line.find(":")); // Extract label
    string line2 = line.substr(line.find(':') + 1, line.size() - 1);
    string dataStr = line2.substr(line2.find_first_of("1234567890")); // Extract data part of the line

    // Tokenize the data string based on commas
    stringstream ss(dataStr);
    string token;
    while (getline(ss, token, ','))
    {
        // Convert token to integer
        int value = stoi(token);

        // Store value in memory
        outputFile << "0x" << hexa_decimal(data_ptr) << " 0x" << hexa_decimal(value) << endl;
        data_mp[label] = data_ptr;
        data_ptr += 4; // Assuming 4 bytes per word
    }
}

// Function to process .word instruction
void processDword(const string &line, map<string, int> &data_mp, ofstream &outputFile)
{
    string label = line.substr(0, line.find(":")); // Extract label
    string line2 = line.substr(line.find(':') + 1, line.size() - 1);
    string dataStr = line2.substr(line2.find_first_of("1234567890")); // Extract data part of the line

    // Tokenize the data string based on commas
    stringstream ss(dataStr);
    string token;
    while (getline(ss, token, ','))
    {
        // Convert token to integer
        int value = stoi(token);

        // Store value in memory
        outputFile << "0x" << hexa_decimal(data_ptr) << " 0x" << hexa_decimal(value) << endl;
        data_mp[label] = data_ptr;
        data_ptr += 8; // Assuming 8 bytes per double word
    }
}

int data_main(string name)
{
    string filename = name;
    ifstream inputFile(filename);
    if (!inputFile.is_open())
    {
        cerr << "Error opening file: " << filename << endl;
        return 1;
    }

    string line;
    int flag = 1;
    map<string, int> data_mp;
    ofstream outputFile("outputDataSeg.txt", std::ios::app); // Output file for data segment with addresses
    outputFile << "DATA SEGMENT" << endl;

    while (getline(inputFile, line))
    {
        size_t found_data = line.find(".data");
        size_t found_text = line.find(".text");

        if (line.empty())
        {
            continue;
        }

        if (found_data != string::npos)
        {
            flag = 1;

            continue;
        }
        else if (found_text != string::npos)
        {
            flag = 0;
        }

        // All the functions are called in the below part
        if (flag == 1)
        {
            stringstream ss(line);
            string token, label;
            ss >> token;
            label = token.substr(0, token.size() - 1); // Remove ':' from token to get label
            outputFile<<label<<endl;
            if (line.find(".asciiz") != string::npos)
            {
                processAsciiz(line, data_mp, outputFile); // Pass outputFile object to the function
            }
            else if (line.find(".byte") != string::npos)
            {
                processByte(line, data_mp, outputFile); // Call processByte function
            }
            else if (line.find(".half") != string::npos)
            {
                processHalf(line, data_mp, outputFile); // Call processHalf function
            }
            else if (line.find(".word") != string::npos)
            {
                processWord(line, data_mp, outputFile); // Call processWord function
            }
            else if (line.find(".dword") != string::npos)
            {
                processDword(line, data_mp, outputFile); // Call processDword function
            }

            data_mp[label] = data_ptr;

            //   outputFile << line << endl; // This prints all those lines that are part of .data segment
        }
        if (flag == 0)
        {
            continue;
        }
    }

    inputFile.close();
    outputFile.close(); // Close the output file
    return 0;
}
