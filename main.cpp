#include <iostream>
#include <fstream>
#include <string>

using namespace std;

int main()
{
    ifstream inputFile("input.asm"); // Open the input file
    if (!inputFile.is_open())
    {
        cerr << "Failed to open the file." << endl;
        return 1; // Return error if file cannot be opened
    }

    string line;
    // Read each line from the file
    while (getline(inputFile, line))
    {
        // Remove leading whitespace
        size_t pos = line.find_first_not_of(" \t");
        if (pos != string::npos)
        {
            line = line.substr(pos);
        }

        if (!line.empty())
        {
            // Find the position of ":"
            size_t colon_pos = line.find(':');
            if (colon_pos != string::npos)
            {
                // Print the part before ":"
                string part1 = line.substr(0, colon_pos);
                // Remove leading whitespace from part1
                size_t part1_pos = part1.find_first_not_of(" \t");
                if (part1_pos != string::npos)
                {
                    part1 = part1.substr(part1_pos);
                }
                cout << part1 << endl;

                // Print the part after ":"
                string part2 = line.substr(colon_pos + 1);
                // Remove leading whitespace from part2
                size_t part2_pos = part2.find_first_not_of(" \t");
                if (part2_pos != string::npos)
                {
                    part2 = part2.substr(part2_pos);
                }
                if (!part1.empty() && !part2.empty())
                {

                    string instruction;
                    bool firstSpace = true; // Flag to track if the first space is encountered
                    for (char c : part2)
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

                    part2 = instruction;

                    cout << part2 << endl;
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
                    cout << instruction << endl;
                }
                else
                {
                    // Print the line if it's not an instruction

                    cout << line << endl;
                }
            }
        }
    }

    inputFile.close(); // Close the input file
    return 0;
}
