#include<iostream>
#include<fstream>
#include<vector>
#include<sstream>
#include<cstdlib>

std::vector<int> read_csv(std::string filename);

int main(){

   std::vector<int> opcode;
   std::vector<int> opcode_save;

   // read input into vector
   opcode = read_csv("input.txt");
   opcode_save = opcode;

   // brute force combination
   for (int k=0; k<= 99; k++){
      opcode[1] = k;
      for (int j=0; j<=99; j++){
         opcode[2] = j;

         for (int i=0; i<opcode.size(); i+=4){

            int a, b;

            if ( opcode[i] == 1 ){
               a = opcode[opcode[i+1]];
               b = opcode[opcode[i+2]];
               opcode[opcode[i+3]] = a + b;
            }
            else if (opcode[i] == 2){
               a = opcode[opcode[i+1]];
               b = opcode[opcode[i+2]];
               opcode[opcode[i+3]] = a * b;
            }
            else if (opcode[i] == 99){
               break;
            }
            else {
               std::cerr << "opcode must be one of [1,2,99]" << std::endl;
               std::exit(EXIT_FAILURE);
            }
         }

         if ( opcode[0] == 19690720){
            std::cout << "noun= " << k << std::endl;
            std::cout << "verb= " << j << std::endl;
            j = 100;
            k = 100;
         }

         // reset opcode
         opcode = opcode_save;
         opcode[1] = k;
      }
   }

   return 0;

}

// Read input containing comma separated integers
std::vector<int> read_csv(std::string filename){

   std::vector<int> opcode(0);
   std::string line;

   // open file filname
   std::ifstream myfile (filename);
   if ( !(myfile.is_open()) ){
      std::cerr << "Could not open " << filename << std::endl;
      std::exit(EXIT_FAILURE);
   }

   std::getline(myfile,line);
   std::istringstream ss(line);

   // parse csv and put into vector
   std::string temp;
   while(ss){
      if (!getline(ss, temp, ',')) break;
      opcode.push_back(std::stoi(temp));
   }

   return opcode;
}
