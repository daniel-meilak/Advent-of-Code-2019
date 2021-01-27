
#include<vector>
#include<algorithm>
#include<iostream>
#include "intcode.hpp"

int main(){

   std::vector<int> phase = {5,6,7,8,9};

   int best_signal = 0;
   std::vector<int> best_phase;

   // create a starting computer point, and an amplifier of 5 computers
   computer_t computer("input", {0});
   std::vector<computer_t> amplifier(5, computer);

   do {

      // initialise computers with the correct phase
      for (int i=0; i<phase.size(); i++){
         amplifier[i].reset({phase[i]});
      }

      int output = 0;

      // run amplifier grid for each phase value
      while ( amplifier[4].status != "finished" ){
         for (int i=0; i<amplifier.size(); i++){
            amplifier[i].input.push_back(output);
            amplifier[i].run();
            output = amplifier[i].output;
         }
      }

      // save best outputs
      if ( output > best_signal){
         best_signal = output;
         best_phase = phase;
      }

   } while (std::next_permutation(phase.begin(), phase.end()));

   std::cout << "Max signal: " << best_signal << std::endl;
   for (int i=0; i<best_phase.size(); i++){
      std::cout << best_phase[i] << " ";
   }
   std::cout << std::endl;

   return 0;
}
