#include<iostream>
#include<vector>
#include<string>
#include<algorithm>
#include<cstdlib>
#include"intcode.h"
#include"../../Utils/utils.h"

std::vector<std::vector<char>> build_screen(const std::vector<long long> &pos);

int main(){

    // read input into vector of strings.
    std::vector<long long> input = input_to_int<long long>(read_input("input_13", ","));

    computer_t comp(input,{},false);
    comp.run();
    int b,p; // unused variables for part2
    std::vector<std::vector<char>> screen = build_screen(comp.output,b,p);

    // count block tiles
    int height = screen.size();
    int width  = screen[0].size();
    int blocks = 0;
    for (int y=0; y<height; y++){
        for (int x=0; x<width; x++){
            if (screen[y][x]=='B'){ blocks++; }
        }
    }

    // output screen
    display(screen);

    std::cout << "Answer (part 1): " << blocks << std::endl;

    // part 2;
    comp.reset({});
    comp.memory[0] = 2;

    while(comp.status!="finished"){
        comp.run();
    }

    std::cout << "Answer (part 2): " << comp.get_score() << std::endl;

    return 0;
}



