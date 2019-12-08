
#include<vector>
#include<algorithm>
#include<iostream>
#include "intcode.hpp"

int main(){

   std::vector<int> phase = {5,5,5,5,5};

   int best_signal = 0;
   std::vector<int> best_phase;

   computer_t computer("test_input", {0,0});
   std::vector<computer_t> amplifier(5, computer);

   do {

      for (int i=0; i<phase.size(); i++){
         amplifier[i].reset({phase[i]});
      }

      int output = 0;

      while ( amplifier[4].status != "finished" ){
         for (int i=0; i<amplifier.size(); i++){
            amplifier[i].input.push_back(output);
            amplifier[i].run();
            output = amplifier[i].output;
            std::cout << amplifier[i].pos_in_input << std::endl;
         }
      }

      std::cout << "next perm" << std::endl;

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
