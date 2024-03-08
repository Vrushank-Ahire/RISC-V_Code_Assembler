#include <iostream>
#include <bits/stdc++.h>
using namespace std;

int data_ptr = 268435456;   //0x10000000 initially (here, in decimal)

// Function to process .asciiz instruction
void processAsciiz(const string& line, map<string, int>& data_mp, ofstream& outputFile) {
    string label = line.substr(0, line.find(":")); // Extract label
    string data = line.substr(line.find_first_of('"') + 1, line.find_last_of('"') - line.find_first_of('"') - 1);

    // Store data in memory
    int address = data_ptr;
    data_mp[label] = address;

    // Write address and ASCII values to the output file
    for (char c : data) {
        outputFile << "Address: " << address << ", Character: " << c << ", ASCII: " << static_cast<int>(c) << endl;
        data_ptr++;
        address++;
    }

    // Store null terminator to mark end of the string
    outputFile << "Address: " << address << ", Character: \\0, ASCII: 0" << endl;
    data_ptr++;
}

int main() {
    string filename = "inputDataSeg.asm";
    ifstream inputFile(filename);
    if (!inputFile.is_open()) {
        cerr << "Error opening file: " << filename << endl;
        return 1;
    }

    string line;
    int flag = 1;
    map<string, int> data_mp;
    ofstream outputFile("outputDataSeg.txt"); // Output file for data segment with addresses

    while (getline(inputFile, line)) {
        size_t found_data = line.find(".data");
        size_t found_text = line.find(".text");

        if (line.empty()) {
            continue;
        }

        if (found_data != string::npos) {
            flag = 1;
            continue;
        } else if (found_text != string::npos) {
            flag = 0;
        }

        // All the functions are called in the below part
        if (flag == 1) {
            stringstream ss(line);
            string token, label;
            ss >> token;
            label = token.substr(0, token.size() - 1); // Remove ':' from token to get label

            if (line.find(".asciiz") != string::npos) {
                processAsciiz(line, data_mp, outputFile); // Pass outputFile object to the function
            }

            data_mp[label] = data_ptr;

            cout << line << endl; // This prints all those lines that are part of .data segment
        }
        if (flag == 0) {
            continue;
        }
    }

    inputFile.close();
    outputFile.close(); // Close the output file
    return 0;
}
