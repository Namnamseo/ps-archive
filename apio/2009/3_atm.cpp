#include <cstdio>
#include <vector>
using namespace std;

const int maxn=500010;

vector<int> edge[maxn];
vector<int> ce  [maxn];

int n,m;
int size   [maxn];
int getcyc [maxn];
int cycsize[maxn];
int parent [maxn];
bool re    [maxn];
int cycind;
int s;
int time;
int lowlink [maxn];
int vis     [maxn];
bool onstack[maxn];
int stack   [maxn];
int top;
int min(int a,int b) { return a>b?b:a; }

void dfs(int pos){
    int i,sz=edge[pos].size(), nxt;
    vis[pos]=++time;
    int& ll=lowlink[pos];
    ll=time;
    stack[top++]=pos;
    onstack[pos]=1;
    for(i=0;i<sz;++i){
        nxt=edge[pos][i];
        if(nxt==parent[pos]) continue;
        if(!vis[nxt]){
            parent[nxt]=pos;
            dfs(nxt);
            ll=min(ll,lowlink[nxt]);
        } else if(onstack[nxt]) ll=min(ll,vis[nxt]);
    }
    if(vis[pos]==ll){
        while(top){
            getcyc[stack[top-1]]=cycind;
            cycsize[cycind]+=size[stack[top-1]];
            onstack[stack[top-1]]=0;
            --top;
            if(top==0 || stack[top]==pos) break;
        }
        ++cycind;
    }
}
int ans;

bool cvis  [500010];
int history[500010];
int ht;
int psum   [500010];

void dfs2(int a){
    cvis[a]=true;
    int i,sz=ce[a].size(), nxt;
    for(i=0;i<sz;++i){
        nxt=ce[a][i];
        if(!cvis[nxt]) dfs2(nxt);
    }
    history[ht++]=a;
}

int main()
{
    int a,b;
    int i,j,sz,nxt;
    int rn;
    scanf("%d%d",&n,&m);
    for(i=0;i<m;++i) scanf("%d%d",&a,&b), edge[a].push_back(b);
    for(i=1;i<=n;++i) scanf("%d",size+i);
    for(i=1;i<=n;++i) if(!vis[i]) dfs(i);
    
    scanf("%d%d",&s,&rn);
    for(;rn--;) scanf("%d",&a), re[getcyc[a]]=true;
    for(i=1;i<=n;++i){
        sz=edge[i].size();
        a=getcyc[i];
        for(j=0;j<sz;++j){
            nxt=edge[i][j];
            b=getcyc[nxt];
            ce[a].push_back(b);
        }
    }
    dfs2(getcyc[s]);
    int ci;
    for(i=ht-1;0<=i;--i){
        ci=history[i];
        
        psum[ci]+=cycsize[ci];
        if(re[ci]) ans=max(ans,psum[ci]);
        
        sz=ce[ci].size();
        
        for(j=0;j<sz;++j){
            nxt=ce[ci][j];
            psum[nxt]=max(psum[nxt],psum[ci]);
        }
    }
    printf("%d\n",ans);
    return 0;
}

