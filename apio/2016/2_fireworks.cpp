#include <bits/stdc++.h>
using namespace std;
void read(int& x){ scanf("%d",&x); }
typedef long long ll;
void read(ll& x){ scanf("%lld",&x); }
template<typename T,typename... Args>
void read(T& a,Args&... b){ read(a); read(b...); }
#define pb push_back
#define all(x) (x).begin(),(x).end()

typedef pair<int,ll> pp;

int n;
vector<pp> edge[300010];

void in(){
    int m;

    read(n, m);
    n += m;
    for(int i=2; i<=n; ++i){
        int a;
        ll b;
        read(a,b);
        edge[a].pb({i, b});
    }
}

struct tree_result {
    map<ll,ll> dy_points;
    ll start_val, start_grad, end_grad;
    tree_result(){
        start_grad = 0;
        end_grad = 0;
        start_val = 0;
    }
    void applyDistance(ll d){
        if(dy_points.size() == 0u){
            dy_points[d] = 2;
            start_val = d;
            start_grad = -1;
            end_grad = 1;
            return;
        }
        ll cur_grad = end_grad, bef_grad = -1, change_pt=-1, bef_pt=-1;
        for(auto it = --dy_points.end();;){
            bef_grad = cur_grad;
            cur_grad -= it->second;
            bef_pt = change_pt;
            change_pt = it->first;
            if(cur_grad <= -1) break;
            it = --dy_points.erase(it);
        }
        dy_points.erase(--dy_points.end());
        start_val += d;
        if(bef_grad == 0){
            if(cur_grad != -1){
                dy_points[change_pt] = -1 - cur_grad;
            }
            dy_points[change_pt + d] = 1;
            dy_points[bef_pt    + d] = 1;
        } else {
            if(cur_grad != -1){
                dy_points[change_pt] = -1 - cur_grad;
            }
            dy_points[change_pt + d] = 2;
        }
        end_grad = 1;
    }
    tree_result operator+(tree_result& r){
        tree_result ret;
        ret.start_val = start_val + r.start_val;
        ret.start_grad = start_grad + r.start_grad;
        ret.end_grad = end_grad + r.end_grad;
        auto &a = dy_points, &b = r.dy_points;
        if(a.size() < b.size()) swap(a, b);
        swap(ret.dy_points, a);
        for(auto it=b.begin(); it!=b.end();){
            ret.dy_points[it->first] += it->second;
            it = b.erase(it);
        }
        return ret;
    }
};

int par[300010];

tree_result res[300010];

int sI[300010], top;
pp last[300010];

void dfs(int x){
    sI[top++]=x;
    while(top){
        x=sI[top-1];
        if(last[x].first){
            int y, d; tie(y, d) = last[x];
            res[y].applyDistance(d);
            if(res[x].dy_points.size() == 0u){
                res[x] = res[y];
            } else {
                res[x] = res[x] + res[y];
            }
            res[y].dy_points.clear();
            last[x] = {0, 0};
        }
        if(edge[x].size() == 0u){
            --top;
            continue;
        } else {
            int y, d; tie(y, d) = edge[x].back();
            edge[x].pop_back();
            if(y == par[x]) continue;
            par[y] = x;
            last[x] = {y, d};
            sI[top++] = y;
        }
    }
}

int main()
{
    in();
    dfs(1);
    auto res = ::res[1];
    ll val = res.start_val;
    ll grad = res.start_grad;
    ll min_val = 1LL << 62;
    ll last_pt = 0;
    for(auto tmp : res.dy_points){
        ll cur_pt, cur_dg;
        tie(cur_pt, cur_dg) = tmp;
        val += grad * (cur_pt - last_pt);
        min_val = min(min_val, val);
        last_pt = cur_pt;
        grad += cur_dg;
    }
    printf("%lld\n", min_val);
    return 0;
}
