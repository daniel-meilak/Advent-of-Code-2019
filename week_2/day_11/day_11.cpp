#include<vector>
#include<iostream>
#include<algorithm>
#include"intcode.h"
#include"../../Utils/utils.h"

bool check_position(std::vector<std::vector<int>> positions, std::vector<int> pos);

int main(){

   // read input into vector of strings.
   std::vector<long long> input = input_to_llint(read_input("input", ","));

   // grid of black/white, initialised as black
   std::vector<std::vector<bool>> grid(100, std::vector<bool> (100, false));

   // directions up,right,left,down
   std::vector<std::vector<int>> direction = {{0,1},{1,0},{0,-1},{-1,0}};

   // robot position
   std::vector<int> pos = {50,50};

   // set starting grid point to white
   grid[pos[0]][pos[1]] = true;

   // robot direction
   int dir = 0;

   // vector of positions accessed
   std::vector<std::vector<int>> positions = {{50,50}};

   computer_t comp(input, {}, true);

   while (comp.status != "finished"){

      //std::cout << "Current pos: " << pos[0] << "," << pos[1] << std::endl;

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

   std::cout << "Answer (part 1): " << positions.size() << std::endl;
   std::cout << "Answer (part 2): " << std::endl;


   // print grid
   for (int i=grid.size()-50; i>=45; i--){
      for (size_t j=50; j<grid.size(); j++){
         if (grid[j][i]==0){
            std::cout << " ";
         }
         else std::cout << "0";
      }
      std::cout << std::endl;
   }
}

bool check_position(std::vector<std::vector<int>> positions, std::vector<int> pos){

   if (std::find(positions.begin(), positions.end(), pos) != positions.end()){
      return true;
   }
   else return false;

}
