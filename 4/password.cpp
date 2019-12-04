#include<vector>
#include<iostream>
#include<algorithm>

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

   std::vector<int> pass(6);
   //std::vector<int> answer;

   // for ( int a=1; a<=6; a++){
   //    for ( int)
   // }

   int i;
   int num = 0;
   bool rule1 = true;
   bool rule2 = false;
   int attempt;


   for (pass[0]=1; pass[0]<=6; pass[0]++){
      for (pass[1] = 1; pass[1] <= 9; pass[1]++){
         for (pass[2] = 1; pass[2] <= 9; pass[2]++){
            for (pass[3] = 1; pass[3] <= 9; pass[3]++){
               for (pass[4] = 1; pass[4] <= 9; pass[4]++){
                  for (pass[5] = 1; pass[5] <= 9; pass[5]++){

                     //std::cout << "number: " << vector_to_int(pass) << std::endl;

                     // rule 1, numbers increase or stay the same
                     // as you go through the password
                     for (i=1; i<pass.size(); i++){
                        if ( pass[i] < pass[i-1] ){
                           rule1 = false;
                           break;
                        }
                     }
                     //if (!rule1) continue;

                     //std::cout << "rule1 is: " << rule1 << std::endl;

                     // rule 2, must be a double on its own
                     for (i=1; i<pass.size()-1;i++){
                        if ( pass[i] == pass[i-1] ){
                           if ( (pass[i] != pass[i+1]) && (i-2<0) ){
                              rule2 = true;
                              break;
                           }
                           else if ( (pass[i] != pass[i+1]) && (i-2>=0) && ( pass[i] != pass[i-2]) ){
                              rule2 = true;
                              break;
                           }
                        }
                        else if ( (pass[i] == pass[i+1]) && ( i+2 == pass.size()) ){
                           if ( pass[i] != pass[i-1] ){
                              rule2 = true;
                              break;
                           }
                        }
                     }

                     //std::cout << "rule2 is: " << rule2 << std::endl;

                     if (rule1 && rule2){
                        attempt = vector_to_int(pass);
                        if ( (attempt >= 156218) && (attempt <= 652527) ){
                           std::cout << attempt << std::endl;
                           num++;
                        }
                     }

                     //std::cout << "num: is " << num << std::endl;

                     //std::exit(0);

                     rule1 = true;
                     rule2 = false;

                  }
               }
            }
         }
      }
   }

   std::cout << "number of passwords: " << num << std::endl;

   return 0;

}
