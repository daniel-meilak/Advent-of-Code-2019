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
   void srb();
   void stp();

   void read_opcode();
   void execute_instruction();
   std::vector<int> mode;
   long instruction;
   bool running;
   bool pause;
   int  pos_in_memory;
   int  last_pos_inp;
   long rb;


public:
   int pos_in_input;
   void run();
   void reset(std::vector<long long> in);

   std::vector<long long> memory;
   std::vector<long long> memory_save;
   std::vector<long long> input;
   std::vector<long long> output;
   std::string status;
   computer_t(const std::vector<long long> &opcode, std::vector<long long> in, bool pause_out);
   computer_t(){};
};

computer_t::computer_t(const std::vector<long long> &opcode, std::vector<long long> in, bool pause_out){

   // start memory with opcode instructions
   memory = opcode;

   // resize memory to have a lot of extra space
   memory.resize(1000000);

   // set required class attributes
   input         = in;
   status        = "starting";
   memory_save   = opcode;
   pos_in_memory = 0;
   last_pos_inp  = 0;
   pos_in_input  = 0;
   rb            = 0;
   mode          = {0,0,0};
   pause         = pause_out;
}

void computer_t::add(){
   long long a = memory[pos_in_memory+1];
   long long b = memory[pos_in_memory+2];
   long long c = memory[pos_in_memory+3];

   if      (mode[0]==0){ a = memory[a   ]; }
   else if (mode[0]==2){ a = memory[a+rb]; }

   if      (mode[1]==0){ b = memory[b   ]; }
   else if (mode[1]==2){ b = memory[b+rb]; }

   if      (mode[2]==0){ memory[c   ] = a+b; }
   else if (mode[2]==2){ memory[c+rb] = a+b; }
   pos_in_memory += 4;
}

void computer_t::mul(){
   long long a = memory[pos_in_memory+1];
   long long b = memory[pos_in_memory+2];
   long long c = memory[pos_in_memory+3];

   if      (mode[0]==0){ a = memory[a  ];  }
   else if (mode[0]==2){ a = memory[a+rb]; }

   if      (mode[1]==0){ b = memory[b   ]; }
   else if (mode[1]==2){ b = memory[b+rb]; }

   if      (mode[2]==0){ memory[c   ] = a*b; }
   else if (mode[2]==2){ memory[c+rb] = a*b; }
   pos_in_memory += 4;
}

void computer_t::jit(){
   long long a = memory[pos_in_memory+1];
   long long b = memory[pos_in_memory+2];

   if      (mode[0]==0){ a = memory[a   ]; }
   else if (mode[0]==2){ a = memory[a+rb]; }


   if ( a != 0 ){
      if      (mode[1]==0){ pos_in_memory = memory[b   ]; }
      else if (mode[1]==2){ pos_in_memory = memory[b+rb]; }
      else if (mode[1]==1){ pos_in_memory = b;            }
   }
   else { pos_in_memory += 3; }
}

void computer_t::jif(){
   long long a = memory[pos_in_memory+1];
   long long b = memory[pos_in_memory+2];

   if      (mode[0]==0){ a = memory[a   ]; }
   else if (mode[0]==2){ a = memory[a+rb]; }

   if ( a == 0 ){
      if      (mode[1]==0){ pos_in_memory = memory[b   ]; }
      else if (mode[1]==2){ pos_in_memory = memory[b+rb]; }
      else if (mode[1]==1){ pos_in_memory = b;            }
   }
   else { pos_in_memory += 3; }
}

void computer_t::lth(){
   long long a = memory[pos_in_memory+1];
   long long b = memory[pos_in_memory+2];
   long long c = memory[pos_in_memory+3];

   if      (mode[0]==0){ a = memory[a   ]; }
   else if (mode[0]==2){ a = memory[a+rb]; }

   if      (mode[1]==0){ b = memory[b   ]; }
   else if (mode[1]==2){ b = memory[b+rb]; }


   if      (mode[2]==0){ memory[c              ] = (a<b) ? 1 : 0; }
   else if (mode[2]==2){ memory[c+rb           ] = (a<b) ? 1 : 0; }
   else if (mode[2]==1){ memory[pos_in_memory+3] = (a<b) ? 1 : 0; }
   
   pos_in_memory += 4;
}

void computer_t::equ(){
   long long a = memory[pos_in_memory+1];
   long long b = memory[pos_in_memory+2];
   long long c = memory[pos_in_memory+3];

   if      (mode[0]==0){ a = memory[a   ]; }
   else if (mode[0]==2){ a = memory[a+rb]; }

   if      (mode[1]==0){ b = memory[b   ]; }
   else if (mode[1]==2){ b = memory[b+rb]; }

   if      (mode[2]==0){ memory[c              ] = (a==b) ? 1 : 0; }
   else if (mode[2]==2){ memory[c+rb           ] = (a==b) ? 1 : 0; }
   else if (mode[2]==1){ memory[pos_in_memory+3] = (a==b) ? 1 : 0; }

   pos_in_memory += 4;
}

void computer_t::inp(){
   // if (last_pos_inp!=pos_in_input){
   //    last_pos_inp++;
   //    running = false;
   //    return;
   // }

   long long a = memory[pos_in_memory+1];

   if      (mode[0]==0){ memory[a              ] = input[pos_in_input]; }
   else if (mode[0]==2){ memory[a+rb           ] = input[pos_in_input]; }
   else if (mode[0]==1){ memory[pos_in_memory+1] = input[pos_in_input]; }
   pos_in_input++;
   pos_in_memory += 2;
}

void computer_t::out(){
   long long a = memory[pos_in_memory+1];

   if      (mode[0]==0){ output.push_back(memory[a   ]); }
   else if (mode[0]==2){ output.push_back(memory[a+rb]); }
   else if (mode[0]==1){ output.push_back(a           ); }
   
   if (pause){ running = false; }
   pos_in_memory += 2;
}

void computer_t::srb(){
   long long a = memory[pos_in_memory+1];

   if      (mode[0]==0){ rb += memory[a   ];}
   else if (mode[0]==2){ rb += memory[a+rb];}
   else if (mode[0]==1){ rb += a;           }
   pos_in_memory += 2;
}

void computer_t::stp(){
   running = false;
   status = "finished";
   pos_in_memory += 1;
}

void computer_t::read_opcode(){

   int opcode = memory[pos_in_memory];
   instruction = opcode%100;

   opcode /= 100;

   for (int i=0; i<3; i++){
      if ( opcode%10 == 0){ mode[i] = 0; }
      else if ( opcode%10 == 1 ){ mode[i] = 1; }
      else if ( opcode%10 == 2 ){ mode[i] = 2; }
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
      case(9 ): srb(); break;
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

void computer_t::reset(std::vector<long long> in){
   memory        = memory_save;
   rb            = 0;
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
