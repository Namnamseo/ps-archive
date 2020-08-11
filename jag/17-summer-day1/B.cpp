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

int x[300010];

struct Node {
	Node *lp, *rp;
	int sz;
	int val;
	Node(int l, int r){
		sz=r-l+1;
		if(l == r){
			lp=0; rp=0;
		} else {
			int mid=(l+r)/2;
			lp=new Node(l, mid);
			rp=new Node(mid+1, r);
		}
	}
	void put(int t, int l, int r, int i){
		if(l == r){
			val = i;
			sz = 0;
			return;
		}
		int mid=(l+r)/2;
		if(t >= rp->sz){
			lp->put(t-rp->sz, l, mid, i);
		} else {
			rp->put(t, mid+1, r, i);
		}
		sz=lp->sz + rp->sz;
	}
	void dfs(int l, int r){
		if(l == r){
			x[l] = val;
			return;
		}
		int mid=(l+r)/2;
		lp->dfs(l, mid);
		rp->dfs(mid+1, r);
	}
} *root;

int a[300010];
int n;

int last[300010];
int len;

int main()
{
	read(n);
	for(int i=1; i<=n; ++i) read(a[i]);
	root = new Node(1, n);
	for(int i=n; 1<=i; --i) root->put(a[i], 1, n, i);
	root->dfs(1, n);
	len = 1; last[1] = x[1];
	for(int i=2; i<=n; ++i){
		int l=0, r=len+1;
		while(l+1<r){
			int mid=(l+r)/2;
			if(last[mid]<=x[i]) l=mid;
			else r=mid;
		}
		last[r]=x[i];
		len=max(len, r);
	}
	printf("%d\n", len);
	return 0;
}

