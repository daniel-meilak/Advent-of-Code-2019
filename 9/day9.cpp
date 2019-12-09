#include<iostream>
#include<chrono>
#include"intcode.hpp"

int main(){

   // Record start time
   auto start = std::chrono::high_resolution_clock::now();

   computer_t computer("input", {2});

   computer.run();

   std::cout << "status: " << computer.status << std::endl;

   // Record end time
   auto finish = std::chrono::high_resolution_clock::now();
   std::chrono::duration<double> elapsed = finish - start;
   std::cout << "Elapsed time: " << elapsed.count() << " s\n";

}
