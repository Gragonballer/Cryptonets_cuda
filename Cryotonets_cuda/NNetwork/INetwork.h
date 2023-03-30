#pragma once
#include "iDisposable.h"
#include"IMatrix.h"
#include"IFactory.h"
class INetwork :
    public IDisposable
{
    public:
    /// <summary>
    /// applies the layer to the vector v
    /// </summary>
    /// <param name="v">the vector of number to apply the layer to</param>
    /// <returns>the results of applying the layer to v</returns>
    virtual IMatrix Apply(IMatrix v) = 0;

    /// <summary>
    /// calls the input layer and applies this layer to the output of the input layer
    /// </summary>
    /// <returns>the results of applying the layer to the output of the input layer</returns>
    virtual IMatrix GetNext() = 0;

    /// <summary>
    /// the dimension of the output of this layer
    /// </summary>
    /// <returns>the dimension</returns>
    virtual int OutputDimension() = 0;

    /// <summary>
    /// returns the parent (input) of this layer
    /// </summary>
    /// <returns> the parent (input) of this layer</returns>

    //INetwork Source() {};
    //INetwork GetSource();
    virtual int OutputDimension()=0;
    virtual void Prepare()=0;

    /// <summary>
    /// prepares this layer and its sources
    /// </summary>
    virtual void PrepareNetwork() = 0;
    /// <summary>
    /// The scale of the output of the network
    /// </summary>
    virtual double GetOutputScale() = 0;

    /// <summary>
    /// The factory in which the output of this layer is encoded
    /// </summary>
    IFactory factory;
    IFactory getFactory() { return factory; }
    void setFactory(IFactory param) { factory = param; }

    virtual void DisposeNetwork() = 0;
};

