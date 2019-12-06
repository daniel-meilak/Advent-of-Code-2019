#include<vector>
#include<iostream>
#include<algorithm>

class map{
public:
   int number;
   map(int num);
};

map::map(int num){
   number = num;
}

int main(){

   map map1(1);
   map map2(2);
   map map3(3);

   std::vector<map> maps = {map1,map2,map3};

   std::vector<map>::iterator it;

   it = std::find_if(maps.begin(),maps.end(), [](map const& obj){
         return obj.number == 2;
   });

   if (it != maps.end()){
      std::cout << "position is: " << std::distance(maps.begin(),it) << std::endl;
   }

   return 0;
}
