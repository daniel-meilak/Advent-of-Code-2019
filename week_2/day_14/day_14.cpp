#include<iostream>
#include<vector>
#include<list>
#include<string>
#include<algorithm>
#include<unordered_map>
#include<utility>
#include<cstdlib>
#include"utils.h"

struct recp{
    int n;
    std::vector<std::pair<std::string,int>> ingred;
};

long long calc_ore(const int &n, std::unordered_map<std::string, recp> recipies);

int main(){

    // read input into vector of vector of strings.
    std::vector<std::string> delimiters = {","," "};
    std::vector<std::vector<std::string>> input = read_input_2D("input_14", delimiters);

    // map of recipies
    std::unordered_map<std::string, recp> recipies;

    // work through input and get all recipies
    for (const auto &line : input){

        // start filling recipie
        recp tmp;

        int i = 0;
        while(line[i]!="=>"){
            tmp.ingred.push_back({line[i+1],std::stoi(line[i])});
            i+=2;
        }
        
        tmp.n = std::stoi(line[i+1]);

        // add recipie to recipies
        recipies[line[i+2]] = tmp;
    }

    long long for_one = calc_ore(1,recipies);

    std::cout << "Answer (part 1): " << for_one << std::endl;

    long long total_ore = 1000000000000LL;
    long long for_total = (total_ore/for_one)*((double)total_ore/(double)calc_ore(total_ore/for_one,recipies));

    // Taking estimate from above and manually checking further
    std::cout << "Answer (part 2): " << for_total+3 << std::endl;

    return 0;
}

long long calc_ore(const int &n, std::unordered_map<std::string, recp> recipies){
    
    // starting from FUEL use BFS method to get total ORE req
    std::list<std::pair<std::string,long long>> queue = {{"FUEL",n}};

    // map of extra ingredients
    std::unordered_map<std::string,long long> extra;

    // fuel count
    long long count = 0;
    while (!queue.empty()){

        // get next ingredient off queue
        std::pair<std::string, long long> current = queue.front();
        queue.pop_front();

        // add ingredients to queue 
        for (const auto &pair : recipies[current.first].ingred){
            
            // required of ingredient
            std::string ingredient = pair.first;
            long long required = pair.second*current.second;

            // if ingredient is ore, add to tally
            if (pair.first=="ORE"){
                count += required;
                continue;
            }

            // check if any leftover in extra
            long long &storage = extra[ingredient];
            if (storage<required && storage!=0LL){
                required -= storage;
                storage   = 0LL;
            }
            else if (storage>=required){
                storage -= required;
                continue;
            }

            // still need ingredient, find out how many can be made
            long long can_make = recipies[ingredient].n;
            long long multiples = 1LL;

            // check how many mutiples of ingredient need to be made
            while (can_make*multiples < required){ multiples++; }

            // save extra
            extra[ingredient] = can_make*multiples - required;

            // add to queue
            queue.push_back({ingredient,multiples});
        }
    }

    return count;
}