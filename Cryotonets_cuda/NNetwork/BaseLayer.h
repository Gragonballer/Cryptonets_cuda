#pragma once
#include "INetwork.h"
#include"IFactory.h"
#include"OperationsCount.h"
#include<ctime>
#include<iostream>
using namespace std;
class BaseLayer :
    public INetwork
{
public:
    bool layerPrepared = false;
    INetwork* source;
    INetwork* getSource(){ return source;};
    INetwork* setSource(INetwork* param){source = param;}
    /*构造函数*/
    BaseLayer(INetwork* obj) : source(obj) {};
    /*原本是空值，在这里没有赋值*/
    IFactory _factory;
    //IFactory Factory{ get { return _factory ? ? Source.Factory; } set { _factory = value; } }
    IFactory getFactory() { return _factory; }
    void setFactory(IFactory param) { _factory = param; }
    IMatrix Apply(IMatrix m);

    //public bool Verbose{ get; set; } = false;
    bool verbose = false;
    bool getVerbose() { return verbose; }
    void setVerbose(bool param) {
        verbose = param;
    }
//#if DEBUG
    //public static string Trace{ get; set; }
//#endif
       IMatrix GetNext()
    {
        if (!layerPrepared) Prepare();
            IMatrix m = source->GetNext();
/*#if DEBUG
        Trace = Environment.StackTrace;
#endif*/
        if (verbose)
        {
            //OperationsCount.Reset();
            OperationsCount OC;
            OC.Reset();
            time_t start = time(0);
            IMatrix res = Apply(m);
            time_t end = time(0);
            //typeif(this).name()返回名称
            cout << "Layer " << typeid(this).name() << " computed in " << (end - start) << " seconds (" << ctime(&start)
                << " -- " << ctime(&start) << ") layer width ( " << m.rowCount << "," << m.columnCount << ")" << endl;
            //Console.WriteLine("Layer {0} computed in {1} seconds ({2} -- {3}) layer width ({4},{5})", this.GetType().Name, (end - start).TotalSeconds, start.ToString("hh:mm:ss.fff"), end.ToString("hh:mm:ss.fff"), m.RowCount, m.ColumnCount);
            /*CryptooTracker类暂未实现*/
            //CryptoTracker.TestBudget(res.GetColumn(0), getFactory());

            OC.Print();
            /*重载暂未实现*/
            if (res != m) m.Dispose();
            return res;
        }
        else
        {
            IMatrix res = Apply(m);
            if (res != m) m.Dispose();
            return res;
        }
    }
    double GetOutputScale()
    {
        return source->GetOutputScale();
    }

    INetwork* GetSource()
    {
        return source;
    }

    int OutputDimension()
    {
        return source->OutputDimension();
    }

    void Prepare()
    {
    }

     void PrepareNetwork()
    {
        if (source != NULL) source->PrepareNetwork();
        if (verbose)
        {
            OperationsCount OC;
            OC.Reset();
            time_t start = time(0);
            Prepare();
            layerPrepared = true;
            time_t end = time(0);
            cout << "Prepare "<< typeid(this).name() <<" computed in "<< (end - start)<<" seconds ("<< ctime(&start) <<" -- "<< ctime(&start) <<")" << endl; 
            OC.Print();
        }
        else
        {
            Prepare();
            layerPrepared = true;
        }

    }

    void DisposeNetwork()
    {
        if (source != NULL)
            source->DisposeNetwork();
        Dispose();
    }
    virtual void Dispose()
    { }
protected:
    void ProcessInEnv(Action<IComputationEnvironment> lambda) = > Utils.ProcessInEnv(lambda, Factory);
    IVector ProcessInEnv(Func<IComputationEnvironment, IVector> lambda) = > Utils.ProcessInEnv(lambda, Factory);
    IMatrix ProcessInEnv(Func<IComputationEnvironment, IMatrix> lambda) = > Utils.ProcessInEnv(lambda, Factory);
    void ParallelProcessInEnv(int count, Action<IComputationEnvironment, int, int> lambda) = > Utils.ParallelProcessInEnv(count, lambda, Factory);
    void ParallelProcessInEnv(int count, IComputationEnvironment masterEnv, Action<IComputationEnvironment, int, int> lambda) = > Utils.ParallelProcessInEnv(count, masterEnv, Factory, lambda);

}
};

