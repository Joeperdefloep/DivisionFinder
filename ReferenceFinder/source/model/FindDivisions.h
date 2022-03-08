#include <iostream>
#include <vector>
#include <set>
#include <algorithm>
#include <math.h>
/****
generate a vector of non-prime factors of total. these should be in the cycle.
****/

std::set<int> prime_factors(int n){
    std::set<int> pfact;
    while(n%2==0){pfact.insert(2);n=n/2;std::cout<<"div\n";}
    for (int i = 3; i <= n; i = i+2){
        while (n%i == 0){
            pfact.insert(i);
            n = n/i;
        }
        std::cout<<n%i;
   }
   return pfact;
}

std::set<int> non_prime_factors(int n){
    std::set<int> pfact = prime_factors(n);
   std::set<int> nfact;
   for (int i=1;i<= n; i++){
       std::cout<<i;
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
            std::cout<<current;
        }
        cycles.push_back(cycle);
        current = *to_check.begin();
        // for(auto p:to_check){std::cout<<p<<", ";}
    }
    return cycles;
}