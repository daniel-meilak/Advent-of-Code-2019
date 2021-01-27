#include<vector>
#include<iostream>
#include<algorithm>
#include<chrono>


// turns a vector of ints into an int
// e.g. {1,2,3} becomes 123
int vector_to_int( std::vector<int> password ){
   std::reverse(password.begin(),password.end());

   int decimal = 1;
   int total = 0;

   for (int i=0; i<password.size(); i++){
      total += password[i]*decimal;
      decimal *= 10;
   }

   return total;
}

// checks if number satisfies part 1 or 2
std::vector<bool> check_number( std::vector<int> password ){
   int sequence_length=0;
   int last = 0;
   int value;
   std::vector<bool> part_1_2(2);
   for (int i=0; i<password.size(); i++){
      value = password[i];
      // value always starts as 1 or higher
      if ( value < last ){
         // rule 2 not satisfied
         part_1_2 = {false,false};
         return part_1_2;
      }
      // find a double
      else if ( value == last){
         part_1_2[0] = true;
         sequence_length++;
      }
      else {
         if ( sequence_length == 1 ){
            part_1_2[1] = true;
         }
         sequence_length = 0;
      }
      last = value;
   }
   part_1_2 = {part_1_2[0], sequence_length == 1 || part_1_2[1]};
   return part_1_2;
}

int main(){

   auto start = std::chrono::high_resolution_clock::now();

   std::vector<int> pass(6);

   int i;
   int count_part1 = 0;
   int count_part2 = 0;
   std::vector<bool> part_1_2(2);
   int attempt;
   int sequence_length=0;
   int last = 0;
   int value;

   // loop through every index of the vector

   for (pass[0]=1; pass[0]<=6; pass[0]++){
      for (pass[1] = 1; pass[1] <= 9; pass[1]++){
         for (pass[2] = 1; pass[2] <= 9; pass[2]++){
            for (pass[3] = 1; pass[3] <= 9; pass[3]++){
               for (pass[4] = 1; pass[4] <= 9; pass[4]++){
                  for (pass[5] = 1; pass[5] <= 9; pass[5]++){

                     for (int j=0; j<pass.size(); j++){
                        value = pass[j];
                        // value always starts as 1 or higher
                        if ( value < last ){
                           // rule 2 not satisfied
                           part_1_2 = {false,false};
                           break;
                        }
                        // find a double
                        else if ( value == last){
                           part_1_2[0] = true;
                           sequence_length++;
                        }
                        else {
                           if ( sequence_length == 1 ){
                              part_1_2[1] = true;
                           }
                           sequence_length = 0;
                        }
                        last = value;
                     }
                     part_1_2 = {part_1_2[0], sequence_length == 1 || part_1_2[1]};

                     if (part_1_2[0]){
                        attempt = vector_to_int(pass);
                        if ( attempt >= 156218 && attempt <= 652527 ) count_part1++;
                     }
                     if (part_1_2[1]){
                        attempt = vector_to_int(pass);
                        if ( attempt >= 156218 && attempt <= 652527 ) count_part2++;
                     }

                     sequence_length=0;
                     last = 0;

                  }
               }
            }
         }
      }
   }

   std::cout << "part1: " << count_part1 << std::endl;
   std::cout << "part2: " << count_part2 << std::endl;

   auto finish = std::chrono::high_resolution_clock::now();
   std::chrono::duration<double> elapsed = finish-start;
   std::cout << "Elapsed time: " << elapsed.count() << "s" << std::endl;

   return 0;

}
