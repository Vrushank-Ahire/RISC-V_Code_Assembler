#include <iostream>
#include <fstream>
#include <string>

int main() {
    std::ifstream inputFile("input.asm"); // Open the input file
    if (!inputFile.is_open()) {
        std::cerr << "Failed to open the file." << std::endl;
        return 1; // Return error if file cannot be opened
    }

    std::string line;
    // Read each line from the file
    while (std::getline(inputFile, line)) {
        // Remove leading whitespace
        size_t pos = line.find_first_not_of(" \t");
        if (pos != std::string::npos) {
            line = line.substr(pos);
        }

        if (!line.empty()) {
            // Find the position of ":"
            size_t colon_pos = line.find(':');
            if (colon_pos != std::string::npos) {
                // Print the part before ":"
                std::string part1 = line.substr(0, colon_pos);
                // Remove leading whitespace from part1
                size_t part1_pos = part1.find_first_not_of(" \t");
                if (part1_pos != std::string::npos) {
                    part1 = part1.substr(part1_pos);
                }
                std::cout << part1 << std::endl;

                // Print the part after ":"
                std::string part2 = line.substr(colon_pos + 1);
                // Remove leading whitespace from part2
                size_t part2_pos = part2.find_first_not_of(" \t");
                if (part2_pos != std::string::npos) {
                    part2 = part2.substr(part2_pos);
                }
                if (!part1.empty() && !part2.empty()) {

                    std::string instruction;
                    bool firstSpace = true; // Flag to track if the first space is encountered
                    for (char c : part2) {
                        if (c == ' ') {
                            // Only add the space if it's the first space encountered
                            if (firstSpace) {
                                instruction += c;
                                firstSpace = false;
                            }
                        } else {
                            instruction += c;
                        }
                    }

                    part2 = instruction;

                    std::cout << part2 << std::endl;
                }
            } else {
                // Check if it's an instruction line
                bool isInstruction = (line.find('#') == std::string::npos);
                if (isInstruction) {
                    std::string instruction;
                    bool firstSpace = true; // Flag to track if the first space is encountered
                    for (char c : line) {
                        if (c == ' ') {
                            // Only add the space if it's the first space encountered
                            if (firstSpace) {
                                instruction += c;
                                firstSpace = false;
                            }
                        } else {
                            instruction += c;
                        }
                    }
                    std::cout << instruction << std::endl;
                } else {
                    // Print the line if it's not an instruction
                    std::cout << line << std::endl;
                }
            }
        }
    }

    inputFile.close(); // Close the input file
    return 0;
}


//Previous Code
// #include <iostream>
// #include <vector>
// #include <cstring>

// using namespace std;

// vector<string> split(const char *str, char delimiter) {
//     vector<string> tokens;
//     char *token = strtok(const_cast<char*>(str), &delimiter);
//     while (token != nullptr) {
//         tokens.push_back(token);
//         token = strtok(nullptr, &delimiter);
//     }
//     return tokens;
// }

// int main() {
//     FILE *inputFile = fopen("input.asm", "r");
//     if (inputFile == nullptr) {
//         cerr << "Error opening file." << endl;
//         return 1;
//     }

//     char line[256];
//     while (fgets(line, sizeof(line), inputFile)) {
//         // Skip empty lines
//         if (strlen(line) <= 1) {
//             continue;
//         }
        
//         cout <<line;
//         vector<string> words;
//         vector<string> tokens = split(line, ' ');
//         for (const string& token : tokens) {
//             vector<string> subTokens = split(token.c_str(), ' ');
//             for (const string& subToken : subTokens) {
//                 words.push_back(subToken);
//             }
//         }
//         for (const string& word : words) {
//          //   cout << word << endl;
//         }
//     }

//     fclose(inputFile);
//     return 0;
// }

