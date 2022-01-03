#!/bin/bash

# script for making new day folder and including files

mkdir day_${1}

echo "#include<iostream>
#include<vector>
#include<string>
#include<algorithm>
#include<cstdlib>
#include\"../../Utils/utils.h\"

int main(){

    // // read input into vector of strings.
    // std::vector<std::string> delimiters = {};
    // std::vector<std::string> input = read_input(\"input\", delimiters);

    // // read input into vector of vector of strings.
    // std::vector<std::string> delimiters = {};
    // std::vector<std::vector<std::string>> input = read_input_2D(\"input\", delimiters);

    std::cout << \"Answer (part 1): \" << std::endl;
    std::cout << \"Answer (part 2): \" << std::endl;

    return 0;
}" >> day_${1}/day_${1}.cpp

mkdir day_${1}/test

echo "#include<iostream>
#include<vector>
#include<string>
#include<algorithm>
#include<cstdlib>
#include\"../../../Utils/utils.h\"

int main(){

    return 0;
}" >> day_${1}/test/test.cpp

echo "## Day ${1}" >> day_${1}/README.md

