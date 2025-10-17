#include <iostream>
#include <string>
#include <utility>
#include <vector>
#include <queue>
using namespace std;
using pp=pair<int,int>;
using ll=long long;
#define rep(i, n) for (int i=0; i<n; ++i)
#define rrep(i, n) for (int i=1; i<=n; ++i)
#define eb emplace_back
#define pb push_back

const int maxn = int(1e3) + 10;
const int maxv = 2 * (maxn + maxn - 1) + 10;

int n, m;

/*
i+j+1 (Slash) : 1 to n+m-1
i-j+m-1 (Backslash): 0 to n+m-2
*/

int Slash(int i, int j) {
    return i + j + 1;
}

int Backslash(int i, int j) {
    return n+m + i-j+m-1;
}

int par[maxv];
int enemy[maxv];
int root(int x) {
    int r = x, t;
    while (par[r] != r) r = par[r];
    while (x != r) t = par[x], par[x] = r, x = t;
    return r;
}

bool Ack(int a, int b) {
    a = root(a); b = root(b);
    if (a == b) return true;
    if (enemy[a] == b) return false;

    par[a] = b;
    if (enemy[a] && enemy[b]) par[enemy[a]] = enemy[b];
    else enemy[b] = enemy[a] + enemy[b];

    if (enemy[b]) enemy[enemy[b]] = b;

    return true;
}

bool Dis(int a, int b) {
    a = root(a); b = root(b);
    if (a == b) return false;
    if (enemy[a] == b) return true;


    if (enemy[a]) par[enemy[a]] = b;
    if (enemy[b]) par[enemy[b]] = a;
    enemy[a] = b; enemy[b] = a;
    return true;
}

int main()
{
    ios_base::sync_with_stdio(0); cin.tie(0);
    cin >> n >> m;

    vector<int> vs;
    rep(j, m-1) vs.pb(Slash(0, j));
    rep(i, n) vs.pb(Slash(i, m-1));
    rep(j, m) vs.pb(Backslash(0, j));
    rep(i, n-1) vs.pb(Backslash(i+1, 0));
    for (int x: vs) par[x] = x;

    rep(i, n) rep(j, m) {
        int x; cin >> x;

        int a = Slash(i, j), b = Backslash(i, j);
        if (!((x ? Dis : Ack)(a, b))) {
            cout << "-1\n";
            return 0;
        }
    }

    static int b1[maxv], b2[maxv];

    for (int x: vs) {
        int a = root(x);
        if (!enemy[a]) continue;

        if (a < enemy[a]) b1[a]++;
        else if (a > enemy[a]) b2[enemy[a]]++;
    }

    int ans = 0;
    for (int a: vs) {
        if (!(par[a] == a && enemy[a] && a < enemy[a])) continue;
        ans += min(b1[a], b2[a]);
    }
    cout << ans << '\n';

    return 0;
}
