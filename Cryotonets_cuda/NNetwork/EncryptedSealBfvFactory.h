#pragma once
#include"IFactory.h"
class EncryptedSealBfvFactory : public IFactory
{
public:
    ConcurrentQueue<EncryptedSealBfvEnvironment> environmentQueue = new ConcurrentQueue<EncryptedSealBfvEnvironment>();
    EncryptedSealBfvEnvironment referenceEnvironment;
    const int DefaultDecompositionBitCount = 10;
    const int DefaultGaloisDecompositionBitCount = 20;

    public EncryptedSealBfvFactory()
    {
        ulong[] primes = new ulong[]{ 40961, 65537, 114689, 147457, 188417 };
        EncryptedSealBfvEnvironment eenv = new EncryptedSealBfvEnvironment(){ ParentFactory = this };
        eenv.GenerateEncryptionKeys(primes, 4096, DefaultDecompositionBitCount, DefaultGaloisDecompositionBitCount);
        referenceEnvironment = eenv;
    }

    public EncryptedSealBfvFactory(ulong[] primes, ulong n, int DecompositionBitCount = DefaultDecompositionBitCount, int GaloisDecompositionBitCount = DefaultGaloisDecompositionBitCount, int SmallModulusCount = -1)
    {
        EncryptedSealBfvEnvironment eenv = new EncryptedSealBfvEnvironment(){ ParentFactory = this };
        eenv.GenerateEncryptionKeys(primes, n, DecompositionBitCount, GaloisDecompositionBitCount, SmallModulusCount);
        referenceEnvironment = eenv;
    }

    public EncryptedSealBfvFactory(string fileName)
    {
        referenceEnvironment = new EncryptedSealBfvEnvironment(fileName)
        {
            ParentFactory = this
        };
    }

    public EncryptedSealBfvFactory(Stream stream)
    {
        referenceEnvironment = new EncryptedSealBfvEnvironment(stream)
        {
            ParentFactory = this
        };
    }
    public IVector CopyVector(IVector v)
    {
        return Utils.ProcessInEnv((env) = > new EncryptedSealBfvVector(v, env), this);
    }
    public IComputationEnvironment AllocateComputationEnv()
    {
        environmentQueue.TryDequeue(out EncryptedSealBfvEnvironment env);
        if (env == null)
            env = new EncryptedSealBfvEnvironment(referenceEnvironment);
        return env;
    }


    public void FreeComputationEnv(IComputationEnvironment env)
    {
        var lenv = env as EncryptedSealBfvEnvironment;
        environmentQueue.Enqueue(lenv);
    }

    public Stream Save(Stream stream, bool withPrivateKeys = false)
    {
        return referenceEnvironment.Save(stream, withPrivateKeys);
    }
    public void Save(string fileName, bool withPrivateKeys = false)
    {
        referenceEnvironment.Save(fileName, withPrivateKeys);

    }


    public IVector LoadVector(StreamReader str)
    {
        return Utils.ProcessInEnv(env = > EncryptedSealBfvVector.Read(str, env as EncryptedSealBfvEnvironment), this);
    }

    public IMatrix LoadMatrix(StreamReader str)
    {
        return Utils.ProcessInEnv(env = > EncryptedSealBfvMatrix.Read(str, env as EncryptedSealBfvEnvironment), this);
    }

    public IVector GetPlainVector(Vector<double> v, EVectorFormat format, double scale)
    {
        return Utils.ProcessInEnv(env = > new EncryptedSealBfvVector(v, env, scale, EncryptData: false, Format : format), this);
    }
    public IVector GetPlainVector(IEnumerable<BigInteger> v, EVectorFormat format)
    {
        return Utils.ProcessInEnv((env) = >
            new EncryptedSealBfvVector(v, env, EncryptData: false, Format : format), this);
    }

    public IVector GetEncryptedVector(Vector<double> v, EVectorFormat format, double scale)
    {
        return Utils.ProcessInEnv((env) = >
            new EncryptedSealBfvVector(v, env, scale, EncryptData: true, Format : format), this);
    }
    public IVector GetEncryptedVector(IEnumerable<BigInteger> v, EVectorFormat format)
    {
        return Utils.ProcessInEnv((env) = >
            new EncryptedSealBfvVector(v, env, EncryptData: true, Format : format), this);
    }

    public IMatrix GetPlainMatrix(Matrix<double> m, EMatrixFormat format, double scale)
    {
        IMatrix res = null;
        Utils.ProcessInEnv((env) = >
        {
            EncryptedSealBfvVector[] vecs = (format == EMatrixFormat.ColumnMajor) ?
                m.EnumerateColumns().Select(v = > new EncryptedSealBfvVector(v, env, scale, Format: EVectorFormat.dense, EncryptData : false)).ToArray()
                : m.EnumerateRows().Select(v = > new EncryptedSealBfvVector(v, env, scale, Format: EVectorFormat.dense, EncryptData : false)).ToArray();

            res = new EncryptedSealBfvMatrix(vecs, env){ Format = format };
            foreach(var v in vecs) v.Dispose();
        }, this);
        return res;
    }

    public IMatrix GetEncryptedMatrix(Matrix<double> m, EMatrixFormat format, double scale)
    {
        IMatrix res = null;
        Utils.ProcessInEnv((env) = >
        {
            EncryptedSealBfvVector[] vecs = null;
            if (format == EMatrixFormat.ColumnMajor)
            {
                vecs = new EncryptedSealBfvVector[m.ColumnCount];
                Utils.ParallelProcessInEnv(vecs.Length, env, (penv, taskIndex, k) = >
                {
                    vecs[k] = new EncryptedSealBfvVector(m.Column(k), penv, scale, Format: EVectorFormat.dense, EncryptData : true);
                });
            }
            else
            {
                vecs = new EncryptedSealBfvVector[m.RowCount];
                Utils.ParallelProcessInEnv(vecs.Length, env, (penv, taskIndex, k) = >
                {
                    vecs[k] = new EncryptedSealBfvVector(m.Row(k), penv, scale, Format: EVectorFormat.dense, EncryptData : true);
                });

            }
            res = new EncryptedSealBfvMatrix(vecs, env){ Format = format };
            foreach(var v in vecs) v.Dispose();
        }, this);
        return res;
    }

    public IMatrix GetMatrix(IVector[] vectors, EMatrixFormat format, bool CopyVectors = true)
    {
        IMatrix mat = null;
        Utils.ProcessInEnv((env) = >
        {
            mat = new EncryptedSealBfvMatrix(Array.ConvertAll(vectors, v = > (EncryptedSealBfvVector)v), env, CopyVectors: CopyVectors)
            {
                Format = format
            };
        }, this);
        return mat;
    }

    public BigInteger GetValueFromString(string str)
    {
        var f = str.Split(',').Select(x = > uint.Parse(x)).ToArray();
        BigInteger v = new BigInteger();
        for (int i = 0; i < f.Length; i++)
            v += referenceEnvironment.preComputedCoefficients[i] * f[i];
        v = v % referenceEnvironment.bigFactor;
        return v;
    }

    public string GetStringFromValue(BigInteger value)
    {
        return string.Join(",", this.referenceEnvironment.Environments.Select(e = > value % e.plainmodulusValue));

    }
};
