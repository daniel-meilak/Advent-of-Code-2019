#include<iostream>
#include<fstream>
#include<sstream>
#include<vector>
#include<string>
#include<numeric>
#include<algorithm>

std::vector<std::vector<std::string>> read_csv(std::string filename);

int main(){

   std::vector<std::vector<std::string>> input_paths;
   std::vector<std::vector<std::vector<int>>> paths(4);
   // 4 path lists
   // 0&1 is x and y list of path1
   // 2&3 is x and y list of path2


   // read intructions into vector of strings
   input_paths = read_csv("input");

   std::string move;
   int distance;
   int x = 0;
   int y = 0;

   // loop through instructions
   for (int i=0; i<input_paths.size(); i++){
      for (int j=0; j<input_paths[i].size(); j++){
         move = input_paths[i][j];
         distance = std::stoi( move.substr(1,move.size()-1) );

         // for every instruction, create a vector
         // first value is y coord if horizontal or x coord if vertical.
         // rest are coordinates from min to max
         if ( move[0] == 'R' ){
            std::vector<int> y_vector(distance+1);
            std::iota(y_vector.begin()+1,y_vector.end(),x+1);
            y_vector[0] = y;
            x += distance;
            paths[(i*2)+1].push_back(y_vector);
         }
         else if ( move[0] == 'L' ){
            std::vector<int> y_vector(distance+1);
            std::iota(y_vector.begin()+1,y_vector.end(),x-distance);
            y_vector[0] = y;
            x -= distance;
            std::reverse(y_vector.begin()+1,y_vector.end());
            paths[(i*2)+1].push_back(y_vector);
         }
         else if ( move[0] == 'U' ){
            std::vector<int> x_vector(distance+1);
            std::iota(x_vector.begin()+1,x_vector.end(),y+1);
            x_vector[0] = x;
            y += distance;
            paths[i*2].push_back(x_vector);
         }
         else if( move[0] == 'D' ){
            std::vector<int> x_vector(distance+1);
            std::iota(x_vector.begin()+1,x_vector.end(),y-distance);
            x_vector[0] = x;
            y -= distance;
            std::reverse(x_vector.begin()+1,x_vector.end());
            paths[i*2].push_back(x_vector);
         }
      }
      x=0;
      y=0;
   }

   std::vector<std::vector<int>> intersection;
   std::vector<int> steps;
   // need to compare x path 1 to y path 2, and x path 2 to y path 1
   for (int i=0; i<paths[0].size(); i++){
      for (int j=0; j<paths[3].size(); j++){
         for (int k=1; k<paths[3][j].size(); k++){
            if ( paths[0][i][0] == paths[3][j][k] ){
               for (int z=1; z<paths[0][i].size(); z++){
                  if (paths[3][j][0] == paths[0][i][z]){
                     intersection.push_back({paths[0][i][0],paths[0][i][z]});
                     int start = 0;
                     int sum = 0;
                     for (int a=0; a<i; a++){
                        sum += abs(paths[0][a][0]-start);
                        sum += paths[0][a].size()-1;
                        start = paths[0][a][0];
                     }
                     sum += abs(paths[0][i][0]-start);
                     sum += z;
                     start = 0;
                     for (int b=0; b<j; b++){
                        sum += abs(paths[3][b][0]-start);
                        sum += paths[3][b].size()-1;
                        start = paths[3][b][0];
                     }
                     sum += abs(paths[3][j][0]-start);
                     sum += k;
                     steps.push_back(sum);
                  }
               }
            }
         }
      }
   }

   for (int i=0; i<paths[2].size(); i++){
      for (int j=0; j<paths[1].size(); j++){
         for (int k=1; k<paths[1][j].size(); k++){
            if ( paths[2][i][0] == paths[1][j][k] ){
               for (int z=1; z<paths[2][i].size(); z++){
                  if (paths[1][j][0] == paths[2][i][z]){
                     intersection.push_back({paths[2][i][0],paths[2][i][z]});
                     int start = 0;
                     int sum = 0;
                     for (int a=0; a<i; a++){
                        sum += abs(paths[2][a][0]-start);
                        sum += paths[2][a].size()-1;
                        start = paths[2][a][0];
                     }
                     sum += abs(paths[2][i][0]-start);
                     sum += z;
                     start = 0;
                     for (int b=0; b<j; b++){
                        sum += abs(paths[1][b][0]-start);
                        std::cout << "sum: " << sum-15 << std::endl;
                        sum += paths[1][b].size()-1;
                        start = paths[1][b][0];
                     }
                     sum += abs(paths[1][j][0]-start);
                     sum += k;
                     steps.push_back(sum);
                  }
               }
            }
         }
      }
   }

   for (int i=0; i<intersection.size(); i++){
      std::cout << steps[i] << " " << abs(intersection[i][0])+abs(intersection[i][1]) << std::endl;
   }

   std::sort(steps.begin(),steps.end());
   std::cout << steps[0] << std::endl;


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
