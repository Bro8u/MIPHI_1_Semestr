#include "tasks.h"

#include <cmath>

int NOuter::NInner::DoSomething(int lhs, int rhs) {
	return (lhs + rhs);
}

int NOuter::DoSomething(int lhs, int rhs) {
	return (lhs - rhs);
}

int NOverload::ProcessTwoArgs(int lhs, int rhs) {
	return (lhs + rhs);
}

char NOverload::ProcessTwoArgs(char lhs, char rhs) {
	return fmax(lhs, rhs);
}

int NOverload::ProcessTwoArgs(int lhs, char rhs) {
	return lhs - rhs;
}

unsigned int NOverflow::WithOverflow(int lhs, int rhs) {
	return ((unsigned int) lhs + (unsigned int) rhs);
}

uint64_t NOverflow::WithOverflow(int64_t lhs, int64_t rhs) {
	return uint64_t(lhs) - uint64_t(rhs);
}

int NLoop::SumInRange(const int lhs, const int rhs) {
	return int64_t(rhs) * int64_t(rhs - 1) / 2 - int64_t(lhs - 1) * int64_t(lhs) / 2;
}

int NLoop::CountFixedBitsInRange(const int from, const int to, const int bitsCnt) {
	int ans = 0;
	for (int i = from; i <= to; ++i) {
		int n = i, count = 0;
		while (n) {
	        count += n & 1;
	        n >>= 1;
	    }
	    if (count == bitsCnt) {
	    	++ans;
	    }
     
	}
	return ans;
}

double NMath::ComputeMathFormula(const double arg) {
	return fabs( (sin(arg) / 2 + cos(arg)) * (sin(arg) / 2 + cos(arg)) + tan(arg) * atan(arg) );
}

bool NMath::IsPositive(int arg) {
	return (arg > 0);
}

int NRecursion::CalculateFibonacci(const int arg) {
	if (arg == 1 || arg == 2){
		return 1;
	}
	int arg1 = arg - 1, arg2 = arg - 2;
	return NRecursion::CalculateFibonacci(arg1) + NRecursion::CalculateFibonacci(arg2);
}
