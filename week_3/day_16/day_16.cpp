#include<iostream>
#include<vector>
#include<string>
#include<algorithm>
#include<cstdlib>
#include"../../Utils/utils.h"

std::string fft(const std::string &input);
void fft_fast(std::string &input);

int main(){

    // read input into vector of strings.
    std::string input = read_line("input", {});

    // number of fft iter
    int iter = 100;

    // part 1 ,perform 100 fft iter on input string
    std::string part1 = input;
    for (int i=0; i<iter; i++){
        part1 = fft(part1);
    }

    // part 2 prep, construct input string
    std::string part2;
    int repeat = 10000;
    for (int i=0; i<repeat; i++){
        part2 += input;
    }

    // get offset and substring for part 2
    int offset = std::stoi(part2.substr(0,7));
    part2 = part2.substr(offset);

    fft_fast(part2);

    std::cout << "Answer (part 1): " << part1.substr(0,8) << std::endl;
    std::cout << "Answer (part 2): " << part2.substr(0,8) << std::endl;

    return 0;
}

std::string fft(const std::string &input){

    std::vector<int> pattern = {0,1,0,-1};
    auto it = pattern.begin();

    const int size = input.size();
    std::string output;

    // calculate each element of output
    for (int i=0; i<size; i++){
        
        int sum = 0;
        if (i==0){ advance_cyclic(it,1,pattern); }
        for (int j=0; j<size; j++){

           sum += (input[j]-'0')*(*it);
           if ( (j+2)%(i+1) == 0 ){ advance_cyclic(it,1,pattern); }
        }

        output.push_back(std::to_string(sum).back());
        it = pattern.begin();
    }

    return output;
}

// apologies if you find the func name unpleasant
void fft_fast(std::string &input){
    
    // shortcut algorithm that takes advantage of position in input
    const int size = input.size();
    const int iter = 100;
    
    // still do 100 fft iter
    for (int i=0; i<iter; i++){

        // output holds sum for current char in next iter
        std::string output;
        int total = 0;

        // for each char in input
        for (int j=0; j<size; j++){

            // special rule for first character
            if (j==0){
                total = 0;
                for (const char &c : input){
                    total += c-'0';
                }
            }
            else {
                total -= input[j-1]-'0';
            }

            output.push_back(std::to_string(total).back());
        }

        // save latest result in part2 string
        input = output;
    }
}