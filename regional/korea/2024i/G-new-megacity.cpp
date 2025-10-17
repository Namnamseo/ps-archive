#include <algorithm>
#include <bitset>
#include <cmath>
#include <numeric>
#include <iostream>
#include <string>
#include <utility>
#include <vector>
#include <queue>
using namespace std;
using pp=pair<int,int>;
using t3=tuple<int,int,int>;
using ll=long long;
#define rep(i, n) for (int i=0; i<n; ++i)
#define rrep(i, n) for (int i=1; i<=n; ++i)
#define eb emplace_back
#define pb push_back
#define x first
#define y second
#define all(v) v.begin(), v.end()

int n, m;
const int maxn = int(1e5) + 10;
const int maxm = int(1e5) + 10;

pair<pp,pp> edge[maxm];

int par[maxn];

int root(int x) {
    int r = x, t;
    while (par[r] != r) r = par[r];
    while (x != r) t = par[x], par[x] = r, x = t;
    return r;
}

char ans[maxm];

int jedge_j;
int first_jedge[maxn];
int jedge_t[2*maxm];
int next_jedge[2*maxm];

bitset<maxn> vis;
int depth[maxn];

void add_edge(int v, int t) {
    ++jedge_j;
    next_jedge[jedge_j] = first_jedge[v];
    first_jedge[v] = jedge_j;
    jedge_t[jedge_j] = t;
}

int dfs(int x, int par_edge_t) {
    vis.set(x);

    int paint_up = 0;

    for (int j = first_jedge[x]; j; j = next_jedge[j]) {
        int t = jedge_t[j];
        if (t == par_edge_t) continue;

        int y = edge[t].y.x + edge[t].y.y - x;
        if (!vis[y]) {
            // printf("%d --> %d\n", x, y);
            depth[y] = depth[x] + 1;
            int thy = dfs(y, t);
            if (thy) {
                // printf("Edge %d -- %d is redundant (painted up)\n", x, y);
                ans[edge[t].x.y] = 2;
                paint_up = max(paint_up, thy-1);
            }
        } else {
            // printf("%d --> %d is CYCLE! edge redundant\n", x, y);
            ans[edge[t].x.y] = 2;
            paint_up = max(paint_up, depth[x] - depth[y]);
        }
    }

    return paint_up;
}

void Solve(vector<int> &ab, vector<int> &ts) {
    // printf("Vertices: "); for (int x: ab) printf("%d ", x); printf("\n");
    // printf("Edges:\n");
    // for (int t: ts) printf("* %d -- %d\n", edge[t].y.x, edge[t].y.y);
    // printf("\n");

    for (int x: ab) {
        first_jedge[x] = 0;
        vis.reset(x);
    }

    jedge_j = 0;
    for (int t: ts) {
        auto [a, b] = edge[t].y;
        add_edge(a, t); add_edge(b, t);
    }

    for (int x: ab) if (!vis[x]) depth[x]=0, dfs(x, -1);
}

int main()
{
    ios_base::sync_with_stdio(0); cin.tie(0);

    cin >> n >> m;
    iota(par+1, par+n+1, 1);

    rep(i, m) {
        int a, b, w; cin >> a >> b >> w;
        edge[i] = {{w, i}, {a, b}};
    }

    sort(edge, edge+m);
    for (int i=0, j; i<m; i=j) {
        for (j=i+1; j<m && edge[i].x.x == edge[j].x.x; ++j); // printf("i %d j %d edge %d %d\n", i, j, edge[i].x.x, edge[j].x.x);

        static vector<int> ts, ab; ts.clear(); ab.clear();

        for (int t=i; t<j; ++t) {
            auto [a, b] = edge[t].y; int ei = edge[t].x.y;
            a = root(a); b = root(b);
            edge[t].y = {a, b};
            if (a == b) { ans[ei] = 3; continue; }
            ts.pb(t); ab.pb(a); ab.pb(b);
        }

        Solve(ab, ts);

        for (int t=i; t<j; ++t) {
            auto [a, b] = edge[t].y;
            a = root(a); b = root(b);
            if (a != b) {
                // printf("joining %d -- %d...\n", a, b);
                par[a] = b;
            }
        }

        // printf("i=%d, j=%d\n", i, j);
    }

    rep(i, m) {
        if (ans[i] == 0) ans[i] = 1;
        cout << int(ans[i]) << '\n';
    }

    return 0;
}
