//
//  main.cpp
//  goldbach
//
//  Created by Magnus Hall on 07/12/2018.
//  Copyright © 2018 Magnus Hall. All rights reserved.
//

#include <iostream>
#include <sstream>
#include <string>
#include <math.h>
#include <vector>


using namespace std;

bool IsValid(string const& test);

vector<int> PrimeList(int upper_limit);

vector<pair<int,int>> FindSum(vector<int> const& primes,int number);



int main(int argc, const char * argv[]) {
    string input;
    cout<<"Type in any real positive even integer > 2 \n";
    cin>>input;
    while(!IsValid(input)){
        cout<<"invalid input, please give a valid integer \n";
        cin>>input;
    }
    double numInput = atof(input.c_str());
    
    int intInput(numInput);

    vector<int> primes = PrimeList(intInput);
    
    vector<pair<int,int>> sums = FindSum(primes,intInput);
    
    for(pair<int,int> s:sums){
        cout<<s.first<<" + "<<s.second<<" = "<<intInput<<endl;
    }
    
    
    
    return 0;
}



bool IsValid(string const& test){
    char* d;
    double converted = strtod(test.c_str(),&d);
    // strtod takes all the numerical bits up to the first non-numerical character and makes them a double. It then points d towards the first non-numerical character.
    // The if statement will register true if d is actually pointing to something (ie. there are more than just numbers in 'test').
    if(*d){
        return false;
    }
    // check that number is an int and not a double
    else{
        double intpart;
        // modf returns the non-integer part of a double it's passed, putting the int part into intpart
        converted = modf(converted,&intpart);
        
        // if statement checks that the fraction portion of the input is 0,
        // that the input is >2
        // and that it is positive
        
        if(converted==0 && intpart>2 && int(intpart)%2==0){
            return true;
        }
        else{return false;}
    }
}


vector<int> PrimeList(int upper_limit){
    //initialise with first few primes (for purpose of the algorithm)
    vector<int> primes={2,3,5};
    int j=1;
    // step through in steps of 2 since no even numbers after 2 (saves a lot of time for big upper limits
    for(int i=7;i<upper_limit;i+=2){
        
        bool isPrime=true;
        
        // there will always be at least one prime factor of i which is < sqrt(i) (if it exists)
        while(primes[j+1]<=pow(i,0.5)){
            j+=1;
        }
        // test all prime factors up to the square root of i
        for(int p=0;p<=j;p++){
            if(i%primes[p]==0){
                isPrime=false;
                break;
            }
        }
        if(isPrime){
            primes.push_back(i);
        }
    }
    return primes;
}

vector<pair<int,int>> FindSum(vector<int> const& primes,int number){
    //set a counter for the start of list of primes
    int i=0;
    //set a counter for end of list of primes
    int j=primes.size()-1;
    
    vector<pair<int,int>> sums;
    while(i<j){

        // if the sum of the lower prime plus the higher prime is > number, decrease the value of the higher prime
        if(primes[i]+primes[j]>number){
            j--;
        }
        // if the sum of the lower prime plus the higher prime is < number, increase the value of the lower prime
        else if(primes[i]+primes[j]<number){
            i++;
        }
        else{
            pair<int,int> combo = {primes[i],primes[j]};
            sums.push_back(combo);
            i++;
        }
    }
    
    
    return sums;
}
