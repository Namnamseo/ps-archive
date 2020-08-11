#include <bits/stdc++.h>
using namespace std;

int n;

int parse() {
	static char buf[10];
	cin >> buf;
	int ret = 0;
	for(int i=0; buf[i]; ++i)
		ret = ret*2 + (buf[i]-'0');
	return ret;
}

int d[10000];
const int inf = 1e9;

int main(){
    ios_base::sync_with_stdio(0); cin.tie(0);
    int S = parse();
    int E = parse();

    fill(d, d+10000, inf);
    d[S] = 0;

    queue<int> q;
    q.push(S);

    while(q.size()) {
    	int x = q.front(); q.pop();
    	if(x == E) {
    		cout << d[E] << endl;
    		return 0;
		}

    	auto relax = [&](int y) {
    		if (y<0 || y>=10000) return;

    		if (d[y] > d[x]+1) {
    			d[y] = d[x]+1;
    			q.push(y);
			}
		};

    	for(int i=30; 0<=i; --i) if(1&(x>>i)) {
    		for(int j=0; j<i; ++j) {
    			relax(x ^ (1ll<<j));
			}
		}

		relax(x+1);
		relax(x-1);
	}
    return 0;
}
