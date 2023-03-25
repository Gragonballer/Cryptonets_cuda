#pragma once
#include"IVector.h"
#include<vector>
#include"BigInteger.h"
#include<eigen/Eigen/Eigen>
enum EVectorFormat { dense, sparse };
using namespace std;
using namespace Eigen;
class IFactory
{
    /// <summary>
    /// generate a plaintext vector
    /// </summary>
    /// <param name="v">values to populate the vector with</param>
    /// <param name="format">type of vector to generate (sparse/dense)</param>
    /// <param name="scale">scale is the precision of the values. Each value is multiplied by scale beore rounded to an integer</param>
    /// <returns>a vector</returns>
    IVector GetPlainVector(vector<double> v, EVectorFormat format, double scale);
    /// <summary>
    /// generate a plaintext vector
    /// </summary>
    /// <param name="v">values to populate the vector with</param>
    /// <param name="format">type of vector to generate (sparse/dense)</param>
    /// <returns>a vector</returns>
    /// vector 代替 IEnumrable
    IVector GetPlainVector(vector<BigInteger> v, EVectorFormat format);
    /// <summary>
    /// generate an encrypted vector
    /// </summary>
    /// <param name="v">values to populate the vector with</param>
    /// <param name="format">type of vector to generate (sparse/dense)</param>
    /// <param name="scale">scale is the precision of the values. Each value is multiplied by scale beore rounded to an integer</param>
    /// <returns>a vector</returns>
    IVector GetEncryptedVector(vector<double> v, EVectorFormat format, double scale);
    /// <summary>
    /// generate an encrypted vector
    /// </summary>
    /// <param name="v">values to populate the vector with</param>
    /// <param name="format">type of vector to generate (sparse/dense)</param>
    /// <returns>a vector</returns>
    IVector GetEncryptedVector(vector<BigInteger> v, EVectorFormat format);
    /// <summary>
    /// Get an unbounded integer from string
    /// </summary>
    /// <param name="str">input string</param>
    /// <returns>unbounded integer</returns>
    BigInteger GetValueFromString(string str);
    /// <summary>
    /// Convert an unbounded integer to string
    /// </summary>
    /// <param name="value">unbounded integer</param>
    /// <returns>string</returns>
    string GetStringFromValue(BigInteger value);
    /// <summary>
    /// Deep copy of a vector
    /// </summary>
    /// <param name="v">The vector to copy</param>
    /// <returns>A new vector</returns>
    IVector CopyVector(IVector v);
    /// <summary>
    /// Load vector from a stream
    /// </summary>
    /// <param name="str">Stream to load from</param>
    /// <returns>The vector</returns>
    IVector LoadVector(StreamReader str);
    /// <summary>
    /// Generate a matrix with plaintext values
    /// </summary>
    /// <param name="m">The data to use to populate the matrix</param>
    /// <param name="format">Matrix format to use</param>
    /// <param name="scale">scale is the precision of the values. Each value is multiplied by scale beore rounded to an integer</param>
    /// <returns>The matrix</returns>
    /// 
    /// MatrixXd是eigen库中的函数，实例代码如下
    ///  Eigen::MatrixXd A(1,4);  // 定义一个2x2的矩阵A
   /* Eigen::MatrixXd B(4, 1);  // 定义一个2x2的矩阵B
    // 给矩阵A, B赋值
    A << 1.1, 2.2, 3.3, 4.4;
    B << 5.5,
        6.5,
        7.5,
        8;
    // 矩阵乘法
    Eigen::MatrixXd C = B * A;
    std::cout << "[B*A] = " << std::endl << C << std::endl;
    */
    /// 
    IMatrix GetPlainMatrix(MatrixXd m, EMatrixFormat format, double scale);
    /// <summary>
    /// Generate a matrix with encrypted values
    /// </summary>
    /// <param name="m">The data to use to populate the matrix</param>
    /// <param name="format">Matrix format to use</param>
    /// <param name="scale">scale is the precision of the values. Each value is multiplied by scale beore rounded to an integer</param>
    /// <returns>The matrix</returns>
    IMatrix GetEncryptedMatrix(Matrix m, EMatrixFormat format, double scale);
    /// <summary>
    /// Creates a matrix from a collection of vectors
    /// </summary>
    /// <param name="vectors"> the vectors that will form the rows/columns of the matrix</param>
    /// <param name="format"> specifies whether the matrix is column major or row major</param>
    /// <param name="env"> computational environment</param>
    /// <param name="CopyVectors"> by default the vectors are copied. However, if this variable is set to false thy are passed by reference and therefore should not be disposed.</param>
    /// <returns> a matrix</returns>
    IMatrix GetMatrix(IVector[] vectors, EMatrixFormat format, bool CopyVectors = true);
    /// <summary>
    /// Load matrix from stream
    /// </summary>
    /// <param name="str">Stream to load from</param>
    /// <returns>Loaded matrix</returns>
    IMatrix LoadMatrix(StreamReader str);
    /// <summary>
    /// Return a computational environment with which it is posible to operate on matrices and vectors
    /// </summary>
    /// <returns>The computational environment</returns>
    IComputationEnvironment AllocateComputationEnv();
    /// <summary>
    /// De-allocate a computational environment
    /// </summary>
    /// <param name="env">The computational environment to de-allocate</param>
    void FreeComputationEnv(IComputationEnvironment env);
    /// <summary>
    /// Save the factory to a stream
    /// </summary>
    /// <param name="stream">The stream to save to</param>
    /// <param name="withPrivateKeys">If set to true, the secret keys are saved, otherwise the factory is saved without secret keys</param>
    /// <returns>The stream</returns>
    Stream Save(Stream stream, bool withPrivateKeys = false);
    /// <summary>
    /// Save the factory to a file
    /// </summary>
    /// <param name="FileName">File name to save to</param>
    /// <param name="withPrivateKeys">If set to true, the secret keys are saved, otherwise the factory is saved without secret keys</param>
    void Save(string FileName, bool withPrivateKeys = false);
};

