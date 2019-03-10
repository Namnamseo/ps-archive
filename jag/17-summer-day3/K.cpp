#include<bits/stdc++.h>
using namespace std;
using ll=long long;
#define rrep(i, n) for(int i=1; i<=n; ++i)
#define pb push_back

const ll mod = int(1e9) + 7;

const int maxn = int(1e5) + 10;

int ch[maxn][2];
int p[maxn];
int sz[maxn];

inline int wh(int i){ return ch[p[i]][1] == i; }
inline void us(int i){ sz[i] = sz[ch[i][0]] + sz[ch[i][1]] + 1; }

void pu(int x){
	if(!p[x]) return;
	int w=wh(x), P=p[x], ww=wh(P), PP=p[P];
	int b=ch[x][!w];

	if(b) p[b] = P; ch[P][w] = b;
	p[P] = x; ch[x][!w] = P;

	us(P); us(x);

	p[x] = PP; if(PP) ch[PP][ww] = x;
}

void splay(int x){
	for(;;){
		int P = p[x], PP = p[P];
		int w = wh(x), ww = wh(P);

		if(!PP){
			pu(x);
			break;
		}

		if(w == ww){
			pu(P); pu(x);
		} else {
			pu(x); pu(x);
		}
	}
}

inline int root(int x){ while(p[x]) x=p[x]; return x; }

ll prime[10000], pn;
vector<int> pi[100001];
bitset<100001> sieve;
void build_prime(){
	for(ll i=2; i<=ll(1e5); ++i){
		if(!sieve[i]){
			prime[pn++] = i;
			for(ll j=i; j<=ll(1e5); j+=i){
				sieve[j] = 1;
				pi[j].pb(i);
			}
		}
	}
}

int rightmost(int x){ while(ch[x][1]) x=ch[x][1]; return x; }

void pick(int x){
	splay(x);
	if(!ch[x][1]) return;
	int t2 = ch[x][1];
	ch[x][1] = 0; p[t2] = 0; us(x);
	int R = rightmost(t2); splay(R);
	ch[R][1] = x; p[x] = R; us(R);
}

ll ans = 1;

ll ipow(ll b, ll e){
	if(e<0) e = (-e) * (mod-2) % (mod-1);
	ll ret = 1;
	while(e){
		if(e&1) (ret*=b)%=mod;
		(b*=b)%=mod; e>>=1;
	}
	return ret;
}

multiset<int> es[100001];

void rem(ll x){
	for(int p:pi[x]){
		int c = 0;
		while(x%p == 0) x/=p, ++c;
		auto f = [&](){
			return es[p].size() ? *--es[p].end() : 0;
		};
		int bmx = f();
		es[p].erase(es[p].find(c));
		int nmx = f();
		(ans *= ipow(p, nmx - bmx)) %= mod;
	}
}

void add(ll x){
	for(int p:pi[x]){
		int c = 0;
		while(x%p == 0) x/=p, ++c;
		auto f = [&](){
			return es[p].size() ? *--es[p].end() : 0;
		};
		int bmx = f();
		es[p].insert(c);
		int nmx = f();
		(ans *= ipow(p, nmx - bmx)) %= mod;
	}
}

int main(){
	ios_base::sync_with_stdio(0); cin.tie(0);
	build_prime();

	int n, q;
	cin >> n >> q;

	rrep(i, n) sz[i] = 1;

	for(;q--;){
		int a, b; cin >> a >> b;
		
		splay(a); splay(b);

		if(root(a) == b){
			pick(a);
			splay(b);
			rem(sz[b]);

			int t2 = ch[b][1];
			ch[b][1] = 0; p[t2] = 0; us(b);

			us(b); us(t2);
			add(sz[b]); add(sz[t2]);
		} else {
			pick(a); pick(b);
			splay(a); splay(b);
			rem(sz[a]); rem(sz[b]); add(sz[a]+sz[b]);
			ch[a][1] = b; p[b] = a; us(a);
		}

		cout << ans << '\n';
	}
	return 0;
}

