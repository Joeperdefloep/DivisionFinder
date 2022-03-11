#include <iostream>
#include <vector>
#include <set>
#include <algorithm>
#include <math.h>

namespace DivisionFinder{
/****
generate a vector of non-prime factors of total. these should be in the cycle.
****/

std::set<int> prime_factors(int n){
    std::set<int> pfact;
    while(n%2==0){pfact.insert(2);n=n/2;}
    for (int i = 3; i <= n; i = i+2){
        while (n%i == 0){
            pfact.insert(i);
            n = n/i;
        }
    }
    return pfact;
}

std::set<int> non_prime_factors(int n){
    std::set<int> pfact = prime_factors(n);
    std::set<int> nfact;
    for (int i=1;i<= n; i++){
        if(std::all_of(pfact.begin(),pfact.end(),[i](int p){return i%p!=0;})){
            nfact.insert(i);
            nfact.insert(n-i);
        }
    }
    return nfact;
}

/*****
Find all cycles for a given total. Will not get equivalent values: for example 1/5 and 4/5 are equivalent
******/
std::vector<std::vector<int>> find_cycles(int total){
    std::vector<std::vector<int>> cycles;
    std::set<int> to_check = non_prime_factors(total);
    
    for(auto p:to_check){std::cout<<p<<", ";}
    int current = 1;

    while (!to_check.empty()){
        std::vector<int> cycle = {current};
        while (to_check.erase(current) && to_check.erase(total-current)){
            current = (current % 2 == 0) ? current/2 : (total+current)/2;
            cycle.push_back(current);
        }
        cycles.push_back(cycle);
        current = *to_check.begin();
    }
    std::cout << "Found " << cycles.size() << "cycles!\n";
    for(auto c:cycles){
        std::cout<< "Cycle of length " << c.size() << ": ";
        for(auto i:c){std::cout<<i<<" ,";}
        std::cout<<std::endl;
    }
    return cycles;
}

std::vector<int> find_cycle(int start, int total){
    std::cout<<"finding cycle from: "<<start<<"/"<<total;
    int current = (start%2==0)?start/2:(total+start)/2;
    std::vector<int> cycle = {start};
    while (current!=start){
        cycle.push_back(current);
        std::cout<<", "<<current<<"/"<<total;
        // std::cout<<"current: "<<current<<", start:"<<start<<std::endl;
        current = (current%2==0)?current/2:(total+current)/2;
    }
    std::cout<<std::endl;
    return cycle;
}

std::pair<int,int> find_fold(std::vector<int> cycle, std::set<int> to_fold){
    std::cout<<" running find_fold with to_fold: ";
    for(auto k: to_fold){std::cout<<k<<", ";}
    for(size_t i=0;i<cycle.size();i++){
        for(size_t j=0;j<i;j++){
            if((cycle[i]+cycle[j])%2==0 && cycle[i]!=cycle[j]){
                std::cout<<"trying fold "<<cycle[i]<<" to "<<cycle[j]<<": "<<(cycle[i]+cycle[j])/2<<std::endl;
                if(to_fold.find((cycle[i]+cycle[j])/2) != to_fold.end()){
                    std::cout<<"found fold!: ("<<cycle[i]<<", "<<cycle[j]<<")";
                    return std::pair<int,int>(cycle[i],cycle[j]);
                }
            } else {
                std::cout<<"could not fold"<<cycle[i]<<" onto "<<cycle[j]<<std::endl;
            }
        }
    }
    //Should not reach here: that means there is no possible fold
    std::cout<< "big oops!, this should not happen!";
    for(auto i:cycle){std::cerr<<i<<", ";}
    throw;
}
} //namespace