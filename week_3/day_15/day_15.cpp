#include<iostream>
#include<vector>
#include<list>
#include<string>
#include<algorithm>
#include<cstdlib>
#include <chrono>
#include <thread>
#include<unordered_map>
#include"../../Utils/utils.h"
#include"../../Utils/point.h"
#include"intcode.h"

using namespace std::chrono_literals;

struct dir{
    point p;
    int in;
};

struct output_t{
    point end;
    size_t longest_path;
    size_t path_length;
    computer_t end_state;
};

// forward function declarations
std::vector<std::vector<char>> build_map(const std::unordered_map<point,computer_t> &grid );
output_t explore_map(const point &start, computer_t comp);

int main(){

    // read input into vector of strings.
    std::vector<long long> input = input_to_llint(read_input("input", ","));

    // create comp and backup state
    computer_t comp(input,{},false);
    computer_t backup = comp;

    // start at 00
    point start = {0,0};

    // Part1 BFS to find goal location
    output_t part1 = explore_map(start,comp);

    // Part2, start from goal loacation, with comp at state from goal location
    output_t part2 = explore_map(part1.end,part1.end_state);

    std::cout << "Answer (part 1): " << part1.path_length                         << std::endl;
    std::cout << "Answer (part 2): " << part2.longest_path -(1+part1.path_length) << std::endl;

    return 0;
}

output_t explore_map(const point &start, computer_t comp){
    
    // neighbouring directions
    std::vector<dir> dirs = {{{0,1},1}, {{0,-1},2}, {{-1,0},3},{{1,0},4}};

    // map of points and content
    std::unordered_map<point,computer_t> grid;
    grid[start] = comp;

    // end state
    computer_t end_state;
    point end;

    // BFS
    std::vector<point> uniques = {start};
    std::list<point> frontier = {start};

    // longest path
    size_t longest_path = 0;

    while(!frontier.empty()){
        point current = frontier.front();
        frontier.pop_front();

        // make copy of current computer state
        computer_t curr_state = grid[current];

        // find neighbours
        for (const dir &d : dirs){
            // first check if dir is already explored, if yes skip.
            point next = current + d.p;
            if (std::find(uniques.begin(), uniques.end(), next)!=uniques.end()){ continue; }
            else { uniques.push_back(next); }

            // input direction into comp and check output
            curr_state.input.push_back(d.in);
            curr_state.run();

            int output = curr_state.output.back();

            // moved to new position
            if (output==1){
                frontier.push_back(next);
                grid[next] = curr_state;
            }
            // found finish
            else if (output==2){
                end_state = curr_state;
                end = next;
            }

            // check if longest path
            longest_path = std::max(curr_state.input.size(), longest_path);

            // if neither, hit wall. 
            // reset comp to previous position
            curr_state = grid[current];

            // // uncomment to display map for each step
            // std::this_thread::sleep_for(100ms);
            // display(build_map(grid));
            // std::cout << std::endl;
        }        
    }

    output_t output;
    output.path_length  = end_state.input.size();
    output.end          = end;
    output.longest_path = longest_path;
    output.end_state    = end_state;

    return output;
}

std::vector<std::vector<char>> build_map(const std::unordered_map<point,computer_t> &grid ){
    
    std::vector<std::vector<char>> map(70,std::vector<char>(70,'#'));

    for (const auto &pair : grid){
        map[pair.first.y+35][pair.first.x+35] = ' ';
    }

    return map;
}
