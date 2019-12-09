#include<iostream>
#include"intcode.hpp"

int main(){

   computer_t computer("test_input", {});

   computer.run();

   std::cout << "output: " << computer.output << std::endl;
   std::cout << "status: " << computer.status << std::endl;
}
