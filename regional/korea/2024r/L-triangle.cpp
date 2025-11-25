#include <algorithm>
#include <iostream>
#include <numeric>
#include <string>
#include <tuple>
#include <utility>
#include <vector>
#include <queue>
using namespace std;
using ll=long long;
using pp=pair<int,int>;
#define rep(i, n) for (int i=0; i<n; ++i)
#define rrep(i, n) for (int i=1; i<=n; ++i)
#define all(v) v.begin(), v.end()
#define eb emplace_back
#define pb push_back
#define x first
#define y second

using pt=pair<ll,ll>;

ll gcd(ll a, ll b) {
    return b ? gcd(b, a%b) : a;
}

pt coprime(pt v) {
    if (v.x == 0) return {0, v.y / abs(v.y)};
    if (v.y == 0) return {v.x / abs(v.x), 0};
    ll g = gcd(abs(v.x), abs(v.y));
    if (g == 1) {
        cout << "-1\n";
        exit(0);
    }
    return {v.x/g, v.y/g};
}

pt operator+(pt a, pt b) { return {a.x+b.x, a.y+b.y}; }
pt operator-(pt a, pt b) { return {a.x-b.x, a.y-b.y}; }
pt operator-(pt b) { return {-b.x, -b.y}; }

ll tri2(pt a, pt b, pt c) {
    b = b-a; c = c-a;
    return abs(
        b.x*c.y - b.y*c.x
    );
}

int main()
{
    ios_base::sync_with_stdio(0); cin.tie(0);

    pt a, b, c;
    cin >> a.x >> a.y;
    cin >> b.x >> b.y;
    cin >> c.x >> c.y;

    pt vab = coprime(b-a);
    pt vbc = coprime(c-b);
    pt vca = coprime(a-c);

    vector<ll> areas;
    for (auto pa: {a+vab, b-vab})
    for (auto pb: {b+vbc, c-vbc})
    for (auto pc: {c+vca, a-vca}) {
        areas.pb(tri2(pa, pb, pc));
    }

    cout << *max_element(all(areas)) << ' '
         << *min_element(all(areas)) << '\n';

    return 0;
}

