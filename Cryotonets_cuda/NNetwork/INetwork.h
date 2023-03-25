#pragma once
#include "iDisposable.h"
class INetwork :
    public IDisposable
{
    INetwork Source() {};
    INetwork GetSource();
    int OutputDimension();
    void Prepare();

    /// <summary>
    /// prepares this layer and its sources
    /// </summary>
    void PrepareNetwork();
    /// <summary>
    /// The scale of the output of the network
    /// </summary>
    double GetOutputScale();

    /// <summary>
    /// The factory in which the output of this layer is encoded
    /// </summary>
    IFactory Factory{ get; set; }

    void DisposeNetwork();
};

