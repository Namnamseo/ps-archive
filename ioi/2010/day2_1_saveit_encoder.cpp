#include "grader.h"
#include "encoder.h"
#include <vector>
#include <algorithm>

using namespace std;

typedef pair<int,int> pp;

static vector<int> e[1000];

static int vis[1000];
static int nowtime;
static int table[36][1000];
static int queue[1000];
static int parent[1000];

static int conv[3];

void input(int&ne, int*&v1, int*&v2){
    int a,b;
    for(;ne--;){
        a=v1[ne]; b=v2[ne];
        e[a].push_back(b);
        e[b].push_back(a);
    }
}

void bfs(int s) {
    ++nowtime; vis[s]=nowtime;
    queue[0]=s;
    parent[0]=-1;
    int head=1, tail=0;
    int i,sz,nxt,me;
    while(tail<head){
        me=queue[tail++];
        sz=e[me].size();
        for(i=0;i<sz;++i){
            nxt=e[me][i];
            if(vis[nxt]!=nowtime){
                vis[nxt]=nowtime;
                if(s==0) parent[nxt]=me;
                table[s][nxt]=table[s][me]+1;
                queue[head++]=nxt;
            }
        }
    }
}

inline void write_int(int x){
    for(int i=9;0<=i;--i) encode_bit(1&(x>>i));
}

inline void write_smallint(int x){
    if(x==0) encode_bit(0);
    else if(x==1) encode_bit(1), encode_bit(0);
    else          encode_bit(1), encode_bit(1);
}

void encode(int n, int h, int ne, int *v1, int *v2){
    input(ne,v1,v2);
    
    int i;
    for(i=0;i<h;++i) bfs(i);
    
    int j;
    for(i=1;i<h;++i) write_int(table[i][0]); // triangular table

    for(i=1;i<n;++i) write_int(parent[i]);
    
    int pc=0, zc=0, mc=0, tmp;
    for(i=1;i<n;++i){
        for(j=0;j<h;++j){
            if(i==j || (parent[i]==0 && j==0)) continue;
            tmp=table[j][i]-table[j][parent[i]];
            if(tmp==0) ++zc;
            else if(tmp>0) ++pc;
            else ++mc;
        }
    }
    
    pp sorter[3]={{zc,0},{pc,1},{mc,-1}};
    sort(sorter,sorter+3);

    for(i=0;i<3;++i) conv[sorter[i].second+1]=2-i;
    write_smallint(conv[0]);
    write_smallint(conv[1]);
    write_smallint(conv[2]);
    
    for(i=1;i<n;++i) for(j=0;j<h;++j){
        if(parent[i]==0 && j==0){
            write_int(table[j][i]);
        } else if(i!=j){
            tmp=table[j][i]-table[j][parent[i]];
            if(tmp==0) write_smallint(conv[1]);
            else if(tmp>0) write_smallint(conv[2]);
            else write_smallint(conv[0]);
        }
    }
}
