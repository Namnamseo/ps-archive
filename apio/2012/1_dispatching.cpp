#include <cstdio>
#include <vector>
#include <queue>
using namespace std;
vector<int> edge[100010];
priority_queue<int> pq[100010];
typedef long long ll;
int n,m;

ll ans;
int sum [100010];
int cnt [100010];
int lead[100010];
int pay [100010];

inline void put(priority_queue<int>& pq,int& sum,int& cnt,int x){
    pq.push(x); sum+=x; ++cnt;
    while(sum>m){
        x=pq.top();
        sum-=x; pq.pop(); --cnt;
    }
}

void dfs(int x){
    int bigind = -1;
    for(auto& nxt:edge[x]){
        dfs(nxt);
        if(bigind==-1 || (pq[bigind].size()<pq[nxt].size())) bigind=nxt;
    }
    if(bigind != -1) swap(pq[x], pq[bigind]), swap(sum[x], sum[bigind]), swap(cnt[x], cnt[bigind]); // constant time swap
    
    priority_queue<int>& mypq = pq[x];
    int& mysum = sum[x];
    int& mycnt = cnt[x];
    
    put(mypq, mysum, mycnt, pay[x]);
    
    for(auto& nxt : edge[x]){
        if(nxt != bigind){
            priority_queue<int>& nxtpq = pq[nxt];
            while(nxtpq.size()){
                put(mypq, mysum, mycnt, nxtpq.top()); nxtpq.pop();
            }
        }
    }
    
    ans=max(ans, ll(mycnt)*lead[x]);
}

int main()
{
    scanf("%d%d",&n,&m);
    int b;
    int root = -1;
    for(int i=1; i<=n; ++i){
        scanf("%d%d%d",&b,pay+i,lead+i);
        if(b) edge[b].push_back(i);
        else root=i;
    }
    dfs(root);
    printf("%lld\n",ans);
    return 0;
}
