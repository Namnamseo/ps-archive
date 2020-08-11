#include <bits/stdc++.h>
using namespace std;

int n, m;
const int maxn = 1e4;
int s[maxn];
char buf[1010];

int main()
{
	ios_base::sync_with_stdio(0); cin.tie(0);
	cin >> n >> m;
	for(int i=0; i<n; ++i) {
		cin >> buf;
		int t = 0;
		for(int j=0; buf[j]; ++j) {
			t |= (1 << (buf[j] - 'a'));
		}
		s[i] = t;
	}

	int c = 0;
	for(;m--;) {
		int cmd; char dat[3];
		cin >> cmd >> dat;
		int v = 1 << (dat[0] - 'a');
		if (cmd == 1) c |= v;
		else c &= ~v;
		int ret = n;
		for(int i=0; i<n; ++i) ret -= !!(s[i] & c);
		cout << ret << '\n';
	}

	return 0;
}
