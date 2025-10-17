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

int n, m;

int A[maxn][maxn];
int it[maxn];

int main()
{
    ios_base::sync_with_stdio(0); cin.tie(0);
    cin >> n >> m;
    rrep(i, n) rrep(j, n) cin >> A[i][j];
    rrep(i, n) rrep(j, n) {
        int b; cin >> b;
        it[j] = max(it[j], abs(A[i][j] - b));
    }

    int ans = 0;
    rep(i, m) {
        int x; cin >> x;
        ans += it[x];
    }
    cout << ans << '\n';

    return 0;
}
