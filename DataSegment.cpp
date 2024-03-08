#include <iostream>
#include <bits/stdc++.h>
using namespace std;

int main()
{
    string filename = "inputDataSeg.asm";
    ifstream inputFile(filename);
    if(!inputFile.is_open())
    {
        cerr << "Error opening file: " << filename<< endl;
        return 1;
    }

    string line;
    int flag = 1;
    while(getline(inputFile,line))
    {
        size_t found_data = line.find(".data");
        size_t found_text = line.find(".text");

        if(line.empty())
        {
            continue;
        }

        if(found_data != string::npos)
        {
            flag = 1;
            continue;
        }
        else if(found_text != string::npos)
        {
            flag = 0;
        }

        if(flag == 1)
        {
            cout << line << endl;
        }
        if(flag == 0)
        {
            continue;
        }
    }
    
    inputFile.close();
    return 0;
}