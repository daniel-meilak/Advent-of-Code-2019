#include<iostream>
#include<vector>
#include<string>
#include<algorithm>
#include<cstdlib>
#include<cctype>
#include<utility>
#include<set>
#include<list>
#include<unordered_map>
#include"../../Utils/utils.h"
#include"../../Utils/point.h"

struct path{
    point pos;
    int steps;
    int level;

    path(point p, int steps): pos(p), steps(steps), level(0){};
    path(point p, int steps, int level): pos(p), steps(steps), level(level){};
};

// forward function declarations
int part1(const point &start, const point &end, const path &init, const std::unordered_map<point,point> &portals, const std::vector<std::string> &input);
int part2(const point &start, const point &end, const path &init, const std::unordered_map<point,point> &portals, const std::vector<std::string> &input);
bool outer(const point &pos, const std::vector<std::string> &input);

int main(){

    // read input into vector of strings.
    std::vector<std::string> input = read_input("input", "");

    const int height = input.size();
    const int width  = input[0].size();

    // map of portals and unlinked portals
    std::unordered_map<point,point> portals;
    std::unordered_map<std::string,point> single;

    // find portal pairs
    std::string name(2,' ');
    point pos;
    bool new_portal = false;
    for (int y=0; y<height-1; y++){
        for (int x=0; x<width-1; x++){

            // check for portal name
            if (std::isupper(input[y][x])){
                name[0] = input[y][x];
                
                // down
                if (std::isupper(input[y+1][x])){
                    name[1] = input[y+1][x];

                    // look up for '.' (check not at border)
                    if (y-1 >= 0 && input[y-1][x]=='.'){ pos = {x,y-1}; }
                    // not above, must be below
                    else { pos = {x,y+2}; }
                    new_portal = true;
                }
                
                // right
                if (std::isupper(input[y][x+1])){
                    name[1] = input[y][x+1];

                    // look left for '.' (check not at border)
                    if (x-1 >= 0 && input[y][x-1]=='.'){ pos = {x-1,y}; }
                    // not left, must be right
                    else { pos = {x+2,y}; }
                    new_portal = true;
                }
            }

            // if we found a vaild portal
            if (new_portal){

                // check if already in list
                if (single.find(name)!=single.end()){
                    
                    // create two portal links
                    portals[pos] = single[name];
                    portals[single[name]] = pos;
                }
                // if not, add to single list
                else { single[name] = pos; }

                new_portal = false;
            }
        }
    }

    point start = single["AA"];
    point end   = single["ZZ"];
    path init(start,0);

    std::cout << "Answer (part 1): " << part1(start,end,init,portals,input) << std::endl;
    std::cout << "Answer (part 2): " << part2(start,end,init,portals,input) << std::endl;

    return 0;
}

int part1(const point &start, const point &end, const path &init, const std::unordered_map<point,point> &portals, const std::vector<std::string> &input){

    int steps=0;
    std::set<point> uniques = {start};
    std::list<path> frontier = {init};
    std::vector<point> dirs = {{1,0},{-1,0},{0,1},{0,-1}}; 

    while(!frontier.empty()){
        path current = frontier.front();
        frontier.pop_front();

        // if we're at end
        if (current.pos==end){
            steps = current.steps;
            break;
        }

        // check neighbours
        for (const auto &dir : dirs){
            path next(current.pos+dir,current.steps+1);

            const char &c = input[next.pos.y][next.pos.x];

            // check if not wall and unique
            if (c=='#' || uniques.find(next.pos)!=uniques.end()){ continue; }
            
            // check if next is a portal (ignore AA at start)
            if (std::isupper(c)){
                if (current.pos==start){ continue; }
                next.pos = portals.at(current.pos);
            }

            // add to frontier and uniques
            frontier.push_back(next);
            uniques.insert(next.pos);
        }
    }

    return steps;
}

// check if entering inner or outer portal
bool outer(const point &pos, const std::vector<std::string> &input){

    const int height = input.size();
    const int width  = input[0].size();

    if (pos.x==2 || pos.x==width-3 || pos.y==2 || pos.y==height-3){ return true; }
    else { return false; }
}

int part2(const point &start, const point &end, const path &init, const std::unordered_map<point,point> &portals, const std::vector<std::string> &input){

    int steps=0;
    std::set<std::pair<point,int>> uniques = {{start,0}};
    std::list<path> frontier = {init};
    std::vector<point> dirs = {{1,0},{-1,0},{0,1},{0,-1}}; 

    while(!frontier.empty()){
        path current = frontier.front();
        frontier.pop_front();

        // if we're at end
        if (current.pos==end && current.level==0){
            steps = current.steps;
            break;
        }

        // check neighbours
        for (const auto &dir : dirs){
            path next(current.pos+dir,current.steps+1,current.level);

            const char &c = input[next.pos.y][next.pos.x];

            // check if not wall and unique
            if (c=='#' || uniques.find({next.pos,next.level})!=uniques.end()){ continue; }
            
            // check if next is a portal (ignore AA at start)
            if (std::isupper(c)){
                if (current.pos==start || current.pos==end){ continue; }

                // check if going up or down a level
                if (outer(current.pos,input)){
                    if (current.level==0){ continue; }
                    else { next.level--; }
                }
                else { next.level++; }
                
                next.pos = portals.at(current.pos);
            }

            // add to frontier and uniques
            frontier.push_back(next);
            uniques.insert({next.pos,next.level});
        }
    }

    return steps;
}