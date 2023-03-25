#pragma once
#include"BigInteger.h"
template <typename T>

class IEnumerable : vector<BigInteger>
{
	unsigned long long current = 0;
	unsigned long long GetCurrent() {
		return current;
	}

	bool MoveNext() {
		current++;
		//if(current<this->size())
		//	return true
		return false
	}
};

