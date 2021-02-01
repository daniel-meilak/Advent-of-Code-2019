#include<iostream>
#include<vector>
#include<string>
#include<algorithm>
#include<cstdlib>
#include"../../Utils/utils.h"
#include"intcode.h"

std::vector<long long> to_ascii(const std::string &command);
void display_output(const std::vector<long long> &output);
void to_input( computer_t &comp, const std::vector<long long> &new_input);

int main(){

    // read input into vector of strings.
    std::vector<long long> input = input_to_llint(read_input("input", ","));

    // springscript instructions
    std::string instructions = "NOT C J\nAND D J\nNOT A T\nOR T J\nWALK";
    computer_t comp(input,to_ascii(instructions),0);

    // run part 1
    while(comp.output.size()<50){
        comp.run();
        if (comp.output.back() > 300LL){ break; }
    }
    display_output(comp.output);

    std::cout << "Answer (part 1): " << comp.output.back() << std::endl;
    
    // springscript instructions part 2
    instructions = "NOT C J\nAND D J\nAND H J\nNOT B T\nAND D T\nOR T J\nNOT A T\nOR T J\nRUN";
    comp.reset(to_ascii(instructions));

    // run part 2
    while(comp.output.size()<50){
        comp.run();
        if (comp.output.back() > 300LL){ break; }
    }
    display_output(comp.output);
    
    std::cout << "Answer (part 2): " << comp.output.back() << std::endl;

    return 0;
}

std::vector<long long> to_ascii(const std::string &command){

    std::vector<long long> output;

    for (const char &c : command){
        output.push_back(c);
    }
    output.push_back('\n');

    return output;
}

void display_output(const std::vector<long long> &output){

    std::string s;

    for (auto it=output.rbegin()+1; it!=output.rend(); it++){
        s += *it;
    }
    std::reverse(s.begin(), s.end());

    std::cout << s << std::endl;
}

void to_input( computer_t &comp, const std::vector<long long> &new_input){

    for (const long long &l : new_input){
        comp.input.push_back(l);
    }
}
