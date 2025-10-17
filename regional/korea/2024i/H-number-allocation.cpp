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

int A,B,C,D,E,F,G,H;

int x[9];

int &a = x[0];
int &b = x[1];
int &c = x[2];
int &e = x[3];
int &f = x[4];
int &g = x[5];
int &i = x[6];
int &j = x[7];
int &k = x[8];
int d, h, l, m;

bool chk[20];

int ans = 0;

void Dfs(int zz) {
    if (zz == 3 && !(a+b+c+d == E)) return;
    if (zz == 6 && !(e+f+g+h == F)) return;
    if (zz == 7 && !(a+e+i+l == A)) return;
    if (zz == 8 && !(b+f+j+m == B)) return;

    if (zz == 9) {
        if (
            C==c+g+k &&
            G==i+j+k)
        {
            ++ans;
        }

        return;
    }

    for (x[zz]=1; x[zz]<=13; ++x[zz]) if (!chk[x[zz]]) {
        chk[x[zz]] = true;
        Dfs(zz+1);
        chk[x[zz]] = false;
    }
}

int main()
{
    ios_base::sync_with_stdio(0); cin.tie(0);

    cin >> A >> B >> C >> D >> E >> F >> G >> H;

    for (d=1; d<=13; ++d) {
        chk[d] = true;

        h = D - d;
        if (1 <= h && h <= 13 && !chk[h]) {
            chk[h] = true;

            for (l=1; l<=13; ++l) if (!chk[l]) {
                chk[l] = true;

                m = H - l;
                if (1 <= m && m <= 13 && !chk[m]) {
                    chk[m] = true;
                    Dfs(0);
                    chk[m] = false;
                }

                chk[l] = false;
            }

            chk[h] = false;
        }

        chk[d] = false;
    }

    cout << ans << '\n';

    return 0;
}
