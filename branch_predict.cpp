#include <bits/stdc++.h>
using namespace std;

map<string, bool> inst_mp; // Declaration moved outside of main
vector<pair<long long, int>> inst_vect;
map<long long, pair<string, int>> branch_map;
map<long long, int> one_bit_maps;
map<long long, pair<int, int>> two_bit_maps;
map<long long, pair<int, int>> s_one;
map<long long, pair<int, int>> s_two;
map<long long, pair<int, int>> s_a_nt;
map<long long, pair<int, int>> s_a_t;
map<long long, pair<long long, string>> branch_buffer;

long long conv_hex_to_dec(string input)
{
    long long ans = 0;
    for (int i = 0; i < 8; i++)
    {
        ans *= 16;

        if (input[i] <= '9')
        {
            ans += (input[i] - '0');
        }

        else
        {
            ans += (input[i] - 'a' + 10);
        }
    }

    return ans;
}

string con_dec_hex(long long input)
{
    string ans;
    for(int i = 0; i<8; i++){
        int temp = input%16;
        if(temp<10){
            ans = (char)('0' + temp) + ans;
        }

        else{
            ans = (char)('a' + temp - 10) + ans;
        }

        input = input/16;
    }
    return ans;
}


void create_map()
{
    inst_mp = {
        {"beq", true},
        {"bne", true},
        {"blt", true},
        {"bge", true},
        {"bltu", true},
        {"bgeu", true},
        {"beqz", true},
        {"bnez", true},
    };
}
void intialise_all()
{
    for (auto &it : branch_map)
    {
        pair<int, int> temp;
        temp.first = 0;
        temp.second = 0;
        long long value = it.first;
        s_one[value] = temp;
        s_two[value] = temp;
        s_a_nt[value] = temp;
        s_a_t[value] = temp;
        one_bit_maps[value] = 0;
        temp.first = 0;
        temp.second = 0;
        two_bit_maps[value] = temp;
        pair<long long, string> temp2;
        temp2.first = 0;
        temp2.second = "";
        branch_buffer[value] = temp2;
    }
}

void call_for_1_bit(int result, long long value)
{
    if (result == 1)
    {
        if (one_bit_maps[value] == 1)
        {
            s_one[value].first += 1;
            s_one[value].second += 1;
        }
        else
        {
            s_one[value].second += 1;
            one_bit_maps[value] = 1;
        }
    }
    else
    {
        if (one_bit_maps[value] == 1)
        {
            s_one[value].second += 1;
            one_bit_maps[value] = 0;
        }
        else
        {
            s_one[value].first += 1;
            s_one[value].second += 1;
        }
    }
}
void call_for_2_bit(int result, long long value)
{
    int first = two_bit_maps[value].first;
    int second = two_bit_maps[value].second;
    if (result == 1)
    {
        if (first == 1 && second == 1)
        {
            s_two[value].first += 1;
            s_two[value].second += 1;
        }
        else if (first == 1 && second == 0)
        {
            two_bit_maps[value].first = 1;
            two_bit_maps[value].second = 1;
            s_two[value].first += 1;
            s_two[value].second += 1;
        }
        else if (first == 0 && second == 0)
        {
            two_bit_maps[value].first = 0;
            two_bit_maps[value].second = 1;
            s_two[value].second += 1;
        }
        else
        {
            two_bit_maps[value].first = 1;
            two_bit_maps[value].second = 1;
            s_two[value].second += 1;
        }
    }
    else
    {
        if (first == 1 && second == 1)
        {
            two_bit_maps[value].first = 1;
            two_bit_maps[value].second = 0;
            s_two[value].second += 1;
        }
        else if (first == 1 && second == 0)
        {
            two_bit_maps[value].first = 0;
            two_bit_maps[value].second = 0;
            s_two[value].second += 1;
        }
        else if (first == 0 && second == 0)
        {
            s_two[value].first += 1;
            s_two[value].second += 1;
        }
        else
        {
            two_bit_maps[value].first = 0;
            two_bit_maps[value].second = 0;
            s_two[value].first += 1;
            s_two[value].second += 1;
        }
    }
}
void call_for_always_taken(int result, long long value)
{
    if (result == 1)
    {
        s_a_t[value].first += 1;
        s_a_t[value].second += 1;
    }
    else
    {
        s_a_t[value].second += 1;
    }
}
void call_for_always_not_taken(int result, long long value)
{
    if (result == 0)
    {
        s_a_nt[value].first += 1;
        s_a_nt[value].second += 1;
    }
    else
    {
        s_a_nt[value].second += 1;
    }
}

double check_accuracy(map<long long, pair<int, int>> &mp)
{
    int correct = 0;
    int total = 0;
    for (auto &it : mp)
    {
        correct += it.second.first;
        total += it.second.second;
    }
    return (correct * 100.00) / total;
}

int main()
{
    ofstream outputFile("outputDataSeg.txt", std::ios::app);

    ifstream file("recur_test");
    string line;
    create_map(); // Call the function to create the map
    int i = 0;
    while (getline(file, line))
    {
        // cout<<i++<<endl;
        istringstream iss(line);
        string token;

        size_t bc_pos = line.find(')');
        bc_pos++;
        while (line[bc_pos] == ' ')
        {
            bc_pos++;
        }
        int bc_end = bc_pos;

        while (line[bc_end] != ' ')
        {
            // cout<<line[bc_end]<<endl;
            bc_end++;
        }

        string inst = line.substr(bc_pos, bc_end - bc_pos);
        // cout<<inst<<endl;
        string inst_2 = line.substr(bc_pos, line.length() - 1);
        pair<string, int> temp2;
        temp2.first = inst_2;
        size_t pc_pos = line.find("0x");
        long long pc;
        if (pc_pos != string::npos)
        {
            // Extract the PC value
            string pc_hex = line.substr(pc_pos + 2, 8); // Assuming PC is always 10 characters long
            pc = conv_hex_to_dec(pc_hex);
            // cout<<pc_hex<<" "<<pc<<endl;
        }
        pair<long long, int> temp;
        temp.first = pc;
        temp.second = 0;
        if (inst_mp.find(inst) != inst_mp.end())
        {
            // cout<<line<<endl;
            size_t pc_pos = line.find("pc");
            pc_pos += 2;
            while (line[pc_pos] == ' ')
            {
                pc_pos++;
            }

            char oper = line[pc_pos];
            pc_pos++;

            while (line[pc_pos] == ' ')
                pc_pos++;

            string s_off = "";

            while (line[pc_pos] != ' ' && line[pc_pos] != '\n')
            {
                s_off += line[pc_pos];
                pc_pos++;
            }

            int off = stoi(s_off, nullptr, 10);

            if (oper == '-')
            {
                off *= -1;
            }
            temp2.second = off;
            branch_map.insert(make_pair(pc, temp2));
            temp.second = 1;
        }

        inst_vect.push_back(temp);
    }
    intialise_all();
    int vec_size = inst_vect.size();
    for (int i = 0; i < vec_size - 1; i++)
    {
        if (inst_vect[i].second == 1)
        {
            int off_set = branch_map[inst_vect[i].first].second;
            long long val = inst_vect[i].first + off_set;
            branch_buffer[inst_vect[i].first].first = val;
            int result;
            long long pcx = inst_vect[i].first;
            if (off_set != (inst_vect[i + 1].first - inst_vect[i].first))
            {
                result = 0;
            }
            else
            {
                result = 1;
            }

            if(result == 0){
                branch_buffer[inst_vect[i].first].second += 'N';
            }

            if(result == 1){
                branch_buffer[inst_vect[i].first].second += 'T';
            }

            call_for_always_taken(result, pcx);
            call_for_always_not_taken(result, pcx);
            call_for_1_bit(result, pcx);
            call_for_2_bit(result, pcx);
        }
    }
    double acc_s_a_t = check_accuracy(s_a_t);
    double acc_s_a_nt = check_accuracy(s_a_nt);
    double acc_1_bit = check_accuracy(s_one);
    double acc_2_bit = check_accuracy(s_two);
    outputFile <<"Accuracy for always taken predictor is "<< acc_s_a_t << "%\n";
    outputFile <<"Accuracy for always not taken predictor is  "<<acc_s_a_nt << "%\n";
    outputFile <<"Accuracy for 1 Bit predictor is "<< acc_1_bit << "%\n";
    outputFile <<"Accuracy for 2 Bit predictor is "<< acc_2_bit << "%\n";

    for (auto it = branch_buffer.begin(); it != branch_buffer.end(); ++it) {
        outputFile << "0x"<<con_dec_hex(it->first) << " : " << "0x"<<con_dec_hex(it->second.first) << endl;
        outputFile<<"History : "<<it->second.second<<endl;
    }
    return 0;
}
