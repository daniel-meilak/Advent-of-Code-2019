#include<iostream>
#include<vector>
#include<string>
#include<algorithm>
#include<numeric>
#include<cstdlib>
#include<ranges>
#include"../../Utils/utils.h"

void new_stack(std::vector<int> &deck);
void cut(std::vector<int> &deck, const int &n);
void deal_increment(std::vector<int> &deck, const int &n);
void new_stack2(const __int128_t deck_size, __int128_t& a, __int128_t& b);
void cut2(const __int128_t deck_size, __int128_t& b, const __int128_t &n);
void deal_increment2(const __int128_t deck_size, __int128_t &a, __int128_t& b, const __int128_t &n);
__int128_t binpow(__int128_t a, __int128_t b, __int128_t m);

int main(){

    // read input into vector of vector of strings.
    std::vector<std::string> delimiters = {" ","deal","into","stack","with"};
    std::vector<std::vector<std::string>> input = read_input_2D("input_22", delimiters);

    const int size = 10007;

    // create deck
    std::vector<int> deck(size);
    std::iota(deck.begin(),deck.end(),0);

    // work through input
    for (const auto &line : input){
        
        if      (line[0]=="new"      ){ new_stack(deck); }
        else if (line[0]=="increment"){ deal_increment(deck,std::stoi(line[1])); }
        else if (line[0]=="cut"      ){ cut(deck, std::stoi(line[1])); }
    }

    // find card 2019
    auto it    = std::ranges::find(deck,2019);
    size_t pos = std::distance(deck.begin(),it); 

    // part 2
    __int128_t deck_size = 119315717514047;
    __int128_t repeat    = 101741582076661;
    __int128_t a=1, b=0;
    __int128_t n = 2020;

    // work through input
    for (const auto &line : input){
        
        if      (line[0]=="new"      ){ new_stack2(deck_size,a,b); }
        else if (line[0]=="increment"){ deal_increment2(deck_size,a,b,std::stoll(line[1])); }
        else if (line[0]=="cut"      ){ cut2(deck_size,b,std::stoll(line[1])); }
    }

    __int128_t r    = mod((b * binpow(1-a,deck_size-2,deck_size)),deck_size);
    __int128_t card = mod(((n-r)*binpow(a,repeat*(deck_size-2),deck_size)+r),deck_size);  

    std::cout << "Answer (part 1): " << pos  << std::endl;
    std::cout << "Answer (part 2): " << (long long)card << std::endl;

    return 0;
}

void new_stack(std::vector<int> &deck){
    std::ranges::reverse(deck); // c++20
}

void cut(std::vector<int> &deck, const int &n){
    if (n>0){ std::rotate(deck.begin(), deck.begin()+n, deck.end()); }
    else { std::rotate(deck.rbegin(), deck.rbegin()+(-n), deck.rend()); }
}

void deal_increment(std::vector<int> &deck, const int &n){

    const int size = deck.size();
    std::vector<int> output(size);

    for (int i=0; i<size; i++){
        output[mod(i*n,size)]=deck[i];
    }

    deck = output;
}

void new_stack2(const __int128_t deck_size, __int128_t& a, __int128_t& b){
    a = mod(-a, deck_size);
    b = mod(deck_size-1-b,deck_size);
}

void cut2(const __int128_t deck_size, __int128_t& b, const __int128_t &n){
    b = mod(b-n,deck_size);
}

void deal_increment2(const __int128_t deck_size, __int128_t &a, __int128_t& b, const __int128_t &n){
    a = mod(a*n,deck_size);
    b = mod(b*n,deck_size);
}

__int128_t binpow(__int128_t a, __int128_t b, __int128_t m){
    a %= m;
    __int128_t res = 1;
    while (b > 0){
        if (b & 1)
            res = res*a % m;
        a = a*a % m;
        b >>= 1;
    }
    return res;
}