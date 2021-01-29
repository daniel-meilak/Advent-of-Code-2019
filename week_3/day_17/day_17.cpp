#include<iostream>
#include<vector>
#include<string>
#include<algorithm>
#include<cstdlib>
#include"../../Utils/utils.h"
#include"intcode.h"

// forward funciton declaration
std::vector<long long> to_ascii(const std::string &input);

int main(){

    // read input into vector of strings.
    std::vector<long long> input = input_to_llint(read_input("input", ","));

    computer_t comp(input,{},false);
    comp.run();

    // grid to hold scaffold image
    std::vector<std::vector<char>> grid(1);

    // starting level of scaffold
    int i=0;

    // work through output of comp
    for (const int &ascii : comp.output){

        switch(ascii){
            default:
                grid[i].push_back(ascii);
                break;
            case(10):
                grid.push_back({});
                i++;
                break;                
        }
    }

    const int height = grid.size();
    const int width  = grid[0].size();

    // find alignment param for each intersection
    int alignment = 0;
    for (int y=1; y<height-3; y++){
        for (int x=1; x<width-1; x++){

            if (grid[y][x]=='#' && grid[y+1][x]=='#' && grid[y-1][x]=='#' && grid[y][x+1]=='#' && grid[y][x-1]=='#'){
                alignment += x*y;
            }
        }
    }

    display(grid);

    std::cout << "Answer (part 1): " << alignment << std::endl;
    
    // part2
    // create main function, then the movement functions
    std::vector<long long> main_func = to_ascii("A,B,B,A,B,C,A,C,B,C");
    std::vector<long long> func_A    = to_ascii("L,4,L,6,L,8,L,12");
    std::vector<long long> func_B    = to_ascii("L,8,R,12,L,12");
    std::vector<long long> func_C    = to_ascii("R,12,L,6,L,6,L,8");
    std::vector<long long> feed      = to_ascii("n");

    // append all inputs
    std::vector<long long> full_input;
    full_input.insert(full_input.end(), main_func.begin(), main_func.end());
    full_input.insert(full_input.end(), func_A.begin(), func_A.end());
    full_input.insert(full_input.end(), func_B.begin(), func_B.end());
    full_input.insert(full_input.end(), func_C.begin(), func_C.end());
    full_input.insert(full_input.end(), feed.begin(), feed.end());

    // reset computer and supply input and 2 in mem[0] to take control of movement
    comp.reset(full_input);
    comp.memory[0] = 2;

    // run comp
    comp.run();

    std::cout << "Answer (part 2): " << comp.output.back() << std::endl;

    return 0;
}

std::vector<long long> to_ascii(const std::string &input){
    
    std::vector<long long> output;

    for (const char &c: input){
        // convert char to ascii num
        int code = c;

        // add to output
        output.push_back(code);
    }

    // add ascii newline to end
    output.push_back(10);

    // return int representation of output
    return output;
}
