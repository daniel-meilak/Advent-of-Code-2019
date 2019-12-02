#include<iostream>
#include<fstream>
#include<vector>
#include<sstream>
#include<cstdlib>

std::vector<int> read_csv(std::string filename);
bool compute( std::vector<int>& opcode, int index);

int main(){

   std::vector<int> opcode;

   // read input into vector
   opcode = read_csv("input.txt");

   opcode[1] = 12;
   opcode[2] = 2;

   // work out opcode
   for (int i=0; i<opcode.size(); i+=4){
      if (compute(opcode, i)) break;
   }

   // print result
   std::cout << opcode[0] << std::endl;

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

bool compute( std::vector<int>& opcode, int index){
   int a, b;
   bool end = false;

   // summation
   if ( opcode[index] == 1 ){
      a = opcode[opcode[index+1]];
      b = opcode[opcode[index+2]];

      opcode[opcode[index+3]] = a + b;
   }
   // multiplication
   else if (opcode[index] == 2){
      a = opcode[opcode[index+1]];
      b = opcode[opcode[index+2]];

      opcode[opcode[index+3]] = a * b;
   }
   // end program
   else if (opcode[index] == 99){
      end = true;
   }
   else {
      std::cerr << "opcode must be one of [1,2,99]" << std::endl;
      std::exit(EXIT_FAILURE);
   }

   return end;
}
