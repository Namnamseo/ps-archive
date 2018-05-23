#include "Brunolib.h"
#include <bits/stdc++.h>
using namespace std;

static bool gen;

static bitset<60> key[150];

static void GEN(){
    if(gen) return;
    srand(12345);
    for(int i=0; i<60; ++i){
        for(int j=0; j<150; ++j){
            key[j][i] = rand()%2;
        }
    }
    gen=1;
}

long long Bruno( int N, int A[] ){
    GEN();
    bitset<60> ret;
    for(int i=0; i<150; ++i) if(A[i]){
        ret ^= key[i];
    }
    auto ans=0ll;
    for(int i=0; i<60; ++i){
        if(ret[i]) ans += (1ll << i);
    }
    return ans;
}
