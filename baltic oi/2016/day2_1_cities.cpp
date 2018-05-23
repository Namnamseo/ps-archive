#include <cstdio>
#include <vector>
#include <algorithm>
#include <queue>
#define pb push_back
using namespace std;

vector<int> edge[100010];
vector<int> ec[100010];

int root;
int v[5];
int n,k;

void read(int& x){ scanf("%d",&x); }
template<typename T,typename... Args> void read(T& a,Args&... b){ read(a); read(b...); }

void in(){
    int m;
    read(n,k,m,root); --k;
    for(int i=0;i<k;++i) read(v[i]);
    for(;m--;){
        int a,b,c; read(a,b,c);
        edge[a].pb(b); edge[b].pb(a);
        ec[a].pb(c); ec[b].pb(c);
    }
}

typedef long long ll;
typedef pair<ll,int> pli;
typedef pair<int,int> pp;
typedef pair<ll,pp> plp;

ll dijk[100010][16];
ll dtemp[100010];

priority_queue<pli> pq_;
priority_queue<plp> pq;

void dijkstra(int start,bool km1){
    int sv=(km1?v[start]:start);
    for(int i=1;i<=n;++i) dtemp[i]=(1LL<<60);
    dtemp[sv]=0; pq_.push({0ll,sv});
    while(pq_.size()){
        auto tmp=pq_.top(); pq_.pop();
        int me;
        if(tmp.first != -dtemp[me=tmp.second]) continue;
        int sz=edge[me].size();
        for(int i=0;i<sz;++i){
            int nxt=edge[me][i], c=ec[me][i];
            if(dtemp[nxt]>dtemp[me]+c){
                dtemp[nxt]=dtemp[me]+c;
                pq_.push({-dtemp[nxt],nxt});
            }
        }
    }
    if(km1) for(int i=1;i<=n;++i) dijk[i][1<<start]=dtemp[i];
}

void renew(int pos,int mask){
    int om=(((1<<k)-1)^mask);
    int i,m;
    ll base=dijk[pos][mask], tmpdiff;
    for(m=om;m; m=((m-1)&om)){
        tmpdiff = 0;
        for(i=0;i<k;++i){
            if((1&(m>>i))==1){
                tmpdiff += dijk[pos][1<<i];
            }
        }
        if(base+tmpdiff < dijk[pos][mask|m]){
            dijk[pos][mask|m]=base+tmpdiff;
            pq.push({-dijk[pos][mask|m],{pos,mask|m}});
        }
    }
}

int main()
{
    in();
    for(int i=0;i<k;++i) dijkstra(i, true);
    for(int i=1;i<=n;++i){
        int ks1=(1<<k);
        for(int j=1;j<ks1;++j){
            if((j&(j-1)))
                for(int t=0;t<k;++t)
                    if(1&(j>>t)) dijk[i][j] += dijk[i][1<<t];
            pq.push({-dijk[i][j], {i,j}});
        }
    }
    while(pq.size()){
        auto a=pq.top(); pq.pop();
        ll dj=-a.first; int x=a.second.first, y=a.second.second;
        if(dijk[x][y]!=dj) continue;
        int i,sz=edge[x].size(),nxt,cst;
        for(i=0;i<sz;++i){
            nxt=edge[x][i];
            cst=ec  [x][i];
            if(dijk[nxt][y]>dijk[x][y]+cst){
                dijk[nxt][y]=dijk[x][y]+cst;
                pq.push({-dijk[nxt][y], {nxt,y}});
                renew(nxt,y);
            }
        }
    }
    ll ans=(1LL<<62);
    dijkstra(root, false);
    for(int i=1;i<=n;++i){
        ans=min(ans, dijk[i][((1<<k)-1)]+dtemp[i]);
    }
    printf("%lld\n",ans);
    return 0;
}
