#pragma once
#include "IDisposable.h"
class IMatrix :
    public IDisposable
{
public:
    unsigned long long rowCount;
    virtual IVector GetColumn(int columnNumber);
    unsigned long long columnCount;
    virtual IVector GetRow(int rowNumber);
};

