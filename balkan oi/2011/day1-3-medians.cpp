#include <iostream>
#include <queue>
#include <numeric>
#include <bitset>
#include <functional>
using namespace std;

const int maxn = int(2e5) + 10;

int n;
bitset<maxn> v;
int id, iu;

struct MED {
	priority_queue<int> lo;
	priority_queue<int,vector<int>,greater<int>> hi;

	void add(int x) {
		v[x] = 1;
		while (v[id]) ++id;
		while (v[iu]) --iu;

		cout << x << ' ';
		if (hi.empty() || x <= hi.top()) lo.push(x);
		else hi.push(x);

		if (hi.size() <= lo.size() && lo.size() <= hi.size()+1u) return;
		while (lo.size() > hi.size()) { hi.push(lo.top()); lo.pop(); }
		while (lo.size() < hi.size()) { lo.push(hi.top()); hi.pop(); }
	}
} med;

auto &lo = med.lo;
auto &hi = med.hi;

int main() {
	cin.tie(0)->sync_with_stdio(0);

	cin >> n; id = 1; iu = 2*n-1;
	{ int x; cin >> x; med.add(x); }
	for (int i=2; i<=n; ++i) {
		int x; cin >> x;
		if (!v[x]) {
			med.add(x);
			med.add(x == hi.top() ? iu : id);
		} else {
			med.add(lo.top() < x ? iu : id);
			med.add(lo.top() < x ? iu : id);
		}
	}

	return 0;
}
