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
        outputFile << "Address: " << data_ptr << ", Value: " << static_cast<int>(c) << endl;
        data_ptr++;
        address++;
    }

    // Store null terminator to mark end of the string
    outputFile << "Address: " << address << ", Value: 0" << endl;
    data_ptr++;
}

// Function to process .byte instruction
void processByte(const string& line, map<string, int>& data_mp, ofstream& outputFile) {
    string label = line.substr(0, line.find(":")); // Extract label
    string line2 = line.substr(line.find(':') + 1,line.size()-1);
    string dataStr = line2.substr(line2.find_first_of("1234567890")); // Extract data part of the line

    // Tokenize the data string based on commas
    stringstream ss(dataStr);
    string token;
    while (getline(ss, token, ',')) {
        // Convert token to integer
        int value = stoi(token);

        // Store value in memory
        outputFile << "Address: " << data_ptr << ", Value: " << value << endl;
        data_mp[label] = data_ptr;
        data_ptr++;
    }
}

// Function to process .half instruction
void processHalf(const string& line, map<string, int>& data_mp, ofstream& outputFile) {
    string label = line.substr(0, line.find(":")); // Extract label
    string line2 = line.substr(line.find(':') + 1,line.size()-1);
    string dataStr = line2.substr(line2.find_first_of("1234567890")); // Extract data part of the line

    // Tokenize the data string based on commas
    stringstream ss(dataStr);
    string token;
    while (getline(ss, token, ',')) {
        // Convert token to integer
        int value = stoi(token);

        // Store value in memory
        outputFile << "Address: " << data_ptr << ", Value: " << value << endl;
        data_mp[label] = data_ptr;
        data_ptr += 2; // Assuming 2 bytes per half-word
    }
}

// Function to process .word instruction
void processWord(const string& line, map<string, int>& data_mp, ofstream& outputFile) {
    string label = line.substr(0, line.find(":")); // Extract label
    string line2 = line.substr(line.find(':') + 1,line.size()-1);
    string dataStr = line2.substr(line2.find_first_of("1234567890")); // Extract data part of the line

    // Tokenize the data string based on commas
    stringstream ss(dataStr);
    string token;
    while (getline(ss, token, ',')) {
        // Convert token to integer
        int value = stoi(token);

        // Store value in memory
        outputFile << "Address: " << data_ptr << ", Value: " << value << endl;
        data_mp[label] = data_ptr;
        data_ptr += 4; // Assuming 4 bytes per word
    }
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
        } 
        else if (found_text != string::npos) {
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
            else if (line.find(".byte") != string::npos) {
                processByte(line, data_mp, outputFile); // Call processByte function
            }
            else if (line.find(".half") != string::npos) {
                processHalf(line, data_mp, outputFile); // Call processHalf function
            }
            else if (line.find(".word") != string::npos) {
                processWord(line, data_mp, outputFile); // Call processWord function
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
