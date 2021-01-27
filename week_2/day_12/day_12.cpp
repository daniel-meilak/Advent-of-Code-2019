#include<iostream>
#include<vector>
#include<numeric>
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

   for (size_t i=0; i<planets.size(); i++){
      for (size_t j=i+1;j<planets.size(); j++){
         for (size_t axis=0; axis<3; axis++){

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

std::vector<long long> get_axis(const std::vector<planet_t> &planets, const int &n){
   return {planets[0].pos[n], planets[1].pos[n], planets[2].pos[n], planets[3].pos[n]};
}

int main(){

   std::vector<planet_t> planets, copy;
   planets.push_back(planet_t("Io"      , { 1,  3,-11}));
   planets.push_back(planet_t("Europa"  , {17,-10, -8}));
   planets.push_back(planet_t("Ganymede", {-1,-15,  2}));
   planets.push_back(planet_t("Callisto", {12, -4, -4}));
   copy = planets;

   int total_time_steps = 1000;
   int time_step = 1;

   for (int t=0; t<total_time_steps; t+=time_step){
      
      // "apply gravity"
      calc_gravity(planets);

      // move planet according to velocity
      for (size_t i=0; i<planets.size();i++){
         for (int axis=0; axis<3; axis++){
            planets[i].pos[axis] += planets[i].vel[axis];
         }
      }

   }

   // calculate total energy
   int total_energy = 0;
   for (size_t i=0; i<planets.size(); i++){
      int pot_energy = 0;
      int kin_energy = 0;
      for (int axis=0; axis<3; axis++){
         pot_energy += abs(planets[i].pos[axis]);
         kin_energy += abs(planets[i].vel[axis]);
      }

      total_energy += pot_energy*kin_energy;
   }

   std::cout << "Answer (part 1): " << total_energy << std::endl;

   // part 2
   planets = copy;
   total_time_steps = 1;

   long long x_repeat = 0, y_repeat = 0, z_repeat = 0;
   std::vector<long long> x_init = get_axis(planets,0);
   std::vector<long long> y_init = get_axis(planets,1);
   std::vector<long long> z_init = get_axis(planets,2);

   while(!x_repeat || !y_repeat || !z_repeat){

      // "apply gravity"
      calc_gravity(planets);

      // move planet according to velocity
      for (size_t i=0; i<planets.size();i++){
         for (int axis=0; axis<3; axis++){
            planets[i].pos[axis] += planets[i].vel[axis];
         }
      }
      
      if (x_repeat==0 && x_init==get_axis(planets,0)){ x_repeat = total_time_steps; }
      if (y_repeat==0 && y_init==get_axis(planets,1)){ y_repeat = total_time_steps; }
      if (z_repeat==0 && z_init==get_axis(planets,2)){ z_repeat = total_time_steps; }

      total_time_steps++;
   }

   long long period = std::lcm(x_repeat+1, std::lcm(y_repeat+1, z_repeat+1));

   std::cout << "Answer (part 2): " << period << std::endl;

   return 0;
}
