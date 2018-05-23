#include <bits/stdc++.h>
#include "Annalib.h"
using namespace std;

static bool gen;

static bitset<150> key_orig[60];
static bitset<150> key[60];

static void GEN(){
    if(gen) return;
    srand(12345);
    for(int i=0; i<60; ++i){
        for(int j=0; j<150; ++j){
            key_orig[i][j] = rand()%2;
        }
    }
    gen=1;
}

void Anna(int N, long long X, int K, int P[]){
    GEN();
    
    int bit[60];
    for(int i=0; i<60; ++i) bit[i] = (1&(X >> i));
    
    for(int i=0; i<60; ++i){
        key[i]=key_orig[i];
        for(int j=0; j<K; ++j) key[i][P[j]]=0;
    }
    int row_ind = 0;
    int key_row[60];
    for(int j=0; j<150 && row_ind<60; ++j){
        bool has_key = 1;
        if(!key[row_ind][j]){
            has_key = 0;
            for(int i=row_ind+1; i<60; ++i) if(key[i][j]){
                {
                    auto tmp=key[row_ind];
                    key[row_ind]=key[i];
                    key[i]=tmp;
                }
                swap(bit[row_ind], bit[i]);
                has_key=1; break;
            }
        }
        if(!has_key) continue;
        for(int i=row_ind+1; i<60; ++i) if(key[i][j]){
            bit[i] ^= bit[row_ind];
            key[i] ^= key[row_ind];
        }
        key_row[row_ind]=j;
        ++row_ind;
    }
    if(row_ind != 60){
        for(int i=0; i<150; ++i) Set(i, 0);
        return;
    }
    bitset<150> ans;
    for(int i=59; 0<=i; --i) if(bit[i]){
        int col = key_row[i];
        for(int j=0; j<60; ++j){
            bit[j] ^= key[j][col];
        }
        ans[col]=1;
    }
    for(int i=0; i<150; ++i) Set(i, ans[i]);
}
