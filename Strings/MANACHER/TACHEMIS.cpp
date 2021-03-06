#include <cstdio>
#include <iostream>
#include <algorithm>
#include <vector>
#include <queue>
#include <stack>
#include <set>
#include <map>
#include <cstring>
#include <cstdlib>
#include <cmath>
#include <string>
#include <memory.h>
#include <sstream>
#include <complex>
#include <cassert>

#define FOR(i,a,b) for (int i = (a), _b = (b); i <= _b; i++)

#define PB push_back
#define MP make_pair


using namespace std;

char s[122222];
int n, m;
pair <char, int> a[122222];
int range[122222];
int sum[122222];

long long call() {
    //manachar algorithm
    int center = 1;
    range[1] = 1;

    a[0] = MP('#', 0);
    a[m + 1] = MP('@', 0);

    FOR (i, 2, m) {
        range[i] = 1;
        if (center + range[center] - 1 >= i) {
            range[i] = range[center * 2 - i];
            if (i + range[i] < center + range[center]) continue;
            else range[i] = center + range[center] - i;
        }

        while (a[i - range[i]] == a[i + range[i]]) range[i]++;
        center = i;
    }
    //end of manachar algorithm

    long long res = 0;
    sum[0] = 0;
    FOR (i, 1, m)
        sum[i] = a[i].second + sum[i - 1];


    FOR (i, 1, m) {
        //counting the palindrom that contain only one kind of character
        res += (long long) (a[i].second + 1) * (a[i].second) / 2;


        //if range[i] > 1, we add to the result the number of palindroms with center at i.
        //we have to subtract (a[i].second + 1)/2 palindroms which are already couted in the previous step.
        if (range[i] > 1) {
            res -= (a[i].second + 1)/2;
            int u = i - range[i] + 1, v = i + range[i] - 1;
            res += (sum[v] - sum[u - 1] + 1)/2;
            if (a[u - 1].first == a[v + 1].first) res += min(a[u - 1].second, a[v + 1].second);
        }
        else
        if (a[i - 1].first == a[i + 1].first) res += min(a[i-1].second, a[i + 1].second);
    }

    return res;
}

int main() {
    int ntest;
    scanf("%d\n", &ntest);

    int sum = 0;
    while (ntest --) {
        cin >> m;
        FOR (i, 1, m)
            cin >> a[i].first >> a[i].second;

        cout <<call() << endl;
    }

    return 0;
}