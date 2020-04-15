#include <bits/stdc++.h>
using namespace std;
#define pb push_back

int n;

vector<int> e[3'000'010];

char buf[500'010];

int nxt[1'000'010][2];
const int root = 1;
int nn = 1;
vector<int> term[1'000'010];

int tn;
int mn;

inline int Not(int x){ return x^1; }

void imply(int a, int b){
	e[a].pb(b);
	e[Not(b)].pb(Not(a));
}

void dfs(int p){
	int pmn = mn;

	for(int x:term[p]){
		if(mn != -1) imply(x, Not(mn)), imply(mn, tn);
		imply(x, tn);
		mn = tn;
		tn += 2;
	}

	for(int n=0; n<2; ++n) if(nxt[p][n]){
		dfs(nxt[p][n]);
	}

	mn = pmn;
}

int idx[3'000'010];
int low[3'000'010];
int stk[3'000'010], top;
bool on[3'000'010];
int myc[3'000'010], cn;

void td(int x){
	static int nt = 0;
	idx[x] = low[x] = ++nt;
	stk[top++] = x; on[x] = 1;

	for(int y:e[x]){
		if(!idx[y]){
			td(y);
			low[x] = min(low[x], low[y]);
		} else if(on[y]) low[x] = min(low[x], idx[y]);
	}

	if(idx[x] == low[x]){
		++cn;
		for(;top--;){
			int a = stk[top];
			on[a] = 0; myc[a] = cn;
			if(a == x) break;
		}
	}
}

vector<string> S;

int main(){
	scanf("%d", &n); S.reserve(n);

	for(int i=0; i<n; ++i){
		scanf("%s", buf);
		S.emplace_back(buf);

		for(int q=0; q<2; ++q){
			int p = root;

			for(int j=0; buf[j]; ++j){
				int& t = nxt[p][((buf[j] == '?') ? q : (buf[j]-'0'))];
				if(!t) t = ++nn;
				p = t;
			}

			term[p].pb(2*i + q);
		}
	}

	tn = 2*n;
	mn = -1;
	dfs(root);

	for(int i=0; i<tn; ++i) if(!idx[i]) td(i);

	for(int i=0; i<n; ++i){
		if(myc[i*2] == myc[i*2+1]){
			puts("NO");
			return 0;
		}
	}

	puts("YES");
	for(int i=0; i<n; ++i){
		string& s = S[i];
		for(int j=0; s[j]; ++j){
			if(s[j] == '?'){
				if(myc[i*2] > myc[i*2+1]){
					putchar('1');
				} else {
					putchar('0');
				}
			} else putchar(s[j]);
		}
		putchar(10);
	}
	return 0;
}

