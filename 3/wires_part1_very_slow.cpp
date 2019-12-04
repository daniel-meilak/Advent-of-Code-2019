#include<iostream>
#include<fstream>
#include<sstream>
#include<vector>
#include<string>
#include<algorithm>

//#include"wires.hpp"

std::vector<std::vector<std::string>> read_csv(std::string filename);

int main(){

   std::vector<std::vector<std::string>> input_paths;
   std::string move;

   // read intructions into vector of strings
   input_paths = read_csv("input");

   // find size of grid required
   int xmin = 0, xmax = 0, ymin = 0, ymax = 0;
   int x,y;
   for (int i=0; i<input_paths.size(); i++){
      x = 0;
      y = 0;
      for (int j=0; j<input_paths[i].size(); j++){
         move = input_paths[i][j];

         if ( move[0] == 'R' ){
            x += std::stoi( move.substr(1,move.size()-1) );
            if ( x > xmax ) xmax = x;
         }
         else if ( move[0] == 'L' ){
            x -= std::stoi( move.substr(1,move.size()-1) );
            if ( x < xmin ) xmin = x;
         }
         else if ( move[0] == 'U' ){
            y += std::stoi( move.substr(1,move.size()-1) );
            if ( y > ymax ) ymax = y;
         }
         else if ( move[0] == 'D' ){
            y -= std::stoi( move.substr(1,move.size()-1) );
            if ( y < ymin ) ymin = y;
         }
      }
   }

   //std::cout << "xmax:" << xmax << " xmin:" << xmin << " ymin:" << ymin << " ymax:" << ymax << std::endl;
   x = -xmin;
   y = -ymin;
   int distance = 0;
   // create 3D grid of booleans
   std::vector<std::vector<std::vector<bool>>> grid(xmax-xmin+1, std::vector<std::vector<bool>>(ymax-ymin+1, std::vector<bool>(input_paths.size(),false)));
   for (int i=0; i<input_paths.size(); i++){
      for (int j=0; j<input_paths[i].size(); j++){
         move = input_paths[i][j];

         if ( move[0] == 'R' ){
            distance = std::stoi( move.substr(1,move.size()-1) );
            for (int k=x; k<=x+distance;k++){
               grid[k][y][i] = true;
            }
            x += distance;
         }
         else if ( move[0] == 'L' ){
            distance = std::stoi( move.substr(1,move.size()-1) );
            for (int k=x; k>=x-distance;k--){
               grid[k][y][i] = true;
            }
            x -= distance;
         }
         else if ( move[0] == 'U' ){
            distance = std::stoi( move.substr(1,move.size()-1) );
            for (int k=y; k<=y+distance;k++){
               grid[x][k][i] = true;
            }
            y += distance;
         }
         else if ( move[0] == 'D' ){
            distance = std::stoi( move.substr(1,move.size()-1) );
            for (int k=y; k>=y-distance;k--){
               grid[x][k][i] = true;
            }
            y -= distance;
         }
      }
      x = -xmin;
      y = -ymin;
   }

   // for (int i=0; i<grid.size(); i++){
   //    for (int j=0; j<grid[0].size(); j++){
   //       std::cout << grid[i][j][0] << " ";
   //    }
   //    std::cout << std::endl;
   // }
   //
   // std::cout << std::endl;
   //
   // for (int i=0; i<grid.size(); i++){
   //    for (int j=0; j<grid[0].size(); j++){
   //       std::cout << grid[i][j][1] << " ";
   //    }
   //    std::cout << std::endl;
   // }

   //std::cout << "ok " << grid[3][3][1]*grid[3][3][0] << std::endl;

   x = -xmin;
   y = -ymin;
   std::vector<int> manhattan_dist;
   std::vector<std::pair<int,int>> intersections;
   int dist;
   bool check = true;
   // loop through grid and check for intersections
   for (int i=0; i<grid.size(); i++){
      for (int j=0; j<grid[0].size(); j++){
         for (int k=0; k<grid[0][0].size(); k++){
            check *= grid[i][j][k];
         }

         if (check){
            std::cout << x-i << " " << y-j << std::endl;
            dist = abs(x-i) + abs(y-j);
            manhattan_dist.push_back(dist);
         }

         check = true;
      }
   }

   // for (int i=0; i<manhattan_dist.size(); i++){
   //    std::cout << manhattan_dist[i] << std::endl;
   // }

   std::sort(manhattan_dist.begin(),manhattan_dist.end());
   std::cout << "Minimum Distance: " << manhattan_dist[1] << std::endl;

   return 0;
}

// Read input containing comma separated strings
std::vector<std::vector<std::string>> read_csv(std::string filename){

   std::vector<std::vector<std::string>> paths;
   std::vector<std::string> single_path;
   std::string line;

   // open file filname
   std::ifstream myfile (filename);
   if ( !(myfile.is_open()) ){
      std::cerr << "Could not open " << filename << std::endl;
      std::exit(EXIT_FAILURE);
   }

   int x = 0;
   while(std::getline(myfile,line)){
      std::istringstream ss(line);

      // parse csv and put into vector
      std::string temp;
      while(ss){
         if (!std::getline(ss, temp, ',')) break;
         single_path.push_back(temp);
      }

      // add path to 2D vector paths and empty single_path
      paths.push_back(single_path);
      single_path.clear();
      x++;
   }

   return paths;
}
