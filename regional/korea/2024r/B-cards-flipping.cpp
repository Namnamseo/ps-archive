#include <iostream>
#include <numeric>
#include <string>
#include <tuple>
#include <utility>
#include <vector>
#include <queue>
using namespace std;
using pp=pair<int,int>;
using ll=long long;
#define rep(i, n) for (int i=0; i<n; ++i)
#define rrep(i, n) for (int i=1; i<=n; ++i)
#define eb emplace_back
#define x first
#define y second

int n, v = int(1e6);
const int maxn = int(2e5) + 10;
const int maxv = int(1e6) + 10;

pp e[maxn];

int par[maxv];
int root(int x) {
    int r = x, t;
    while (r != par[r]) r = par[r];
    while (x != r) t = par[x], par[x]=r, x=t;
    return r;
}

int cv[maxv], ce[maxv];

int main()
{
    ios_base::sync_with_stdio(0); cin.tie(0);

    cin >> n;
    iota(par+1, par+v+1, 1);

    rrep(i, n) cin >> e[i].x;
    rrep(i, n) cin >> e[i].y;

    rrep(i, n) {
        auto [a, b] = e[i];
        par[root(a)] = root(b);
    }

    rep(i, v+1) ++cv[root(i)];
    rrep(i, n) ++ce[root(e[i].x)];

    int ans = 0;
    rep(i, v+1) if (par[i] == i) {
        if (ce[i] == cv[i] - 1) {
            ans += ce[i];
        } else {
            ans += cv[i];
        }
    }

    cout << ans << '\n';

    return 0;
}

