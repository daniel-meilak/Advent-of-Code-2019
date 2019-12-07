
#include<vector>
#include<algorithm>
#include<iostream>
#include "intcode.hpp"

int main(){

   std::vector<computer_t> amplifier;

   std::vector<int> phase = {0,1,2,3,4};
   int signal = 0;

   int best_signal = 0;
   std::vector<int> best_phase;

   computer_t computer("test_input", {0,0});

   do {
      for (int i=0; i<phase.size(); i++){
         computer.reset({phase[i], signal});
         computer.run();
         signal = computer.output;
      }

      if ( signal > best_signal){
         best_signal = signal;
         best_phase = phase;
      }

   } while (std::next_permutation(phase.begin(), phase.end()));

   std::cout << "Max signal: " << best_signal << std::endl;

   return 0;
}
