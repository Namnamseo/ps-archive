#include "grader.h"
#include "decoder.h"
#include <cstdio>
#include <vector>

inline int read_int(){
    int ret=0; for(int i=0;i<10;++i) ret=((ret<<1)|(decode_bit())); return ret;
}

static int table[36][1000];
static int parent[1000];

static int conv[3];

inline int read_smallint(){
    if(decode_bit()==0) return 0;
    else if(decode_bit()==0) return 1;
    else return 2;
}

inline int read_pm(){
    int tmp=read_smallint();
    if(conv[0]==tmp) return -1;
    else if(conv[1]==tmp) return 0;
    else return 1;
}

static std::vector<int> edge[1000];
static int queue[1000];

void topo(){
    int head=0, tail=0;
    queue[head++]=0;
    while(tail<head){
        int me=queue[tail++];
        int sz = edge[me].size();
        for(int i=0;i<sz;++i){
            int that=edge[me][i];
            queue[head++]=that;
        }
    }
}

void decode(int n, int h) {
    int i,j;
    for(i=1;i<h;++i) table[i][0]=read_int(); // zeroth column

    for(i=1;i<n;++i) parent[i]=read_int(), edge[parent[i]].push_back(i); // parent
    topo();

    for(i=0;i<3;++i) conv[i]=read_smallint();
    
    for(i=1;i<n;++i) for(j=0;j<h;++j){
        if(parent[i]==0 && j==0){
            table[j][i]=read_int();
            //printf("Getting %d,%d is big ; %d\n",j,i,table[j][i]);
        } else if(i!=j) table[j][i]=read_pm();
    }
    
    for(i=1;i<n;++i){
        int me=queue[i];
        for(j=0;j<h;++j){
            if(me==j || (parent[me]==0 && j==0)) continue;
            table[j][me]+=table[j][parent[me]];
        }
    }
    
    for(i=0;i<h;++i) for(j=0;j<n;++j) hops(i,j,table[i][j]);
}
