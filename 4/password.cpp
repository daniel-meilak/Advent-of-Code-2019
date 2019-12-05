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

int main(){

   auto start = std::chrono::high_resolution_clock::now();

   std::vector<int> pass(6);

   int i;
   int part1_count = 0;
   int part2_count = 0;
   bool rule1 = true;
   bool rule2 = false;
   bool rule3 = false;
   int attempt;

   // loop through every index of the vector

   for (pass[0]=1; pass[0]<=6; pass[0]++){
      for (pass[1] = 1; pass[1] <= 9; pass[1]++){
         for (pass[2] = 1; pass[2] <= 9; pass[2]++){
            for (pass[3] = 1; pass[3] <= 9; pass[3]++){
               for (pass[4] = 1; pass[4] <= 9; pass[4]++){
                  for (pass[5] = 1; pass[5] <= 9; pass[5]++){

                     // rule 1, numbers increase or stay the same
                     // as you go through the password
                     for (i=1; i<pass.size(); i++){
                        if ( pass[i] < pass[i-1] ){
                           rule1 = false;
                           break;
                        }
                     }

                     // rule 2, must be a double on its own
                     for (i=1; i<pass.size()-1;i++){
                        // if prevous number matches
                        if ( pass[i] == pass[i-1] ){
                           rule3 = true;
                           // and if the next doesnt match and 2nd previous is out of bounds
                           if ( (pass[i] != pass[i+1]) && (i-2<0) ){
                              rule2 = true;
                              break;
                           }
                           // and if the next doesnt match and 2nd previous is in bounds but also doesnt match
                           else if ( (pass[i] != pass[i+1]) && (i-2>=0) && ( pass[i] != pass[i-2]) ){
                              rule2 = true;
                              break;
                           }
                        }
                        // if the next number matches and its the penultimate number i.e. index 4
                        else if ( (pass[i] == pass[i+1]) && ( i+2 == pass.size()) ){
                           rule3 = true;
                           // if the previous doesn't match
                           if ( pass[i] != pass[i-1] ){
                              rule2 = true;
                              break;
                           }
                        }
                     }

                     // if both rules are satisfied
                     if (rule1 && rule3){
                        // make the int
                        attempt = vector_to_int(pass);
                        // check its in the limit, print and add to tally
                        if ( (attempt >= 156218) && (attempt <= 652527) ){
                           //std::cout << attempt << std::endl;
                           part1_count++;
                           if (rule2) part2_count++;
                        }
                     }

                     // refresh rules for next number
                     rule1 = true;
                     rule2 = false;
                     rule3 = false;

                  }
               }
            }
         }
      }
   }

   std::cout << "part1: " << part1_count << std::endl;
   std::cout << "part2: " << part2_count << std::endl;

   auto finish = std::chrono::high_resolution_clock::now();
   std::chrono::duration<double> elapsed = finish-start;
   std::cout << "Elapsed time: " << elapsed.count() << "s" << std::endl;

   return 0;

}
