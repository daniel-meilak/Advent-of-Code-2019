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
   void multiply();
   void input_function();
   void output_function();
   void jump_if_true();
   void jump_if_false();
   void less_than();
   void equals();
   void stop();
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
   computer_t(std::string filename, std::vector<int> in);
};

computer_t::computer_t(std::string filename, std::vector<int> in){

   // open and read input file
   std::ifstream input_file (filename);
   if ( !(input_file.is_open()) ){
      std::cerr << "Error: could not open " << filename << std::endl;
      std::exit(EXIT_FAILURE);
   }

   std::string line, code;
   getline(input_file, line);
   std::istringstream ss(line);

   // fill memory
   while(ss){
      if ( !getline(ss, code, ',') ) break;
      memory.push_back(std::stoi(code));
   }

   // set required class attributes
   input = in;
   status = "starting";
   memory_save = memory;
   pos_in_memory = 0;
   pos_in_input = 0;
   mode = {0,0,0};
}

void computer_t::add(){
   int a,b;

   if ( mode[0] == 0 ){ a = memory[memory[pos_in_memory+1]]; }
   else { a = memory[pos_in_memory+1]; }

   if ( mode[1] == 0 ){ b = memory[memory[pos_in_memory+2]]; }
   else { b = memory[pos_in_memory+2]; }

   memory[memory[pos_in_memory+3]] = a+b;
   pos_in_memory += 4;
}

void computer_t::multiply(){
   int a,b;

   if ( mode[0] == 0 ){ a = memory[memory[pos_in_memory+1]]; }
   else { a = memory[pos_in_memory+1]; }


   if ( mode[1] == 0 ){ b = memory[memory[pos_in_memory+2]]; }
   else { b = memory[pos_in_memory+2]; }

   memory[memory[pos_in_memory+3]] = a*b;
   pos_in_memory += 4;
}

void computer_t::jump_if_true(){
   int a;
   if ( mode[0] ==0 ){ a = memory[memory[pos_in_memory+1]]; }
   else { a = memory[pos_in_memory+1]; }

   if ( a != 0 ){
      if (mode[1] == 0 ){ pos_in_memory = memory[memory[pos_in_memory+2]]; }
      else { pos_in_memory = memory[pos_in_memory+2]; }
   }
   else { pos_in_memory += 3; }
}

void computer_t::jump_if_false(){
   int a;
   if ( mode[0] == 0 ){ a = memory[memory[pos_in_memory+1]]; }
   else { a = memory[pos_in_memory+1]; }

   if ( a == 0 ){
      if (mode[1] == 0 ){ pos_in_memory = memory[memory[pos_in_memory+2]]; }
      else { pos_in_memory = memory[pos_in_memory+2]; }
   }
   else { pos_in_memory += 3; }
}

void computer_t::less_than(){
   int a,b;

   if ( mode[0] == 0 ){ a = memory[memory[pos_in_memory+1]]; }
   else { a = memory[pos_in_memory+1]; }

   if ( mode[1] == 0 ){ b = memory[memory[pos_in_memory+2]]; }
   else { b = memory[pos_in_memory+2]; }

   if ( a < b ){ memory[memory[pos_in_memory+3]] = 1; }
   else { memory[memory[pos_in_memory+3]] = 0; }
   pos_in_memory += 4;
}

void computer_t::equals(){
   int a,b;

   if ( mode[0] == 0 ){ a = memory[memory[pos_in_memory+1]]; }
   else { a = memory[pos_in_memory+1]; }

   if ( mode[1] == 0 ){ b = memory[memory[pos_in_memory+2]]; }
   else { b = memory[pos_in_memory+2]; }

   if ( a == b ){ memory[memory[pos_in_memory+3]] = 1; }
   else { memory[memory[pos_in_memory+3]] = 0; }
   pos_in_memory += 4;
}

void computer_t::input_function(){
   memory[memory[pos_in_memory+1]] = input[pos_in_input];
   pos_in_input++;
   pos_in_memory += 2;
}

void computer_t::output_function(){
   if ( mode[0] == 0){ output = memory[memory[pos_in_memory+1]];}
   else { output = memory[pos_in_memory+1]; }
   pos_in_memory += 2;
   running = false;
}

void computer_t::stop(){
   running = false;
   status = "finished";
   pos_in_memory += 1;
}

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

void computer_t::execute_instruction(){
   if ( instruction == 1 ){ add(); }
   else if ( instruction == 2 ){ multiply();        }
   else if ( instruction == 3 ){ input_function();  }
   else if ( instruction == 4 ){ output_function(); }
   else if ( instruction == 5 ){ jump_if_true();    }
   else if ( instruction == 6 ){ jump_if_false();   }
   else if ( instruction == 7 ){ less_than();       }
   else if ( instruction == 8 ){ equals();          }
   else if ( instruction == 99 ){ stop();           }
   else {
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
   memory = memory_save;
   pos_in_input = 0;
   pos_in_memory = 0;
   input = in;
   status = "reset";
}

void print_memory( computer_t computer ){
   for (int i=0; i<computer.memory.size(); i++){
      std::cout << computer.memory[i] << " ";
   }
   std::cout << std::endl;
}

#endif // INTCODE_H_
