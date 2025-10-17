#include <cmath>
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

const int maxn = int(1e4) + 10;
const double pi = 3.14159265358979323846264;

int n;

int mod = 3600;
int Z(int x) {
    if (x < 0) {
        x = mod - (-x)%mod; if (x >= mod) x -= mod; return x;
    } else return x % mod;
}

double _cos[3600], _sin[3600];
double Cos(int theta) { return _cos[Z(theta)]; }
double Sin(int theta) { return _sin[Z(theta)]; }
void init_trig() {
    rep(i, 3600) {
        double theta = i / 1800.0 * pi;
        _cos[i] = cos(theta);
        _sin[i] = sin(theta);
    }
}

int lp[maxn][2];
int cc[3600];

int radial_count(int dir, int offset) {
    int crossings = 0;
    int ln_up = 0, ln_down = 0;
    rep(i, n) {
        int la = Z(lp[i][0] - dir);
        int lb = Z(lp[i][1] - dir);

        if (!la || !lb) {
            la += lb;
            if (la < 1800) ++ln_up;
            else ++ln_down;
            continue;
        }

        double cA = Cos(la), sA = Sin(la), cB = Cos(lb), sB = Sin(lb);
        double nume = cA*sB - sA*cB, denom = sB-sA;
        if (denom < 0) nume=-nume, denom=-denom;
        if (nume < 0) continue;

        if (nume <= denom && offset / 1e3 * denom <= nume) ++crossings;
    }

    int ret = (crossings + ln_down) & 1;
    // printf("dir %4d, offset %4d --> cross %d lines; up %d, down %d; parity %d\n", dir, offset, crossings, ln_up, ln_down, ret);
    return ret;
}

int main()
{
    ios_base::sync_with_stdio(0); cin.tie(0);
    init_trig();

    cin >> n;
    rep(i, n) { cin >> lp[i][0] >> lp[i][1]; ++cc[lp[i][0]]; ++cc[lp[i][1]]; }

    int p1dir, p1off; cin >> p1dir >> p1off;
    int p2dir, p2off; cin >> p2dir >> p2off;

    int ans = 0;

    ans += radial_count(p1dir, p1off);
    ans += radial_count(p2dir, p2off);

    int mindir = min(p1dir, p2dir);
    int maxdir = max(p1dir, p2dir);
    for (int i=mindir; i<maxdir; ++i) ans += cc[i];

    if (ans%2 == 0) cout << "YES\n";
    else cout << "NO\n";

    return 0;
}
