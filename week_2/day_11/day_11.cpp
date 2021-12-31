#include<vector>
#include<iostream>
#include<algorithm>
#include"intcode.h"
#include"../../Utils/utils.h"

// directions up,right,left,down
const std::vector<std::vector<int>> direction = {{0,1},{1,0},{0,-1},{-1,0}};

bool check_position(std::vector<std::vector<int>> positions, std::vector<int> pos);
std::vector<std::vector<int>> run_comp(computer_t &comp, std::vector<std::vector<bool>>& grid, std::vector<int> pos);

int main(){

   // read input into vector of strings.
   std::vector<long long> input = input_to_int<long long>(read_input("input_11", ","));

   // grid of black/white, initialised as black
   std::vector<std::vector<bool>> grid1(150, std::vector<bool> (150, false));
   std::vector<std::vector<bool>> grid2 = grid1;

   // robot position
   std::vector<int> pos = {75,75};

   // set starting positions to black and while
   grid1[pos[0]][pos[1]] = false;
   grid2[pos[0]][pos[1]] = true;

   computer_t comp1(input, {}, true);
   computer_t comp2(input, {}, true);

   std::vector<std::vector<int>> positions1, positions2;
   positions1 = run_comp(comp1, grid1, pos);
   positions2 = run_comp(comp2, grid2, pos);

   std::cout << "Answer (part 1): " << positions1.size() << std::endl;
   std::cout << "Answer (part 2): " << std::endl;

   // print grid
   // for (int i=grid2.size()-75; i>=70; i--){
   //    for (size_t j=75; j<grid2.size(); j++){
   //       if (grid2[j][i]==0){
   //          std::cout << " ";
   //       }
   //       else std::cout << "0";
   //    }
   //    std::cout << std::endl;
   // }
   display(grid2);
}

bool check_position(std::vector<std::vector<int>> positions, std::vector<int> pos){

   return std::find(positions.begin(), positions.end(), pos) != positions.end();
}

std::vector<std::vector<int>> run_comp(computer_t &comp, std::vector<std::vector<bool>>& grid, std::vector<int> pos){

   // robot direction
   int dir = 0;

   std::vector<std::vector<int>> positions = {pos};

   while (comp.status != "finished"){

      // input current grid black/white status
      comp.input.push_back(grid[pos[0]][pos[1]]);

      comp.run();

      // read colour to paint panel
      grid[pos[0]][pos[1]] = comp.output.back();

      comp.run();

      // read direction change
      if (comp.output.back() == 0LL){
         dir = (dir-1)%4;
         if (dir < 0) dir += 4;
      }
      else {
         dir = (dir+1)%4;
         if (dir > 3) dir -= 4;
      }

      // move robot position
      pos[0] += direction[dir][0];
      pos[1] += direction[dir][1];

      if ( !check_position(positions, pos) ) positions.push_back(pos);
   }

   return positions;
}