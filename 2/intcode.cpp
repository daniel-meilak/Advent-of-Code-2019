#include<iostream>
#include<fstream>
#include<vector>
#include<sstream>
#include<cstdlib>

std::vector<int> read_csv(std::string filename);

int main(){

   std::vector<int> opcode;

   // read input into vector
   opcode = read_csv("input.txt");

   opcode[1] = 12;
   opcode[2] = 2;

   // work out opcode
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

   // print result
   std::cout << opcode[0];
   for (int i=1; i<opcode.size(); i++){
     std::cout << "," << opcode[i];
   }
   std::cout << std::endl;

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
