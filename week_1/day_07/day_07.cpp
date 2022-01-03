#include<vector>
#include<algorithm>
#include<iostream>
#include"intcode.h"
#include"../../Utils/utils.h"

int main(){

   std::vector<int> phase1 = {0,1,2,3,4};
   std::vector<int> phase2 = {5,6,7,8,9};

   int part_1 = 0;
   int part_2 = 0;

   // read input into vector of strings.
   std::vector<int> input = input_to_int(read_input("input_07", {","}));

   // create an amplifier of 5 computers
   std::vector<computer_t> amplifier(5, computer_t(input, {0}));

   do {

      // initialise computers with the correct phase
      for (size_t i=0; i<phase1.size(); i++){
         amplifier[i].reset({phase1[i]});
      }

      int output = 0;

      // run amplifier grid for each phase value
      for (size_t i=0; i<amplifier.size(); i++){
         amplifier[i].input.push_back(output);
         amplifier[i].run();
         output = amplifier[i].output;
      }
      
      // save best outputs
      part_1 = std::max(output,part_1);

   } while (std::next_permutation(phase1.begin(), phase1.end()));

   do {

      // initialise computers with the correct phase
      for (size_t i=0; i<phase2.size(); i++){
         amplifier[i].reset({phase2[i]});
      }

      int output = 0;

      // run amplifier grid for each phase value
      while ( amplifier[4].status != "finished" ){
         for (size_t i=0; i<amplifier.size(); i++){
            amplifier[i].input.push_back(output);
            amplifier[i].run();
            output = amplifier[i].output;
         }
      }

      // save best outputs
      part_2 = std::max(output,part_2);

   } while (std::next_permutation(phase2.begin(), phase2.end()));

   std::cout << "Answer (part 2): " << part_1 << std::endl;
   std::cout << "Answer (part 2): " << part_2 << std::endl;

   return 0;
}
