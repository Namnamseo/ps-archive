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

int n, m;

const int maxn = int(2e5) + 10;
const int maxm = int(1e5) + 10;

char T[maxn], P[maxm];

vector<pp> edge[2*maxn];

const int mod = int(1e9)+7, E = 37;
int hashT[maxn];
int hashP[maxm];
int powE[maxn];

// T[tidx .. tidx+match-1] == P[1 .. match]?
bool Check(int tidx, int match) {
    int ht = (hashT[tidx + match - 1] + (mod - hashT[tidx-1] * 1ll * powE[match] % mod)) % mod;
    int hp = hashP[match];
    return hp == ht;
}

void Hashify(char *s, int *out) {
    for (int i=1; s[i]; ++i) {
        out[i] = (out[i-1] * 1ll * E + (s[i] - 'a' + 1)) % mod;
    }
}

int main()
{
    ios_base::sync_with_stdio(0); cin.tie(0);
    cin >> m >> n >> (P+1) >> (T+1);

    if (n < m) {
        cout << n << '\n';
        return 0;
    }

    powE[0] = 1; for (int i=1; i<=n; ++i) powE[i] = powE[i-1] * 1ll * E % mod;
    Hashify(P, hashP);
    Hashify(T, hashT);

    for (int i=1; i<=n; ++i) {
        int ml = 0, mr = min(m, n-i+1)+1;
        while (ml + 1 < mr) {
            int mid = (ml+mr)/2;
            (Check(i, mid) ? ml : mr) = mid;
        }
        int match = ml;

        if (match == m) {
            // exit
            edge[2*(i-1)+1].eb(2*(i+match-1), m-match);
        } else if (match) {
            // jump
            edge[2*(i-1)+1].eb(2*(i+match-1)+1, m-match);
        }
    }

    for (int i=0; i<=n; ++i) {
        // jumping in
        edge[2*i].eb(2*i+1, 0);
    }

    for (int i=1; i<=n; ++i) {
        // coming back
        // Although it might not be able to match a prefix,
        // using this edge in that case would be a loss.
        edge[2*i+1].eb(2*(i-1)+1, 1);

        // plain next
        edge[2*(i-1)].eb(2*i, 1);
    }

    const int TV = 2*n + 1, SV = 0;

    priority_queue<pp> pq;
    static int dist[2*maxn];
    fill(dist, dist+TV+1, int(1e9));

    dist[SV] = 0; pq.emplace(0, SV);

    while (pq.size()) {
        auto [mdist, x] = pq.top(); pq.pop();
        if (dist[x] != -mdist) continue;

        for (auto [y, d]: edge[x]) {
            int nd = -mdist + d;
            if (dist[y] > nd) {
                dist[y] = nd;
                pq.emplace(-nd, y);
            }
        }
    }

    cout << dist[2*n] << '\n';

    return 0;
}
