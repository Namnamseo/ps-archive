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

int n;
int a[100010];

int coo[100010], cn;

const int M = 220'0000;

int tl[M];
int tr[M];
int tv[M];
int tn;

int root[100010];

void build_tree(int p, int rl, int rr){
	tl[p] = ++tn;
	tr[p] = ++tn;
	if(rl == rr) return;
	int mid=(rl+rr)/2;
	build_tree(tl[p], rl, mid);
	build_tree(tr[p], mid+1, rr);
}

int update_tree(int op, int rl, int rr, int up){
	if(rr<up || up<rl) return op;
	if(rl == rr){
		++tn;
		tv[tn]=tv[op]+1;
		return tn;
	}
	int me = ++tn, mid = (rl+rr)/2;
	tl[me] = update_tree(tl[op], rl, mid, up);
	tr[me] = update_tree(tr[op], mid+1, rr, up);
	tv[me] = tv[tl[me]] + tv[tr[me]];
	return me;
}

int rsum(int p, int rl, int rr, int ql, int qr){
	if(rr<ql || qr<rl) return 0;
	if(ql<=rl && rr<=qr) return tv[p];
	int mid=(rl+rr)/2;
	return rsum(tl[p], rl, mid, ql, qr) + rsum(tr[p], mid+1, rr, ql, qr);
}

int rect(int l, int r, int d, int u){
	if(l>r || d>u) return 0;
	return rsum(root[r], 1, n, d, u) - rsum(root[l-1], 1, n, d, u);
}

ll ans;

int vl[100010], vln;
int vr[100010], vrn;

void Work(int L, int R, int X, int Y){
	if(L>R) return;
	int mid = vl[(L+R)/2];

	ll mv = 0;
	int least=Y, most=X;

	for(int i=X; i<=Y; ++i){
		if(a[mid] <= a[vr[i]]) break;
		ll v = rect(mid+1, vr[i]-1, a[vr[i]]+1, a[mid]) + rect(mid+1, vr[i]-1, a[vr[i]], a[mid]-1);
		v = -v - 1;
		if(mv > v){
			mv = v;
			least = most = i;
		} else if(mv == v){
			most = i;
		}
	}

	ans = min(ans, mv);

	mid = (L+R)/2;
	if(mv < 0) Work(L, mid-1, X, least);
	Work(mid+1, R, most, Y);
}

void process(int l, int r){
	if(l == r) return;
	int mid = (l+r)/2;
	process(l, mid); process(mid+1, r);

	vln = vrn = 0;

	vl[vln++] = l;
	for(int i=l+1; i<=mid; ++i){
		if(a[vl[vln-1]] < a[i]) vl[vln++] = i;
	}

	vr[vrn++] = r;
	for(int i=r-1; i>mid; --i){
		if(a[vr[vrn-1]] > a[i]) vr[vrn++] = i;
	}

	reverse(vr, vr+vrn);

	Work(0, vln-1, 0, vrn-1);
}

int main()
{
	read(n);
	for(int i=1; i<=n; ++i) read(a[i]), coo[i]=a[i];
	sort(coo+1, coo+n+1);
	for(int i=1; i<=n; ++i){
		a[i] = lower_bound(coo+1, coo+n+1, a[i]) - coo;
	}

	build_tree(root[0]=1, 1, n);

	for(int i=1; i<=n; ++i) root[i] = update_tree(root[i-1], 1, n, a[i]);
	ll invs = 0;
	for(int i=2; i<=n; ++i) invs += rsum(root[i-1], 1, n, a[i]+1, n);
	if(invs == 0){
		if(unique(coo+1, coo+n+1) != coo+n+1){
			puts("0");
		} else {
			puts("1");
		}
		return 0;
	}

	process(1, n);

	printf("%lld\n", invs + ans);

	return 0;
}
