#include<iostream>
#include<fstream>
#include<vector>
#include<cstdlib>

// forward function declarations
std::vector<double> read_mass(std::string filename, std::vector<double>& masses);
int fuel_for_module(int module_fuel);

int main(){

   // parameters
   std::vector<double> module_masses(0);
   int total_fuel = 0;

   // read module masses
   read_mass("input", module_masses);

   // calculate fuel required
   for ( int i=0; i < module_masses.size(); i++ ){
      total_fuel += fuel_for_module(module_masses[i]);
   }

   std::cout << "Total fuel required: " << total_fuel << std::endl;

   return 0;
}


// Read input file of doubles into vector and return vector
std::vector<double> read_mass(std::string filename, std::vector<double>& masses){

   double mass=0.0;
   std::ifstream myfile (filename);
   if ( !(myfile.is_open()) ){
      std::cerr << "Could not open " << filename << std::endl;
      std::exit(EXIT_FAILURE);
   }

   while( myfile >> mass){
      masses.push_back(mass);
   }

   return masses;
}

// fuel for module calculator
// reqursively works out the fuel required for the calculated fuel
int fuel_for_module( int module_mass ){

   int fuel = ((int)((double)module_mass/3.0)) - 2;

   // no fuel required for extra fuel
   if ( ((int)((double)fuel/3.0) - 2) <= 0 ){
      return fuel;
   }
   // calculate fuel required for extra fuel
   else {
      return (fuel + fuel_for_module(fuel));
   }

}
