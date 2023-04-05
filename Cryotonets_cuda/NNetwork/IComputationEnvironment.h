#include<iostream>
#include"IFactory.h"
class IComputationEnvironment
{
    IFactory* parentFactory;
    IFactory* getParentFactory(IFactory param) { return parentFactory; };

    /// <summary>
    /// the prime factors used as plaintext modulii
    /// </summary>
    vector<unsigned long long> primes;
    vector<unsigned long long> getPrims() { return primes; }

};
