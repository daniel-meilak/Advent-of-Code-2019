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

   int total_time_steps = 1;
   bool running = true;
   int axis = 2;

   while(running){

      // "apply gravity"
      calc_gravity(planets);

      // move planet according to velocity
      for (int i=0; i<planets.size();i++){
         for (int axis=0; axis<3; axis++){
            planets[i].pos[axis] += planets[i].vel[axis];
         }
      }

      if (planets[0].vel[axis] == 0){
         if (planets[1].vel[axis] == 0){
            if (planets[2].vel[axis] == 0){
               if (planets[3].vel[axis] == 0){
                  std::cout << "Steps: " << total_time_steps << std::endl;
                  running = false;
               }
            }
         }
      }

      total_time_steps++;
   }

   return 0;
}
