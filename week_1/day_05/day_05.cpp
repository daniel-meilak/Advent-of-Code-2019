#include<iostream>
#include<string>
#include<fstream>
#include<cstdlib>
#include<sstream>
#include<vector>
#include"intcode.h"
#include"../../Utils/utils.h"

int main()
{
   // read input into vector of strings.
   std::vector<int> input = input_to_int(read_input("input", ","));

   int in = 1;

   // part 1
   computer_t comp(input, {in});
   comp.run();
   std::cout << "Answer (part 1): " << comp.output << std::endl;

   // part 2
   in = 5;
   comp.reset({in});
   comp.run();
   std::cout << "Answer (part 2): " << comp.output << std::endl;

   return 0;
}
