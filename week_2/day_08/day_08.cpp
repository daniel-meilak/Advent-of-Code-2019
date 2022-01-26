#include<vector>
#include<iostream>
#include<fstream>
#include<cstdlib>
#include<string>

//std::vector<std::vector<std::string>> read_data(filename);
std::vector<std::string> read_data(std::string filename);

int main(){

   std::vector<std::string> layers;

   layers = read_data("input_08");

   int min_0 = 100000;
   int save_1{0}, save_2{0};

   for (size_t i=0; i<layers.size(); i++){
      int num_0 = 0;
      int num_1 = 0;
      int num_2 = 0;

      for (size_t j=0; j<layers[i].size(); j++){
         if (layers[i][j] == '0'){ num_0++; }
         else if (layers[i][j] == '1'){ num_1++; }
         else if (layers[i][j] == '2'){ num_2++; }
      }

      if ( num_0 < min_0 ){
         min_0  = num_0;
         save_1 = num_1;
         save_2 = num_2;
      }
   }

   std::cout << "Answer (part 1): " << save_1*save_2 << std::endl;

   std::string picture;

   for (size_t i=0; i<150; i++){
      for (size_t j=0; j<layers.size(); j++){

         if (layers[j][i] == '0'){
            picture.push_back(' ');
            break;
         }
         else if (layers[j][i] == '1'){
            picture.push_back('0');
            break;
         }
      }
   }

   std::cout << "Answer (part 2): " << std::endl;
   for (size_t i=0; i<picture.size(); i+=25){
      std::cout << picture.substr(i,25) << std::endl;
   }

   return 0;
}

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

   for (size_t i=0; i<line.size();i+=150){
      pixel = line.substr(i,150);
      layers.push_back(pixel);
   }

   return layers;
}
