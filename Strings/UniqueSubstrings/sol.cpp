// Author: thecodekaiser
#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
#define MXLVL 32
#define MXLEN 100005

struct tuple
{
	int a[2];
	int original;
} L[MXLEN];

int sortIndex[MXLVL][MXLEN];

int comp(tuple A, tuple B)
{
	return (A.a[0] == B.a[0]) ? ((A.a[1] < B.a[1]) ? 1 : 0) : ((A.a[0] < B.a[0]) ? 1 : 0);
} 
