#include<vector>
#include<algorithm>
#include<iostream>
#include"intcode.h"
#include"../../Utils/utils.h"

int main(){

   std::vector<int> phase = {5,6,7,8,9};

   int best_signal = 0;
   std::vector<int> best_phase;

   // read input into vector of strings.
   std::vector<int> input = input_to_int(read_input("input", ","));

   // create an amplifier of 5 computers
   std::vector<computer_t> amplifier(5, computer_t(input, {0}));

   do {

      // initialise computers with the correct phase
      for (size_t i=0; i<phase.size(); i++){
         amplifier[i].reset({phase[i]});
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
      if ( output > best_signal){
         best_signal = output;
         best_phase  = phase;
      }

   } while (std::next_permutation(phase.begin(), phase.end()));

   std::cout << "Answer (part 2): " << best_signal << std::endl;

   return 0;
}
