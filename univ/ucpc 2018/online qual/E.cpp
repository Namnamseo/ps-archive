#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef pair<int,int> pp;
typedef pair<ll,ll> pll;
void read(int& x){ scanf("%d",&x); }
void read(ll& x){ scanf("%lld",&x); }
template<typename T,typename... Args>
void read(T& a,Args&... b){ read(a); read(b...); }
#define all(x) (x).begin(),(x).end()
#define pb push_back
#define eb emplace_back
#define x first
#define y second

pp Q[1'000'010];
int head, tail;

const int M=524288;

int lazy[M<<1];
int tree[M<<1];

inline void pd(int p, int l, int r){
	if(l == r) return;
	if(lazy[p] < 0){
		lazy[p*2] = -1; tree[p*2] = 0;
		lazy[p*2+1] = -1; tree[p*2+1] = 0;
		lazy[p] = 0;
	} else if(lazy[p] > 0){
		lazy[p*2] = tree[p*2] = lazy[p];
		lazy[p*2+1] = tree[p*2+1] = lazy[p];
		lazy[p] = 0;
	}
}

int Get(int p, int l, int r, int q){
	if(l == r) return tree[p];
	pd(p, l, r);
	int mid = (l+r)/2;
	if(q <= mid) return Get(p*2, l, mid, q);
	else return Get(p*2+1, mid+1, r, q);
}

void Clear(int p, int l, int r, int ul, int ur){
	pd(p, l, r);
	if(r < ul || ur < l) return;
	if(ul <= l && r <= ur){
		lazy[p] = -1; tree[p] = 0;
		return;
	}
	int mid = (l+r)/2;
	Clear(p*2, l, mid, ul, ur);
	Clear(p*2+1, mid+1, r, ul, ur);
}

void Set(int p, int l, int r, int ul, int ur, int uv){
	pd(p, l, r);
	if(r < ul || ur < l) return;
	if(ul <= l && r <= ur){
		lazy[p] = tree[p] = uv;
		return;
	}
	int mid = (l+r)/2;
	Set(p*2, l, mid, ul, ur, uv);
	Set(p*2+1, mid+1, r, ul, ur, uv);
}

int n, m, k, q;

inline void Push(int type, int cnt){
	Q[tail++] = {type, cnt};
}

inline void Enqueue(int sp, int gap){
	while(gap && head < tail){
		int num = min(Q[head].y, gap);
		Set(1, 1, m, sp, sp + num - 1, Q[head].x);
		Q[head].y -= num; gap -= num;
		sp += num;
		if(Q[head].y == 0) ++head;
	}
}

void Expand(int p, int l, int r){
	if(l == r){
		printf("%d ", tree[p]);
		return;
	}
	pd(p, l, r);
	int mid = (l+r)/2;
	Expand(p*2, l, mid); Expand(p*2+1, mid+1, r);
}

int main()
{
	read(n, m, k, q);
	for(int i=1; i<=n; ++i){
		int a; read(a); Push(a, 1);
	}
	Enqueue(1, m);
	for(;q--;){
		int com; read(com);
		if(com == 1){
			int L, R; read(L, R);
			Clear(1, 1, m, L, R);
			Enqueue(L, R-L+1);
		} else if(com == 2){
			int i; read(i);
			printf("%d ", Get(1, 1, m, i));
		} else if(com == 3){
			int p, q; read(p, q);
			Push(p, q);
		} else {
			ll t; read(t);
			while(t && head < tail){
				ll num = min(ll(Q[head].y), t);
				t -= num; Q[head].y -= num;
				if(Q[head].y == 0) ++head;
			}
		}
	}
	putchar(10);
	Expand(1, 1, m);
	return 0;
}
