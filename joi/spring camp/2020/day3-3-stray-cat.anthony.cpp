#include "Anthony.h"
#include <bitset>
#include <vector>
using namespace std;
using vi=vector<int>;

namespace {
const int maxn = int(2e4) + 10;

int n;

struct Edge { int l, r; } ev[maxn];
vector<int> es[maxn];
int lev[maxn];
int col[maxn];

void bfs() {
    static int q[maxn];
    static bitset<maxn> vis;
    int f = 0, t = 1; vis.set(0);
    while (f < t) {
        int x = q[f++];
        for (int ei : es[x]) {
            int y = ev[ei].l + ev[ei].r - x;
            if (vis[y]) continue;
            vis.set(y);
            lev[y] = lev[x]+1;
            q[t++] = y;
        }
    }
}

void Read(int N, int M, vi &U, vi &V) {
    n = N;
    for (int i=0; i<M; ++i) {
        ev[i] = {U[i], V[i]};
        es[U[i]].push_back(i);
        es[V[i]].push_back(i);
    }
}

vi Case1(int N, int M, vi &U, vi &V) {
    Read(N, M, U, V);
    bfs();

    for (int i=0; i<M; ++i) {
        int a = ev[i].l, b = ev[i].r;
        col[i] = min(lev[a], lev[b])%3;
    }
    return vi(col, col+M);
}

const int dict[6] = {0, 1, 1, 0, 0, 1};
void Go(int x, int p, int state) {
    if (es[x].size() == 1u) return;
    if (es[x].size() > 2u) {
        int pc = dict[(state+5)%6];
        for (int ei : es[x]) {
            int y = ev[ei].l + ev[ei].r - x;
            if (y == p) continue;
            col[ei] = pc^1;
            Go(y, x, 1+(pc^1));
        }
        return;
    }

    for (int ei : es[x]) {
        int y = ev[ei].l + ev[ei].r - x;
        if (y == p) continue;
        col[ei] = dict[state];
        Go(y, x, (state+1)%6);
    }
}

vi Case2(int N, int M, vi &U, vi &V) {
    Read(N, M, U, V);
    for (int ei : es[0]) {
        int y = ev[ei].l + ev[ei].r;
        Go(y, 0, 1);
    }
    return vi(col, col+M);
}

}  // namespace

namespace {
}  // namespace

vi Mark(int N, int M, int A, int B, vi U, vi V) {
    if (B == 0)
        return Case1(N, M, U, V);
    else
        return Case2(N, M, U, V);
}
