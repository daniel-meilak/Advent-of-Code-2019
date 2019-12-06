#include<iostream>
#include<string>
#include<vector>
#include<fstream>
#include<cstdlib>
#include<algorithm>

std::vector<string> read_input(){
   // map of orbits
   std::vector<std::string> map;

   // open input file
   std::ifstream myfile (input);
   if ( !(myfile.is_open()) ){
      std::cerr << "Error:could not open input" << std::endl;
      std::exit(EXIT_FAILURE);
   }

   // read orbits into map
   std::string line;
   while (!getline(myfile, line)){
      map.push_back(std::substr(0,3));
      map.push_back(std::substr(4,3));
   }

   return map;
}

class orbit_t{
public:
   std::string name;
   std::string linked_to;
   int linked_to_index;
   int links;
   orbit_t( std::string name, std::string linked_to );
   orbit_t();
};

orbit_t::orbit_t( std::string name, std::string linked_to ){
   this->name = name;
   this->linked_to = linked_to;
   fully_linked = false;
   links = 1;
}

int main(){

   std::vector<std::string> map;
   map = read_input();

   std::vector<orbit_t> system;

   // create vector of orbit objects
   for (int i=1; i<map.size(); i+=2){
      orbit_t orbit( map[i], map[i]-1 );
      system.push_back(orbit);
   }

   // find the index of each planet for later calc.
   for (int i=0; i<system.size(); i++){
      auto it = std::find_if(system.begin(), system.end(), [](system const& obj){
         return obj.name == system[i].linked_to;
      });
      system[i].linked_to_index = std::distance(system.begin(), it);
   }

   orbit_t planet;
   int links = 0;
   for (int i=0; i<system.size(); i++){

      planet = system[i];
      while (planet.linked_to != "COM"){
         system[i].links++;
         planet = system[planet.linked_to_index];
      }

      lins += planet.links;
   }

}
