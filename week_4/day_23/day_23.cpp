#include<iostream>
#include<vector>
#include<string>
#include<algorithm>
#include<cstdlib>
#include"../../Utils/utils.h"
#include"intcode.h"

long long part1(std::vector<computer_t> network);
long long part2(std::vector<computer_t> network);

int main(){

    // read input into vector of strings.
    std::vector<long long> input = input_to_llint(read_input("input", ","));

    // vector of computers initialised with input instructions
    std::vector<computer_t> network(50,computer_t(input,{},0));

    // input id for each comp
    for (int i=0; i<50; i++){
        network[i].input = {i};
    }

    std::cout << "Answer (part 1): " << part1(network) << std::endl;
    std::cout << "Answer (part 2): " << part2(network) << std::endl;

    return 0;
}

long long part1(std::vector<computer_t> network){
    
    long long y_value;

    bool running = true;
    std::vector<long long> out;
    while(running){

        // run each computer
        for (auto &comp : network){

            comp.run();
            // if comp returns output
            if (comp.output.size()==3){
                out.assign(comp.output.end()-3, comp.output.end());
                comp.output.clear();
            }
            // if no output move to next comp
            else { continue; }

            if (out[0]==255){
                y_value = out[2];
                running = false;
                break;
            }

            // send output to another comp
            network[out[0]].input.push_back(out[1]);
            network[out[0]].input.push_back(out[2]);
        } 
    }

    return y_value;
}

long long part2(std::vector<computer_t> network){
    
    std::vector<long long> y_values;
    long long first_y;
    long long NATx, NATy;

    bool running = true;
    std::vector<long long> out;
    while(running){

        // run each computer
        for (auto &comp : network){

            comp.run();
            // if comp returns output
            if (comp.output.size()==3){
                out.assign(comp.output.end()-3, comp.output.end());
                comp.output.clear();
            }
            // if no output check idle and move to next comp
            else {
            
                // check if computers are idle
                bool idle = true;
                for (const auto &c : network){
                    if (c.input.size()>0 && c.input.back()!=-1LL){ idle=false; }
                }

                if (idle){
                    if (std::find(y_values.begin(), y_values.end(),NATy)!=y_values.end()){
                        first_y = NATy;
                        running = false;
                    }
                    else { y_values.push_back(NATy); }

                    network[0].input.push_back(NATx);
                    network[0].input.push_back(NATy);
                }

                continue;
            }

            // send output to NAT
            if (out[0]==255){
                NATx = out[1];
                NATy = out[2];
            }
            // send output to another comp
            else {
                network[out[0]].input.push_back(out[1]);
                network[out[0]].input.push_back(out[2]);
            }
        } 
    }

    return first_y;
}