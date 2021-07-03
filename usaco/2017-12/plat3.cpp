#include <iostream>
#include <algorithm>
#include <vector>
#include <queue>
#define rrep(i, n) for(int i=1; i<=n; ++i)
#define rep(i, n) for(int i=0; i<n; ++i)
using namespace std;
const int maxn = int(1e5) + 10;

int n;
int a[maxn];
vector<int> p[maxn];

const int M = 131072;
int t[M<<1];
void upd(int p, int v) { for (p+=M; p; p/=2) t[p] += v; }

int kth(int k) { int p = 1;
	while (p < M) {
		if (t[p*2] >= k) p*=2;
		else k-=t[p*2], p=p*2+1;
	}
	return p-M;
}

int main()
{
	ios_base::sync_with_stdio(0); cin.tie(0);
	cin >> n; if (n == 1) { cout << "0\n"; return 0; }
	rrep(i, n) (cin >> a[i]), p[a[i]].push_back(i);

	int z = n;
	for(int k=n-1; 0<=k; --k) {
		for(int x:p[k]) upd(x, +1);
		if (t[1] >= n-k) z = min(z, kth(n-k));
	}

	cout << (n-z) << endl;

	return 0;
}
