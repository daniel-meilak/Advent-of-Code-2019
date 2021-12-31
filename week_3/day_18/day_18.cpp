#include<iostream>
#include<vector>
#include<string>
#include<algorithm>
#include<cstdlib>
#include<cctype>
#include<tuple>
#include<list>
#include<set>
#include"../../Utils/utils.h"
#include"../../Utils/point.h"

struct state{
    point pos;
    int steps;
    std::vector<bool> keys;

    state(point pos={0,0}, int steps=0, std::vector<bool> keys={0}): pos(pos), steps(steps), keys(keys){};
};

// forward function declarations
int bfs(const std::vector<std::string> &grid, const state &start);

int main(){

    // read input into vector of strings.
    std::vector<std::string> input  = read_input("input_18" , "");
    std::vector<std::string> input2 = read_input("input2", "");
    int height = input.size();
    int width  = input[0].size();

    // set up for part 2
    std::vector<std::vector<char>> in_quarter(4);
    std::vector<state> quarter_start(4);

    // find starting pos and number of keys
    point start;
    int num_keys = 0;
    for (int y=0; y<height; y++){
        for (int x=0; x<width; x++){

            char &tile = input[y][x];

            if (tile=='@'){
                start = {x,y};
                input[y][x]='.';
            }
            else if (islower(tile)){
                num_keys++;

                // find keys in each quarter (part 2)
                if      (y < height/2 && x < width/2){ in_quarter[0].push_back(tile); }
                else if (y < height/2 && x > width/2){ in_quarter[1].push_back(tile); }
                else if (y > height/2 && x < width/2){ in_quarter[2].push_back(tile); }
                else if (y > height/2 && x > width/2){ in_quarter[3].push_back(tile); }
            }
        }
    }

    // create initial states for part 2
    // bots only need to find keys in their corner, all other keys are set to true
    std::vector<std::vector<bool>> quarter_keys(4,std::vector<bool>(num_keys,true));    
    std::vector<point> dirs = {{-1,-1},{1,-1},{-1,1},{1,1}};
    for (int i=0; i<4; i++){
        for (const char &c : in_quarter[i]){
            quarter_keys[i][c - 'a'] = false;
        }
        quarter_start[i].pos  = start + dirs[i];
        quarter_start[i].keys = quarter_keys[i];
    }

    // set up for part 1
    std::vector<bool> keys(num_keys,false);
    state initial(start,0,keys);

    std::cout << "Answer (part 1): " << bfs(input,initial) << std::endl;
    
    // find sum of steps for each bot 
    int sum = 0;
    for (int i=0; i<4; i++){
        sum += bfs(input2,quarter_start[i]);
    }

    std::cout << "Answer (part 2): " << sum << std::endl;

    return 0;
}

int bfs(const std::vector<std::string> &grid, const state &start){

    // directions
    std::vector<point> dirs = {{0,-1},{-1,0},{1,0},{0,1}};

    std::set<std::tuple<point,std::vector<bool>>> uniques = {std::make_tuple(start.pos,start.keys)};
    std::list<state> frontier = {start};
    state current;

    while(!frontier.empty()){
        current = frontier.front();
        frontier.pop_front();

        // if all keys collected, return current step count
        if (std::find(current.keys.begin(), current.keys.end(), false)==current.keys.end()){ break; }

        for (const point &dir : dirs){
            state next = current;
            next.pos   = next.pos + dir;
            next.steps++;

            const char &tile = grid[next.pos.y][next.pos.x];

            // check if state.pos is wall or already seen state
            // if (tile=='#' || uniques.find(next)!=uniques.end()){ continue; }
            if (tile=='#' || uniques.find(std::make_tuple(next.pos,next.keys))!=uniques.end()){ continue; }

            // if next pos blocked by door we dont have key to, continue
            if (isupper(tile) && !next.keys[tile - 'A']){ continue; }

            // if we come across key, set flag
            if (islower(tile)){ next.keys[tile - 'a'] = true; }

            // add next to frontier and uniques
            frontier.push_back(next);
            // uniques.insert(next);
            uniques.insert(std::make_tuple(next.pos,next.keys));
        }
    }

    return current.steps;
}
