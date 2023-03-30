#pragma once
#include<string>
#define DEBUG   //该语句在测试以后要删除
/// <summary>
  /// This class is used to count the number of operations performed of each type.
  /// </summary>
class OperationsCount
{
public:
    static int Destructor, Encryption, Plain, Decryption, Multiplication, PlainMultiplication, Addition, Dispose;
    static int PlainAddition, Subtraction, PlainSubtraction, Rotation, AddMany, AddManyItemCount, Relinarization;
    static Dictionary<string, int> Totals = null;

    static OperationsCount()
    {
        AppDomain.CurrentDomain.ProcessExit += CurrentDomain_ProcessExit;
    }

    static void CurrentDomain_ProcessExit(object sender, EventArgs e)
    {
        PrintTotals();
    }
    /// <summary>
    /// report on an operation performed
    /// </summary>
    /// <param name="counter">type of operation performed</param>
    /// <param name="value">number of times the operation was performed</param>
    //[ConditionalAttribute("DEBUG")]
    #ifdef DEBUG
    static void Add(ref int counter, int value)
    {
        Interlocked.Add(ref counter, value);
    }
    #endif
    /// <summary>
    /// print the number of times each operation was performed
    /// </summary>
    //[ConditionalAttribute("DEBUG")]
    #ifdef DEBUG
    static void Print()
    {
        if (Totals == null) return;
        Type type = typeof(OperationsCount);
        FieldInfo[] fields = type.GetFields();

        Console.WriteLine("Operations:");
        foreach(var f in fields)
        {
            Console.WriteLine("\t{0}\t{1}", f.Name, (int)f.GetValue(f.Name));
        }
    }
    #endif
    /// <summary>
    /// reset operation counters
    /// </summary>
    //[ConditionalAttribute("DEBUG")]
    #ifdef DEBUG
    static void Reset()
    {
        Type type = typeof(OperationsCount);
        FieldInfo[] fields = type.GetFields();
        if (Totals == null)
            Totals = new Dictionary<string, int>();


        foreach(var f in fields)
        {
            if (!Totals.ContainsKey(f.Name))
                Totals[f.Name] = (int)f.GetValue(f.Name);
            else
                Totals[f.Name] += (int)f.GetValue(f.Name);
            f.SetValue(f.Name, 0);
        }
    }
    #endif
    /// <summary>
    /// print the number of operations performed since the begining of the execution
    /// (numbers are not effected by calls to Reset)
    /// </summary>
    //[ConditionalAttribute("DEBUG")]
    #ifdef DEBUG
    static void PrintTotals()
    {
        if (Totals == null) return;
        Type type = typeof(OperationsCount);
        FieldInfo[] fields = type.GetFields();

        Console.WriteLine("Operations (total):");
        foreach(var f in fields)
        {
            Console.WriteLine("\t{0}\t{1}", f.Name, (int)f.GetValue(f.Name) + Totals[f.Name]);
        }
    }
    #endif

}