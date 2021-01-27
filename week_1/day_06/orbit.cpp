#include<iostream>
#include<string>
#include<vector>
#include<fstream>
#include<cstdlib>
#include<algorithm>

class orbit_t{
public:
   std::string name;
   std::string linked_to;
   int linked_to_index;
   int links;
   std::vector<std::string> path_to_COM;
   orbit_t( std::string name, std::string linked_to );
};

orbit_t::orbit_t( std::string name, std::string linked_to ){
   this->name = name;
   this->linked_to = linked_to;
   links = 1;
}

int find_planet_index( std::vector<orbit_t> system, std::string name );
std::vector<std::string> read_input();

int main(){

   std::vector<std::string> map;
   map = read_input();

   std::vector<orbit_t> system;

   // create vector of orbit objects
   for (int i=1; i<map.size(); i+=2){
      orbit_t orbit( map[i], map[i-1] );
      system.push_back(orbit);
   }

   // find the index of each planet for later calc.
   for (int i=0; i<system.size(); i++){
      system[i].linked_to_index = find_planet_index( system, system[i].linked_to );
   }

   int links = 0;
   for (int i=0; i<system.size(); i++){

      orbit_t planet = system[i];
      while (planet.linked_to != "COM"){
         system[i].links++;
         system[i].path_to_COM.push_back(planet.linked_to);
         planet = system[planet.linked_to_index];
      }
      system[i].path_to_COM.push_back(planet.linked_to);

      links += system[i].links;
   }

   std::cout << "Number of links = " << links << std::endl;

   int YOU_index = find_planet_index( system, "YOU");
   int SAN_index = find_planet_index( system, "SAN");

   std::string join_at;
   for (int i=0; i<system[YOU_index].path_to_COM.size(); i++){
      for (int j=0; j<system[SAN_index].path_to_COM.size(); j++){

         if ( system[YOU_index].path_to_COM[i] == system[SAN_index].path_to_COM[j] ){
            join_at = system[YOU_index].path_to_COM[i];
            i = system[YOU_index].path_to_COM.size();
            j = system[SAN_index].path_to_COM.size();
         }
      }
   }

   int join_at_index = find_planet_index( system, join_at);

   int YOU_to_SAN = system[YOU_index].links + system[SAN_index].links - 2*system[join_at_index].links - 2;
   std::cout << "Number of links from YOU to SAN: " << YOU_to_SAN << std::endl;

   std::cout << system[YOU_index].links << std::endl;
   std::cout << system[SAN_index].links << std::endl;
   std::cout << system[join_at_index].links << std::endl;

   return 0;
}

int find_planet_index( std::vector<orbit_t> system, std::string name){
   auto it = std::find_if(system.begin(), system.end(), [system, name](orbit_t const& obj){
      return obj.name == name;
   });

   return std::distance(system.begin(), it);
}

std::vector<std::string> read_input(){
   // map of orbits
   std::vector<std::string> map;

   // open input file
   std::ifstream myfile ("input");
   if ( !(myfile.is_open()) ){
      std::cerr << "Error:could not open input" << std::endl;
      std::exit(EXIT_FAILURE);
   }

   // read orbits into map
   std::string line;

   // std::getline(myfile,line);
   // map.push_back(line.substr(0,3));
   // map.push_back(line.substr(4,1));

   while (std::getline(myfile, line)){
      map.push_back(line.substr(0,3));
      map.push_back(line.substr(4,3));
   }

   return map;
}
