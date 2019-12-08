#include<vector>
#include<iostream>
#include<fstream>
#include<cstdlib>

std::vector<std::string> read_data(std::string filename);

int main(){

   std::vector<std::string> layers;

   layers = read_data("input");

   std::string picture;

   for (int i=0; i<150; i++){
      for (int j=0; j<layers.size(); j++){

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

   std::cout << "NOTE: Requires monospace font" << std::endl;
   for (int i=0; i<picture.size(); i+=25){
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

   for (int i=0; i<line.size();i+=150){
      pixel = line.substr(i,150);
      layers.push_back(pixel);
   }

   return layers;
}
