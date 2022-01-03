#include<iostream>
#include<fstream>
#include<vector>
#include<sstream>
#include<cstdlib>
#include"../../Utils/utils.h"
#include"intcode.h"

int main(){

   // read input into vector of strings.
   std::vector<int> opcode = input_to_int(read_input("input_02", {","}));

   opcode[1] = 12;
   opcode[2] = 2;

   computer_t comp(opcode,{});
   comp.run();

   std::cout << "Answer (part 1): " << comp.memory[0] << std::endl;
   
   // brute force loop to solve part 2
   int noun, verb;

   bool found_soln = false;
   for (noun=0; noun<100; noun++){
      for (verb=0; verb<100; verb++){
         
         // reset and retry with new noun and verb
         comp.reset({});
         comp.memory[1] = noun;
         comp.memory[2] = verb;
         comp.run();
         if (comp.memory[0] == 19690720){
            found_soln = true;
            break;
         }
      }
      if (found_soln){ break; }
   }
   
   std::cout << "Answer (part 2): " << 100*noun+verb << std::endl;

   return 0;
}

