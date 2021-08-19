#include "encoder.h"
#include "encoderlib.h"
#include <vector>
using namespace std;

typedef unsigned long long ll;
static int each_cnt[256];

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
    ll index = 0;
    for(int i=0; i<count; ++i){
        index *= 256;
        index += st[i];
    }
    int ones = chR - chL;
    int left_count = 5*count + ones;
    vector<int> v;
    for(;left_count;){
        if(index >= combi[left_count-1][ones] && !big[left_count-1][ones]){
            index -= combi[left_count-1][ones];
            --ones;
            v.push_back(1);
            left_count -= 1;
        } else {
            v.push_back(0);
            left_count -= 1;
        }
    }
    auto it=v.begin();
    for(int i=chL; it!=v.end(); ++it){
        if((*it) == 0){
            ++each_cnt[i];
        } else {
            ++i;
        }
    }
}

int min(int a,int b){ return a>b?b:a; }

void encode(int N, int A[])
{
    if(!combi[0][0]) bC();
    for(int i=0; i<256; ++i) each_cnt[i]=0;
    for(int i=0; i<N; i += 8){
        procChunk(A+i, min(N-i, 8), i*4, i*4+31);
    }
    for(int i=0; i<256; ++i){
        int t=each_cnt[i];
        for(;t--;){
            send(i);
        }
    }
}
