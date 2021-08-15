#include <algorithm>
#include <iostream>
using namespace std;
using pp=pair<int,int>;
#define x first
#define y second
const int maxn = int(5e5) + 10;

int budget[2];

int n, m;
char _buf[2][maxn], *p1=_buf[0], *p2=_buf[1];
pp bounds[maxn];
void Board() {
	cin >> n >> m >> p1 >> p2;
	if (p1[0] == 'D') swap(p1, p2);

	for (int i=0, x=0, y=0; p1[i]; ++i) {
		if (p1[i] == 'R') ++y;
		else { ++x; bounds[x].y = y; }
	}

	for (int i=0, x=0, y=0; p2[i]; ++i) {
		if (p2[i] == 'R') ++y;
		else { ++x; bounds[x].x = y+1; }
	}

	int d = n, r = m;
	while (d>1 && r>1) {
		--d; --r;
		r = min(r, bounds[d].y);
		while (1 < d && r < bounds[d].x) --d;
	}
	budget[0] += d-1;
	budget[1] += r-1;
}

int main() { cin.tie(0)->sync_with_stdio(0);
	int k; cin >> k;
	for(;k--;) Board();
	cout << ((budget[1] > budget[0]) ? "First" : "Second") << '\n';
	return 0;
}
