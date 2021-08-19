#include "railroad.h"
#include <bits/stdc++.h>
using namespace std;

#define eb emplace_back
#define x first
#define y second

using pp=pair<int,int>;
using ll=long long;

map<int,int> df;

const int inf = int(1e9) + 10;
const int maxn = int(4e5) + 10;

int par[maxn];
vector<pp> D;

int R(int x){ return (par[x]==x) ? x : (par[x]=R(par[x])); }

vector<tuple<int,int,int>> ev;

long long plan_roller_coaster(std::vector<int> s, std::vector<int> t) {
    int n = s.size();

    for(int i=0; i<n; ++i) {
        df[s[i]] += -1;
        df[t[i]] += +1;
    }

    df[0] += +1;
    df[inf] += -1;

    D = vector<pp>(df.begin(), df.end());

    int sz = D.size();
    iota(par, par+sz, 0);

    ll ans = 0;
    int lev = 0, last = 0;

    for(int i=0; i<sz; ++i) {
        auto &tmp = D[i];
        if(lev < 0) {
            ans += (tmp.x - last) * 1ll * (-lev);
        }
        if(lev && i) {
            par[R(i-1)] = i;
        }
        last = tmp.x;
        lev += tmp.y;
    }

    auto fnd = [&](int x){ return int(lower_bound(D.begin(), D.end(), pp(x, -inf)) - D.begin()); };
    for(int i=0; i<n; ++i) {
        par[R(fnd(s[i]))] = R(fnd(t[i]));
    }
    par[R(fnd(0))] = R(fnd(inf));

    for(int i=0; i+1<sz; ++i) {
        int va = R(i), vb = R(i+1);
        if(va != vb) ev.eb(D[i+1].x-D[i].x, va, vb);
    }

    sort(ev.begin(), ev.end());
    for(auto &tmp:ev) {
        int v, a, b; tie(v, a, b) = tmp;
        if(R(a) != R(b)) {
            ans += v;
            par[R(a)] = R(b);
        }
    }

    return ans;
}
