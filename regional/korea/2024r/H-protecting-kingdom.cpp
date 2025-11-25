#include <algorithm>
#include <bitset>
#include <iostream>
#include <numeric>
#include <string>
#include <tuple>
#include <utility>
#include <vector>
#include <map>
#include <queue>
using namespace std;
using ll=long long;
using pp=pair<int,int>;
using plli=pair<ll,int>;
#define rep(i, n) for (int i=0; i<n; ++i)
#define rrep(i, n) for (int i=1; i<=n; ++i)
#define all(v) v.begin(), v.end()
#define siz(v) ((int)(v.size()))
#define eb emplace_back
#define pb push_back
#define x first
#define y second

int n; ll w;
int ans;

const int maxn = 250010;

ll el[maxn];
int fei[maxn];
int nei[maxn];
int ey[maxn];
vector<ll> haz[maxn];

using mlli=map<ll,int>;

void fancy_insert(mlli &m, plli t) {
    auto it = m.lower_bound(t.x+1);
    if (it != m.begin()) {
        auto pit = prev(it);
        if (pit->y >= t.y) return;
        if (pit->x == t.x) m.erase(pit);
    }
    it = m.insert_or_assign(it, t.x, t.y);
    for (;;) {
        auto nxt = next(it);
        if (nxt != m.end() && t.y >= nxt->y) m.erase(nxt);
        else break;
    }
}

mlli dfs(int x, int acnt, ll adst) {
    mlli m;
    for (int ei=fei[x]; ei; ei=nei[ei]) { int y =ey[ei];
        auto tmp = dfs(y, acnt+siz(haz[ei]), adst+el[ei]);
        for (int i=0, s=siz(haz[ei]); i<s; ++i) {
            auto it = tmp.lower_bound(w + adst + haz[ei][i] + 1);
            if (it != tmp.begin()) {
                ans = max(ans, prev(it)->y - acnt - i);
            }
            fancy_insert(tmp, plli{adst+haz[ei][i], acnt+1+i});
        }

        if (siz(m) < siz(tmp)) swap(m, tmp);
        for (auto [d1, c1]: tmp) {
            // d1+d2-2*adst <= w
            auto it = m.lower_bound(w + 2*adst - d1 + 1);
            if (it != m.begin()) {
                ans = max(ans, c1 + prev(it)->y - 2*acnt);
            }
        }
        for (auto t: tmp) fancy_insert(m, t);
    }

    return m;
}

int main()
{
    ios_base::sync_with_stdio(0); cin.tie(0);

    cin >> n >> w;

    rrep(ei, n-1) {
        int p, k; ll l; cin >> p >> el[ei] >> k;
        haz[ei].resize(k); for (ll &x: haz[ei]) cin >> x;
        nei[ei] = fei[p]; fei[p] = ei; ey[ei] = ei+1;

        for (int head=0, tail=0, n=haz[ei].size(); head<n; ++head) {
            while (haz[ei][head]-haz[ei][tail] > w) ++tail;
            ans = max(ans, head-tail+1);
        }
    }

    dfs(1, 0, 0);

    cout << ans << '\n';

    return 0;
}

