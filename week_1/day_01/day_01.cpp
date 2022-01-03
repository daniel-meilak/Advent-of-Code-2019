#include<iostream>
#include<fstream>
#include<vector>
#include<cstdlib>
#include"../../Utils/utils.h"

// forward function declarations
int fuel_for_module(const int &module_mass, const bool part2);

int main(){

   // read input into vector of strings.
   std::vector<int> input = input_to_int(read_input("input_01"));

   // parameters
   int total1 = 0;
   int total2 = 0;

   // calculate fuel required
   size_t size = input.size();
   for (size_t i=0; i < size; i++ ){
      total1 += fuel_for_module(input[i],false);
      total2 += fuel_for_module(input[i],true );
   }

   std::cout << "Answer (part 1): " << total1 << std::endl;
   std::cout << "Answer (part 2): " << total2 << std::endl;

   return 0;
}

// fuel for module calculator
// reqursively works out the fuel required for the calculated fuel
int fuel_for_module(const int &module_mass, const bool part2){

   int fuel = (module_mass/3) - 2;

   if (part2){
      // no fuel required for extra fuel
      if ( (fuel/3 - 2) <= 0 ){ return fuel; }
      // calculate fuel required for extra fuel
      else { return (fuel + fuel_for_module(fuel,part2)); }
   }

   return fuel;
}
