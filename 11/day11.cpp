#include<vector>
#include<iostream>
#include<algorithm>
#include"intcode.hpp"

bool check_position(std::vector<std::vector<int>> positions, std::vector<int> pos);

int main(){

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

   computer_t intcode("input", {}, true);

   while (intcode.status != "finished"){

      //std::cout << "Current pos: " << pos[0] << "," << pos[1] << std::endl;

      // input current grid black/white status
      intcode.input.push_back(grid[pos[0]][pos[1]]);

      intcode.run();

      // read colour to paint panel
      grid[pos[0]][pos[1]] = intcode.output;

      intcode.run();

      // read direction change
      if (intcode.output == 0){
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

   std::cout << "Positions accessed: " << positions.size() << std::endl;


   // print grid
   for (int i=grid.size()-1; i>=0; i--){
      for (int j=0; j<grid.size(); j++){
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
