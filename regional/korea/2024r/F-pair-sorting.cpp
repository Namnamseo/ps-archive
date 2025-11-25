#include <iostream>
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

int n, m;

using t3=tuple<int,int,int>;
vector<t3> ans;

int t[110][2];

pp fnd(int x) {
    static int tmp[2], tn; tn=0;
    rrep(i, n) rep(j, 2) {
        if (t[i][j] ==x) tmp[tn++] = i;
    }
    return {tmp[0], tmp[1]};
}

int main()
{
    ios_base::sync_with_stdio(0); cin.tie(0);

    cin >> n;

    rrep(i, n) t[i][0] = t[i][1] = n+1-i;

    rrep(i, n) rep(j, 2) {
        auto fndr = fnd(i);

        int target = (j == 0 ? fndr.x : fndr.y);
        if (target == i) continue;

        for (int x = target; i < x; --x) {
            int more = (t[x-1][0] < t[x-1][1]);
            int mine = (t[x][1] == i);

            ans.eb(x-1, t[x-1][more], t[x][mine]);
            swap(t[x-1][more], t[x][mine]);
        }
    }

    cout << ans.size() << '\n';

    for (auto [x, y, z]: ans) {
        cout << x << ' ' << y << ' ' << z << '\n';
    }

    return 0;
}

