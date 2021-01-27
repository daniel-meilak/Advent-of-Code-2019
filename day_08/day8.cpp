#include<vector>
#include<iostream>
#include<fstream>
#include<cstdlib>

//std::vector<std::vector<std::string>> read_data(filename);
std::vector<std::string> read_data(std::string filename);

int main(){

   std::vector<std::string> layers;

   layers = read_data("input");

   int min_0 = 100000;
   int save_0, save_1, save_2;

   for (int i=0; i<layers.size(); i++){
      int num_0 = 0;
      int num_1 = 0;
      int num_2 = 0;

      for (int j=0; j<layers[i].size(); j++){
         if (layers[i][j] == '0'){ num_0++; }
         else if (layers[i][j] == '1'){ num_1++; }
         else if (layers[i][j] == '2'){ num_2++; }
      }

      if ( num_0 < min_0 ){
         min_0 = num_0;
         save_0 = num_0;
         save_1 = num_1;
         save_2 = num_2;
      }
   }

   std::cout << "1 * 2= " << save_1*save_2 << std::endl;

   return 0;
}

// std::vector<std::vector<std::string>> read_data(std::string filename){
//
//    std::ifstream myfile (filename);
//    if ( !(myfile.is_open()) ){
//       std::cerr << "Could not open " << filename << std::endl;
//       std::exit(EXIT_FAILURE);
//    }
//
//    std::string line;
//    std::getline(myfile, line);
//
//    std::vector<std::string> pixel;
//    std::vector<std::vector<std::string>> layers;
//
//    for (int i=0; i<line.size();i+=25){
//       pixel.push_back(line.substr(i,25));
//       if (pixel.size() == 6){
//          layers.push_back(pixel);
//          pixel.clear();
//       }
//    }
//
//    return layers;
// }

std::vector<std::string> read_data(std::string filename){

   std::ifstream myfile (filename);
   if ( !(myfile.is_open()) ){
      std::cerr << "Could not open " << filename << std::endl;
      std::exit(EXIT_FAILURE);
   }

   std::string line;
   std::getline(myfile, line);

   std::string pixel;
   std::vector<std::string> layers;

   for (int i=0; i<line.size();i+=150){
      pixel = line.substr(i,150);
      layers.push_back(pixel);
   }

   return layers;
}
