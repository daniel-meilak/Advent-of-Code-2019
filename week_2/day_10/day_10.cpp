#include<vector>
#include<string>
#include<iostream>
#include<fstream>
#include<algorithm>
#include<numeric>
#include<cmath>

std::vector<std::vector<int>> read_input(std::string filename);
std::vector<int> direction_vector(std::vector<int> vect1, std::vector<int> vect2);
constexpr double pi = 3.14159265358979323846;

class neighbour_t{
public:
   std::vector<int> position;
   double angle;
   double distance;
   neighbour_t(std::vector<int> station, std::vector<int> asteroid);
   int group;
};

neighbour_t::neighbour_t(std::vector<int> station, std::vector<int> asteroid){
   position = asteroid;
   angle = std::atan2(asteroid[0]-station[0],asteroid[1]-station[1])*180/pi;
   distance = std::sqrt( (asteroid[0]-station[0])*(asteroid[0]-station[0]) + (asteroid[1]-station[1])*(asteroid[1]-station[1]));
}


int main(){

   std::vector<std::vector<int>> asteroid_positions = read_input("input");


   size_t detected = 0;
   std::vector<int> best_pos = {0,0};
   std::vector<neighbour_t> neighbour_list;

   for ( auto& station: asteroid_positions ){

      std::vector<std::vector<int>> direction_list;
      std::vector<neighbour_t> temp_neighbour_list;

      for ( auto& asteroid: asteroid_positions ){

         if ( station == asteroid ) continue;

         std::vector<int> direction = direction_vector(station, asteroid);
         neighbour_t neighbour(station,asteroid);
         temp_neighbour_list.push_back(neighbour);

         if ( std::find(direction_list.begin(),direction_list.end(), direction) == direction_list.end() ){
            direction_list.push_back(direction);
         }

         if ( direction_list.size() > detected ){
            detected = direction_list.size();
            best_pos = station;
            neighbour_list = temp_neighbour_list;
         }
      }
   }

   std::sort(neighbour_list.begin(), neighbour_list.end(), [](const neighbour_t &min, const neighbour_t &max){
         return min.angle > max.angle;
      });

   double tol = 0.001;
   int num_diff_angles = 1;
   for (size_t i=0; i<neighbour_list.size()-1; i++){

      neighbour_list[i].group = num_diff_angles;
      if ( (neighbour_list[i].angle < neighbour_list[i+1].angle - tol) || (neighbour_list[i].angle > neighbour_list[i+1].angle + tol) ){
         num_diff_angles++;
      }
   }

   std::cout << "Answer (part 1): " << num_diff_angles << std::endl;

   for (size_t i=0; i<neighbour_list.size(); i++){
      if (neighbour_list[i].group==200){
         std::cout << "Answer (part 2): " << neighbour_list[i].position[0] << "0" << neighbour_list[i].position[1] << std::endl;
         break;
      }
   }

   return 0;
}

std::vector<std::vector<int>> read_input(std::string filename){

   std::vector<std::vector<int>> asteroid_positions;

   std::ifstream myfile (filename);
   if ( !(myfile.is_open()) ){
      std::cerr << "Error: could not open " << filename << std::endl;
      std::exit(EXIT_FAILURE);
   }

   std::string line;
   int i = 0;
   while (getline(myfile,line)){
      int size = line.size();
      for ( int j=0; j<size; j++ ){
         if (line[j] == '#') asteroid_positions.push_back({j,i});
      }
      i++;
   }

   return asteroid_positions;

}

std::vector<int> direction_vector(std::vector<int> vect1, std::vector<int> vect2){

   int a,b,c;

   a = vect2[0]-vect1[0];
   b = vect2[1]-vect1[1];

   c = std::__gcd(a,b);

   return {a/abs(c),b/abs(c)};
}
