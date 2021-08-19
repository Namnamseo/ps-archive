#include <bits/stdc++.h>
using namespace std;
#define sz(v) ((int)((v).size()))
#define all(v) (v).begin(), (v).end()
#define pb push_back
#define coord_comp(v) sort(all(v)), v.erase(unique(all(v)), v.end())
#define v_index(v, x) (lower_bound(all(v),x)-(v).begin())
typedef pair<int,int> pp;
typedef long long ll;

int n,k;

vector<pp> edge[200001];

bool dead[200010];

int nt;
int pre_time[200010];
int pre_par [200010];
int pre_size[200010];
int pre_mcsz[200010];

void pre_dfs(int x){
    pre_size[x]=1;
    pre_mcsz[x]=0;
    pre_time[x]=nt;
    for(pp ep : edge[x]){
        int y = ep.first;
        if(dead[y] || (pre_time[y]==nt && pre_par[x]==y)) continue;
        pre_par[y]=x;
        pre_dfs(y);
        pre_mcsz[x] = max(pre_mcsz[x], pre_size[y]);
        pre_size[x] += pre_size[y];
    }
}

int find_cent(int root){
    ++nt;
    pre_par[root] = -1;
    pre_dfs(root);
    int sz=pre_size[root];
    while(true){
        if(pre_mcsz[root] <= sz/2) break;
        for(pp ep:edge[root]){
            int y=ep.first;
            if(dead[y] || pre_par[root]==y) continue;
            if(pre_mcsz[root] == pre_size[y]){
                root=y; break;
            }
        }
    }
    return root;
}

int ans=2e9;

int par[200010];

void dfs_child(int x, int depth, int dc, set<pp>& s){
    s.insert({depth,dc});
    for(pp ep:edge[x]){
        int y=ep.first;
        if(dead[y] || par[x]==y) continue;
        par[y]=x;
        dfs_child(y, depth+ep.second, dc+1, s);
    }
}

inline void find_pairs(pp& t,multiset<pp>& s){
    if(t.first > k) return;
    auto it=s.lower_bound({k-t.first,0});
    if(it!=s.end() && it -> first == k-t.first){
        ans = min(ans, t.second + it->second);
    }
}

void treat_root(int x){
    vector<set<pp>> sets;
    for(pp ep:edge[x]){
        int y=ep.first;
        if(dead[y]) continue;
        par[y]=x;
        set<pp> ns;
        dfs_child(y, ep.second, 1, ns);
        sets.pb(ns);
    }
    multiset<pp> s;
    for(auto& ss:sets){
        for(pp t:ss) s.insert(t);
    }
    s.insert({0,0});
    for(auto& v:sets){
        for(auto t:v) s.erase(s.find(t));
        for(auto t:v) find_pairs(t, s);
        for(auto t:v) s.insert(t);
    }
}

int best_path(int N, int K, int H[][2], int L[]) {
    n = N; k = K;
    for(int i=0; i<n-1; ++i){
        int a=H[i][0],b=H[i][1],c=L[i];
        edge[a].pb({b,c});
        edge[b].pb({a,c});
    }

    queue<int> q;
    q.push(1);
    while(q.size()){
        int t = q.front(); q.pop();
        int cent = find_cent(t);
        treat_root(cent);
        dead[cent] = true;
        for(pp ep:edge[cent]){
            int y = ep.first;
            if(!dead[y]){
                q.push(y);
            }
        }
    }
    if(ans == int(2e9)) ans=-1;
    return ans;
}
