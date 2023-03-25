#pragma once
#include<stdio.h>

class Utils
{
    void ProcessInEnv(Action<IComputationEnvironment> lambda, IFactory factory)
    {
        int env = factory.AllocateComputationEnv();
        lambda(env);
        factory.FreeComputationEnv(env);
    }
};

