#include <bits/stdc++.h>
using namespace std;
using pp=pair<int,int>;
#define x first
#define y second
#define rep(i, n) for(int i=0; i<n; ++i)
#define rrep(i, n) for(int i=1; i<=n; ++i)
#define pb push_back
#define eb emplace_back

const int maxn = int(1e6) + 10;
const int root = 0;

int dp[maxn];

struct trie {
	int nxt[maxn][26];
	int fail[maxn];
	int nc = 1;

	int append(int node, char c){
		return nxt[node][c-'A'] = nc++;
	}

	int putstr(char *s){
		int p = root;
		while(*s){
			int i=(*s)-'A';
			if(!nxt[p][i]) nxt[p][i] = nc++;
			p = nxt[p][i];
			++s;
		}
		return p;
	}

	int h[maxn], hn;
	int help[maxn][26];
	void aho(){
		queue<int> q;
		rep(i, 26) if(nxt[root][i]){
			help[root][i] = nxt[root][i];
			fail[nxt[root][i]] = root;
			q.push(nxt[root][i]);
		} else help[root][i] = root;

		while(q.size()){
			int x=q.front(); q.pop();
			h[hn++] = x;
			rep(i, 26) if(nxt[x][i]){
				help[x][i] = nxt[x][i];
				int f = fail[x];
				while(f!=root && !nxt[f][i]) f=fail[f];
				if(nxt[f][i]) f=nxt[f][i];
				fail[nxt[x][i]] = f;
				q.push(nxt[x][i]);
			} else help[x][i] = help[fail[x]][i];
		}
	}

	void propa(){
		for(int i=hn-1; 0<=i; --i) dp[fail[h[i]]] += dp[h[i]];
	}
} royal, qry;

char buf[maxn];
int qwhere[maxn];
int n, q;
int ri[maxn];

void dfs(int ri, int qi){
	++dp[qi];
	rep(i, 26) if(royal.nxt[ri][i]) dfs(royal.nxt[ri][i], qry.help[qi][i]);
}

int main(){ ios_base::sync_with_stdio(0); cin.tie(0);

	cin >> n >> q;
	rrep(i, n){
		int tmp;
		cin >> buf >> tmp;
		ri[i] = royal.append(ri[tmp], buf[0]);
	}

	rrep(i, q) {
		cin >> buf;
		int l = strlen(buf);
		reverse(buf, buf+l);
		qwhere[i] = qry.putstr(buf);
	}

	qry.aho();
	dfs(root, root);
	qry.propa();

	rrep(i, q) cout << dp[qwhere[i]] << '\n';
	
	return 0;
}
