#include <vector>
#include <algorithm>
#include <queue>
#define pb push_back
using namespace std;

typedef pair<int,int> pp;

vector<pp> edge[100010];
typedef long long ll;

ll dijk[100010];
ll scnd[100010];
typedef pair<ll,int> pd;

priority_queue<pd> pq;

int travel_plan(int N, int M, int R[][2], int L[], int K, int P[])
{
    for(int i=0; i<N; ++i){
        dijk[i]=(1LL<<62);
        scnd[i]=(1LL<<62);
    }
    for(int i=0; i<K; ++i){
        int a=P[i];
        dijk[a]=0;
        scnd[a]=0;
        pq.push({scnd[a],a});
    }
    for(int i=0; i<N; ++i) edge[i].clear();
    for(int i=0; i<M; ++i){
        int a=R[i][0], b=R[i][1];
        if(dijk[b]!=0) edge[a].pb({b, L[i]});
        if(dijk[a]!=0) edge[b].pb({a, L[i]});
    }
    for(;pq.size();){
        auto t=pq.top(); pq.pop();
        int x=t.second;
        if(scnd[x] != -t.first) continue;
        for(pp yy:edge[x]){
            int y=yy.first; int d=yy.second;
            if(dijk[y]>scnd[x]+d){
                if(dijk[y]<scnd[y]){
                    scnd[y] = dijk[y];
                    pq.push({-scnd[y],y});
                }
                dijk[y] = scnd[x]+d;
            } else if(scnd[y] > scnd[x]+d){
                scnd[y]=scnd[x]+d;
                pq.push({-scnd[y],y});
            }
        }
    }
    return scnd[0];
}
