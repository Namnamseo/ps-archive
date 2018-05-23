#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef pair<int,int> pp;
typedef pair<ll,ll> pll;
void read(int& x){ scanf("%d",&x); }
void read(ll& x){ scanf("%lld",&x); }
template<typename T,typename... Args>
void read(T& a,Args&... b){ read(a); read(b...); }
#define all(x) (x).begin(),(x).end()
#define pb push_back
#define x first
#define y second

int n, m;

struct bipar {
    int v;
    vector<int> mat, rev;
    vector<bool> dl, dr;
    vector<bool> vis;
    vector<pp> forces;
    vector<vector<int>> edge;
    int matches;
    void set_v(int _v){
        v = _v;
        mat.assign(v+1, 0);
        rev.assign(v+1, 0);
        dl.assign(v+1, false);
        dr.assign(v+1, false);
        vis.assign(v+1, false);
        edge.clear(); edge.resize(v+1);
        forces.clear();
        matches = 0;
    }
    void force_match(int x, int y){
        forces.pb(pp{x, y});
        dl[x]=true; dr[y]=true; ++matches;
    }
    bool dfs(int x){
        if(vis[x]) return false;
        vis[x]=1;
        for(int y:edge[x]) if(!dr[y]){
            if(rev[y]==-1 || dfs(rev[y])){
                mat[x]=y; rev[y]=x;
                return true;
            }
        }
        return false;
    }
    int match(){
        int ans = matches;
        fill(all(rev), -1);
        for(int i=1; i<=v; ++i) if(!dl[i]){
            fill(all(vis), false);
            if(dfs(i)) ++ans;
        }
        return ans;
    }
    vector<pp> get(){
        vector<pp> ret = forces;
        for(int i=1; i<=v; ++i) if(!dl[i] && mat[i]){
            ret.pb(pp{i, mat[i]});
        }
        return ret;
    }
} lr, diag;

void Work(){
    read(n, m);
    lr.set_v(n);
    diag.set_v(2*n-1);
    map<pp,int> def;
    for(int i=1; i<=n; ++i) for(int j=1; j<=n; ++j){
        diag.edge[i-j+n].pb(i+j-1);
        lr.edge[i].pb(j);
    }
    for(int i=1; i<=m; ++i){
        char mod[5]; int x, y;
        scanf("%s%d%d", mod, &x, &y);
        if(mod[0] != '+'){
            def[pp{x, y}]+=1;
            lr.force_match(x, y);
        }
        if(mod[0] != 'x'){
            def[pp{x, y}]+=2;
            diag.force_match(x-y+n, x+y-1);
        }
    }
    int ans = lr.match() + diag.match();
    map<pp,int> m;
    auto conv=[](pp tmp){ return pp{(tmp.x+tmp.y+1-n)/2,(tmp.y-tmp.x+1+n)/2}; };
    
    for(auto tmp:lr.get()) m[tmp] += 1;
    for(auto tmp:diag.get()) m[conv(tmp)] += 2;
    
    for(auto tmp:def) if(m[tmp.x]==tmp.y) m.erase(tmp.x);
    
    printf("%d %d\n", ans, int(m.size()));
    const char* exp=".x+o";
    for(auto tmp:m){
        printf("%c %d %d\n", exp[tmp.y], tmp.x.x, tmp.x.y);
    }
}

int main()
{
    freopen("in_l", "r", stdin);
    freopen("out_l", "w", stdout);
	int tc; read(tc);
	for(int i=1; i<=tc; ++i){
        printf("Case #%d: ", i);
        Work();
	}
    return 0;
}
