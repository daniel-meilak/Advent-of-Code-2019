#include<iostream>
#include<vector>
#include<string>
#include<algorithm>
#include<cstdlib>
#include<utility>
#include<unordered_set>
#include"../../Utils/utils.h"

// sorting functions
bool sort_by_manhattan(const std::pair<int,int> &lhs, const std::pair<int,int> &rhs){
    return lhs.first < rhs.first;
}

bool sort_by_length(const std::pair<int,int> &lhs, const std::pair<int,int> &rhs){
    return lhs.second < rhs.second;
}

// position struct
struct point{
    int x,y;

    point(int x_, int y_): x(x_), y(y_){};
};

// point equality
bool operator==(const point &lhs, const point &rhs){
    return (lhs.x==rhs.x && lhs.y==rhs.y);
}

// hash for storing points in unordered_set
namespace std {
    template <> struct hash<point> {
        typedef point argument_type;
        typedef std::size_t result_type;
        std::size_t operator()(const point& id) const noexcept {
            return std::hash<int>()(id.x ^ (id.y << 4));
        }
    };
}


int main(){

    // read input into vector of vector of strings.
    std::vector<std::string> delimiters = {","};
    std::vector<std::vector<std::string>> input = read_input_2D("input", delimiters);

    // create two unordered maps of point keys and length values
    // key existence means wire exists on that pos
    std::vector<std::unordered_map<point,int>> wires(2);
    

    // for both wires, a positions x,y and current length at pos, l
    std::vector<int> x(2,0), y(2,0), l(2,0);    

    // wires are the same length, iterate together
    for (size_t i=0; i<input.size(); i++){
        for (size_t j=0; j<input[i].size(); j++){

            std::string &path = input[i][j];

            // distance
            int dist = std::stoi(path.substr(1));

            switch(path[0]){
                case('U'):{
                    for (int k=0; k<dist; k++){
                        y[i]++;
                        l[i]++;
                        wires[i][point(x[i],y[i])] = l[i];
                    }
                    break;
                }
                case('D'):{
                    for (int k=0; k<dist; k++){
                        y[i]--;
                        l[i]++;
                        wires[i][point(x[i],y[i])] = l[i];
                    }
                    break;
                }
                case('L'):{
                    for (int k=0; k<dist; k++){
                        x[i]--;
                        l[i]++;
                        wires[i][point(x[i],y[i])] = l[i];
                    }
                    break;
                }
                case('R'):{
                    for (int k=0; k<dist; k++){
                        x[i]++;
                        l[i]++;
                        wires[i][point(x[i],y[i])] = l[i];
                    }
                    break;
                }
            }
        }
    }

    // find intersections and store in vector of intersection dist and length
    std::vector<std::pair<int,int>> inter;
    for (const auto &pair : wires[0]){

        const int &x = pair.first.x;
        const int &y = pair.first.y;

        // if key exists in wires[1], lines intersect
        if ( wires[1].count(point(x,y)) ){
            inter.push_back( {manhattan(x,y), pair.second+wires[1][point(x,y)]} );
        }
    }

    // sort inter by manhattan dist
    std::sort(inter.begin(), inter.end(), sort_by_manhattan);
    int best_manhattan = inter[0].first;

    // sort inter by combigned length
    std::sort(inter.begin(), inter.end(), sort_by_length);
    int best_length = inter[0].second;

    std::cout << "Answer (part 1): " << best_manhattan << std::endl;
    std::cout << "Answer (part 2): " << best_length    << std::endl;

    return 0;
}