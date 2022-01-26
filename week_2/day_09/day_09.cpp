#include<iostream>
#include<chrono>
#include"intcode.h"
#include"utils.h"

int main(){

   // read input into vector of strings.
   std::vector<long long> input = input_to_int<long long>(read_input("input_09", {","}));

   // part 1
   computer_t comp(input, {1});
   comp.run();
   std::cout << "Answer (part 1): " << comp.output.back() << std::endl;

   // part 2
   comp.reset({2});
   comp.run();
   std::cout << "Answer (part 2): " << comp.output.back() << std::endl;
}
