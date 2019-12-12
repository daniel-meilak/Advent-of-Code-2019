#include<iostream>
#include<vector>
#include<string>


class planet_t{
public:
   std::string name;
   std::vector<int> pos;
   std::vector<int> vel;
   planet_t(std::string name, std::vector<int> pos);
};

planet_t::planet_t(std::string name, std::vector<int> pos){

   this->name = name;
   this->pos  = pos;
   vel = {0,0,0};
}

void calc_gravity(std::vector<planet_t>& planets){

   for (int i=0; i<planets.size(); i++){
      for (int j=i+1;j<planets.size(); j++){
         for (int axis=0; axis<3; axis++){

            if ( planets[i].pos[axis] > planets[j].pos[axis]){
               planets[i].vel[axis] -= 1;
               planets[j].vel[axis] += 1;
            }
            else if ( planets[i].pos[axis] < planets[j].pos[axis] ){
               planets[i].vel[axis] += 1;
               planets[j].vel[axis] -= 1;
            }
         }
      }
   }
}

int main(){

   std::vector<planet_t> planets;
   planets.push_back(planet_t("Io", {1,3,-11}));
   planets.push_back(planet_t("Europa", {17,-10,-8}));
   planets.push_back(planet_t("Ganymede", {-1,-15,2}));
   planets.push_back(planet_t("Callisto", {12,-4,-4}));

   int total_time_steps = 1000;
   int time_step = 1;

   for (int t=0; t<total_time_steps; t+=time_step){
      // "apply gravity"
      calc_gravity(planets);

      // move planet according to velocity
      for (int i=0; i<planets.size();i++){
         for (int axis=0; axis<3; axis++){
            planets[i].pos[axis] += planets[i].vel[axis];
         }
      }

   }
   std::cout << planets[0].pos[0] <<" " << planets[0].vel[0] << std::endl;

   // calculate total energy
   int total_energy = 0;
   for (int i=0; i<planets.size(); i++){
      int pot_energy = 0;
      int kin_energy = 0;
      for (int axis=0; axis<3; axis++){
         pot_energy += abs(planets[i].pos[axis]);
         kin_energy += abs(planets[i].vel[axis]);
      }

      total_energy += pot_energy*kin_energy;
   }

   std::cout << "Total enery in the system is: " << total_energy << std::endl;

   return 0;
}
