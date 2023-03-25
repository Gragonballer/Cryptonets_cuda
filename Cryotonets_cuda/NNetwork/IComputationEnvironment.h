#include<iostream>
#include"IFactory.h"
class IComputationEnvironment
{
    IFactory parentFactory;
    IFactory ParentFactory(IFactory param) { param.get(); };

        /// <summary>
        /// the prime factors used as plaintext modulii
        /// </summary>
    unsigned long int [] Primes{ get; }
}
