#include "decoder.h"
#include "decoderlib.h"
#include <vector>
using namespace std;

typedef unsigned long long ll;
static int cnt_each[256];

static ll combi[72][72];
static bool big[72][72];

static void bC(){
    combi[0][0]=1;
    for(int i=1; i<=71; ++i){
        combi[i][0]=combi[i][i]=1;
        for(int j=1; j<i; ++j){
            combi[i][j]=combi[i-1][j-1]+combi[i-1][j];
            if(i==68){
                if(31<=j && j<=37) big[i][j]=true;
            }
            if(i==69){
                if(29<=j && j<=40) big[i][j]=true;
            }
            if(i==70){
                if(28<=j && j<=42) big[i][j]=true;
            }
            if(i==71){
                if(27<=j && j<=44) big[i][j]=true;
            }
        }
    }
}

static void procChunk(int *st, int count,int chL,int chR){
    vector<int> v;
    for(int i=chL; i<=chR; ++i){
        for(int j=0; j<cnt_each[i]; ++j) v.push_back(0);
        if(i<chR) v.push_back(1);
    }
    ll index = 0;
    int ones = chR-chL;
    for(int i=0; i<v.size(); ++i){
        if(v[i] == 1){
            index += combi[((int)v.size())-1-i][ones];
            --ones;
        }
    }
    for(int i=0; i<count; ++i){
        st[count-1-i] = index%256;
        index /= 256;
    }
}

static int min(int a,int b){ return a>b?b:a; }

void decode(int N, int L, int X[])
{
    if(!combi[0][0]) bC();
    for(int i=0; i<256; ++i) cnt_each[i] = 0;

    for(int i=0; i<L; ++i) ++cnt_each[X[i]];

    int rets[N];
    for(int i=0; i<N; ++i) rets[i]=0;

    for(int i=0; i<N; i += 8){
        procChunk(rets+i, min(N-i, 8), i*4, i*4+31);
    }
    for(int i=0; i<N; ++i) output(rets[i]);
}
