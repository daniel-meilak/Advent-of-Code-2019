#ifndef INTCODE_H_
#define INTCODE_H_

#include <iostream>
#include <string>
#include <fstream>
#include <cstdlib>
#include <sstream>
#include <vector>

class computer_t{
private:
   void add();
   void mul();
   void inp();
   void out();
   void jit();
   void jif();
   void lth();
   void equ();
   void stp();
   
   void read_opcode();
   void execute_instruction();
   std::vector<int> mode;
   int instruction;
   bool running;
   int pos_in_memory;


public:
   int pos_in_input;
   void run();
   void reset(std::vector<int> in);
   std::vector<int> memory;
   std::vector<int> memory_save;
   std::vector<int> input;
   std::string status;
   int output;
   computer_t(const std::vector<int> &opcode, std::vector<int> in);
};

computer_t::computer_t(const std::vector<int> &opcode, std::vector<int> in){

   // set required class attributes
   memory        = opcode;
   input         = in;
   status        = "starting";
   memory_save   = opcode;
   pos_in_memory = 0;
   pos_in_input  = 0;
   mode          = {0,0,0};
}

// add 
void computer_t::add(){
   int a,b;

   a = memory[pos_in_memory+1];
   b = memory[pos_in_memory+2];

   if (!mode[0]){ a= memory[a]; }
   if (!mode[1]){ b= memory[b]; }

   memory[memory[pos_in_memory+3]] = a+b;
   pos_in_memory += 4;
}

// multiply
void computer_t::mul(){
   int a,b;

   a = memory[pos_in_memory+1];
   b = memory[pos_in_memory+2];

   if (!mode[0]){ a= memory[a]; }
   if (!mode[1]){ b= memory[b]; }

   memory[memory[pos_in_memory+3]] = a*b;
   pos_in_memory += 4;
}

// jump if true
void computer_t::jit(){
   int a;
   a = memory[pos_in_memory+1];
   if (!mode[0]){ a= memory[a]; }

   if (a){
      pos_in_memory = memory[pos_in_memory+2];
      if (!mode[1]){ pos_in_memory = memory[pos_in_memory]; }
   }
   else { pos_in_memory += 3; }
}

// jump if false
void computer_t::jif(){
   int a;
   a = memory[pos_in_memory+1];
   if (!mode[0]){ a= memory[a]; }

   if (!a){
      pos_in_memory = memory[pos_in_memory+2];
      if (!mode[1]){ pos_in_memory = memory[pos_in_memory]; }
   }
   else { pos_in_memory += 3; }
}

// less than
void computer_t::lth(){
   int a,b;

   a = memory[pos_in_memory+1];
   b = memory[pos_in_memory+2];

   if (!mode[0]){ a= memory[a]; }
   if (!mode[1]){ b= memory[b]; }

   if ( a < b ){ memory[memory[pos_in_memory+3]] = 1; }
   else        { memory[memory[pos_in_memory+3]] = 0; }
   pos_in_memory += 4;
}

// equal to
void computer_t::equ(){
   int a,b;

   a = memory[pos_in_memory+1];
   b = memory[pos_in_memory+2];

   if (!mode[0]){ a= memory[a]; }
   if (!mode[1]){ b= memory[b]; }

   if ( a == b ){ memory[memory[pos_in_memory+3]] = 1; }
   else         { memory[memory[pos_in_memory+3]] = 0; }
   pos_in_memory += 4;
}

// input
void computer_t::inp(){
   memory[memory[pos_in_memory+1]] = input[pos_in_input];
   pos_in_input++;
   pos_in_memory += 2;
}

// output
void computer_t::out(){
   output = memory[pos_in_memory+1];
   if (!mode[0]){ output = memory[output]; }

   pos_in_memory += 2;
}

// halt 
void computer_t::stp(){
   running = false;
   status = "finished";
   pos_in_memory += 1;
}

// read opcode
void computer_t::read_opcode(){

   int opcode = memory[pos_in_memory];
   instruction = opcode%100;

   opcode /= 100;

   for (int i=0; i<3; i++){
      if ( opcode%10 == 1){ mode[i] = 1; }
      else if ( opcode%10 == 0 ){ mode[i] = 0; }
      else {
         std::cerr << "Invalid mode on position " << pos_in_memory << std::endl;
         std::exit(EXIT_FAILURE);
      }
      opcode /= 10;
   }
}

// execute instruction
void computer_t::execute_instruction(){

   switch(instruction){
      case(1 ): add(); break;
      case(2 ): mul(); break;
      case(3 ): inp(); break;
      case(4 ): out(); break;
      case(5 ): jit(); break;
      case(6 ): jif(); break;
      case(7 ): lth(); break;
      case(8 ): equ(); break;
      case(99): stp(); break;
      default :
         std::cerr << "Bad instruction number at position " << pos_in_memory << std::endl;
         std::exit(EXIT_FAILURE);
   }
}

void computer_t::run(){
   running = true;
   while (running){
      read_opcode();
      execute_instruction();
   }
}

void computer_t::reset(std::vector<int> in){
   memory        = memory_save;
   pos_in_input  = 0;
   pos_in_memory = 0;
   input         = in;
   status        = "reset";
}

void print_memory( computer_t computer ){
   for (size_t i=0; i<computer.memory.size(); i++){
      std::cout << computer.memory[i] << " ";
   }
   std::cout << std::endl;
}

#endif // INTCODE_H_
