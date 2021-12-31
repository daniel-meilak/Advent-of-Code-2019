#include<iostream>
#include<vector>
#include<list>
#include<string>
#include<algorithm>
#include<cstdlib>
#include"../../Utils/utils.h"
#include"intcode.h"

std::list<long long> to_ascii(const std::string &command);
void display_output(const std::vector<long long> &output);

int main(){

    // read input into vector of strings.
    std::vector<long long> input = input_to_int<long long>(read_input("input_25", ","));

    computer_t comp(input,{});
    comp.run();

    std::string in;
    while(true){
        display_output(comp.output);
        std::getline(std::cin,in);
        comp.input = to_ascii(in);
        comp.run();
    }

    std::cout << "Answer (part 1): " << std::endl;
    display_output(comp.output);

    return 0;
}

std::list<long long> to_ascii(const std::string &command){

    std::list<long long> output;

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