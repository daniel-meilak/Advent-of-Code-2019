#include<iostream>
#include<vector>
#include<string>
#include<algorithm>
#include<cstdlib>
#include"../../Utils/utils.h"
#include"intcode.h"

bool in_beam(computer_t &comp, const int x, const int y);

int main(){

    // read input into vector of strings.
    std::vector<long long> input = input_to_llint(read_input("input", ","));

    // grid of bool for tractor beam area
    std::vector<std::vector<bool>> grid(50,std::vector<bool>(50,false));

    // initialise computer 
    computer_t comp(input,{},0);

    // use intcode program to find beam area
    int count = 0;
    for (int y=0; y<50;y++){
        for (int x=0; x<50; x++){

            comp.reset({x,y});
            comp.run();
            if (comp.output.back()){
                grid[y][x] = true;
                count++;
            }
        }
    }

    display(grid);

    // part 2
    // start at x=0, y=200
    int x = 0, y = 200;
    int xsave,ysave;
    bool found_area = false;
    while(!found_area){
        
        // if bottom left isn't in beam, move right
        if (!in_beam(comp,x,y)){
            x++;
            continue;
        }

        // if top right isn't in beam, move down
        if (!in_beam(comp,x+99,y-99)){
            y++;
        }
        // if both corners are in the beam, found the area
        else {
            xsave = x;
            ysave = y-99;
            break;
        }
    }

    std::cout << "Answer (part 1): " << count             << std::endl;
    std::cout << "Answer (part 2): " << xsave*10000+ysave << std::endl;

    return 0;
}

bool in_beam(computer_t &comp, const int x, const int y){

    comp.reset({x,y});
    comp.run();
    if (comp.output.back()){ return true; }
    else { return false; }
}
