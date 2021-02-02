#include<iostream>
#include<vector>
#include<string>
#include<algorithm>
#include<cstdlib>
#include<cmath>
#include"../../Utils/utils.h"

struct vertex{
    int f,y,x;
};

// forward function declarations
int nieghbour_bugs(const int &x, const int &y, const std::vector<std::string> &grid);
void calc_frame(const std::vector<std::vector<std::string>> &grid, std::vector<std::vector<std::string>> &copy, const int &f);
void recursive_neighbours(const std::vector<std::vector<std::string>> &grid, std::vector<std::vector<std::string>> &copy, const vertex &curr, const std::vector<vertex> &neighbours);
void rotate(vertex &v, const int &ang);

int main(){

    // read input into vector of strings.
    std::vector<std::string> input = read_input("input", "");

    // unique grids
    std::vector<std::vector<std::string>> uniques;

    // grid with boundaries
    std::vector<std::string> grid(input.size()+2,std::string(input[0].size()+2,'.'));
    const int height = grid.size()-1;
    const int width  = grid[0].size()-1;

    // fill grid
    for (int y=1; y<height; y++){
        for (int x=1; x<width; x++){
            grid[y][x] = input[y-1][x-1];
        }
    }

    // grid copy
    std::vector<std::string> copy = grid;

    while (std::find(uniques.begin(),uniques.end(),grid)==uniques.end()){

        // add unique grid
        uniques.push_back(grid);

        // get next state
        for (int y=1; y<height; y++){
            for (int x=1; x<height; x++){
                
                int bugs   = nieghbour_bugs(x,y,grid);
                char &tile = grid[y][x]; 

                // bug dies unless only 1 neighbour
                if (tile=='#' && bugs!=1){ copy[y][x]='.'; }
                else if (tile=='.' && (bugs==1 || bugs==2)){ copy[y][x]='#'; }
            }
        }

        // update grid
        grid = copy;
    }

    // calculate biosensitivity
    long long bio = 0;
    for (int y=1; y<height; y++){
        for (int x=1; x<width; x++){
            if (grid[y][x]=='#'){ bio += std::pow(2,(x-1)+(y-1)*(width-1)); }
        }
    }

    std::cout << "Answer (part 1): " << bio << std::endl;

    // part 2
    // sim time
    const int time = 200;

    // vector of recursive frames and copy
    std::vector<std::vector<std::string>> frames(time*2+3,std::vector<std::string>(input.size(),std::string(input[0].size(),'.')));
    std::vector<std::vector<std::string>> frames_copy;

    // make middle frame input
    frames[time+1] = input;
    frames_copy  = frames;

    // 200 seconds
    int min_frame = time+1;
    int max_frame = time+1;
    for (int i=0; i<time; i++){
        
        // increase frame range
        min_frame--;
        max_frame++;

        // simulate only frames that change
        for (int f=min_frame; f<=max_frame; f++){
            calc_frame(frames,frames_copy,f);
        }

        // update frames
        frames = frames_copy;
    }

    // count all bugs
    int count = 0;
    for (size_t i=0; i<frames.size(); i++){
        for (size_t j=0; j<frames[0].size(); j++){
            for (size_t k=0; k<frames[0][0].size(); k++){
                if (frames[i][j][k]=='#'){ count++; }
            }
        }
    }

    std::cout << "Answer (part 2): " << count << std::endl;

    return 0;
}

int nieghbour_bugs(const int &x, const int &y, const std::vector<std::string> &grid){
    
    int count = 0;
    if (grid[y+1][  x]=='#'){ count++; }
    if (grid[y-1][  x]=='#'){ count++; }
    if (grid[  y][x+1]=='#'){ count++; }
    if (grid[  y][x-1]=='#'){ count++; }

    return count;
}

void calc_frame(const std::vector<std::vector<std::string>> &grid, std::vector<std::vector<std::string>> &copy, const int &f){

    // corner coords
    std::vector<vertex> coords = {{f,0,0},{f,0,1},{f,1,0},{f,1,1},{f,2,0},{f,2,1}};

    // neighbours (hard coded corner)
    std::vector<std::vector<vertex>> neighbours = 
        {   {{f-1,1,2},{f-1,2,1},{f  ,1,0},{f  ,0,1}},
            {{f-1,1,2},{f  ,0,0},{f  ,1,1},{f  ,0,2}},
            {{f  ,0,0},{f-1,2,1},{f  ,2,0},{f  ,1,1}},
            {{f  ,0,1},{f  ,1,0},{f  ,2,1},{f  ,1,2}},
            {{f  ,1,0},{f-1,2,1},{f  ,3,0},{f  ,2,1}},
            {{f  ,1,1},{f  ,2,0},{f  ,3,1},{f+1,0,0},{f+1,1,0},{f+1,2,0},{f+1,3,0},{f+1,4,0}}};

    // rotations
    std::vector<int> angles = {0,90,180,270};

    // rotate coors to do whole grid
    for (const int &ang : angles){

        // rotate coords
        for (vertex &v : coords){ rotate(v,ang); }

        // rotate neighbours
        for (std::vector<vertex> &line : neighbours){
            for (vertex &v : line){ rotate(v,ang); }
        }

        // update neighbour
        for (size_t i=0; i<coords.size(); i++){
            recursive_neighbours(grid,copy,coords[i],neighbours[i]);
        }
    }
}

void recursive_neighbours(const std::vector<std::vector<std::string>> &grid, std::vector<std::vector<std::string>> &copy, const vertex &curr, const std::vector<vertex> &neighbours){

    int bug_count = 0;
    for (const vertex &v : neighbours){
        if (grid[v.f][v.y][v.x]=='#'){ bug_count++; }
    }

    char &tile = copy[curr.f][curr.y][curr.x];
    if (tile=='#' && bug_count!=1){ tile='.'; }
    else if (tile=='.' && (bug_count==1 || bug_count==2)){ tile='#'; }
}

// rotate coordinate about the point 2,2
void rotate(vertex &v, const int &ang){
    int s,c;
    int px = 2, py = 2;

    switch(ang){
        case(0):
            s = 0;
            c = 1;
            break;
        case(90):
            s = 1;
            c = 0;
            break;
        case(180):
            s = 0;
            c = -1;
            break;
        case(270):
            s = -1;
            c = 0;
            break;
    }

    // translate back to origin
    v.x -= px;
    v.y -= py;

    // rotate point
    int xsave = v.x;
    v.x = v.x*c   - v.y*s;
    v.y = xsave*s + v.y*c;

    // translate back
    v.x += px;
    v.y += py;
}
