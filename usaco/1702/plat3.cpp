#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef pair<int,int> pp;
void read(int& x){ scanf("%d",&x); }
template<typename T,typename... Args>
void read(T& a,Args&... b){ read(a); read(b...); }
#define all(x) (x).begin(),(x).end()
#define pb push_back

int n;

struct SEG2D {
	static const int M=131072;
	vector<int> xp[M<<1];
	vector<int> tr[M<<1];
	void preap(int x, int y){
		x+=M;
		while(x) xp[x].pb(y), x>>=1;
	}
	void init(){
		for(int i=0; i<2*M; ++i){
			sort(all(xp[i]));
			tr[i].resize(xp[i].size());
		}
	}
	void add(vector<int>& xp, vector<int>& tr, int y, int v){
		int p=lower_bound(all(xp), y)-xp.begin();
		if(p == 0){
			tr[p] += v; return;
		}
		while(p < tr.size()) tr[p]+=v, p+=(p&(-p));
	}
	void ap(int x, int y, int v){
		x+=M;
		while(x) add(xp[x], tr[x], y, v), x>>=1;
	}
	int get(vector<int>& xp, vector<int>& tr, int s){
		int ret=tr[0];
		while(s) ret+=tr[s], s&=(s-1);
		return ret;
	}
	int get(vector<int>& xp, vector<int>& tr, int d, int u){
		int l=lower_bound(all(xp), d)-xp.begin();
		int r=upper_bound(all(xp), u)-xp.begin()-1;
		if(r<l) return 0;
		int ret=get(xp, tr, r);
		if(l) ret-=get(xp, tr, l-1);
		return ret;
	}
	int rs(int l, int r, int d, int u){
		l+=M; r+=M;
		int ret=0;
		while(l<=r){
			if(l&1) ret+=get(xp[l], tr[l], d, u), ++l;
			if((r&1)==0) ret+=get(xp[r], tr[r], d, u), --r;
			l>>=1; r>>=1;
		}
		return ret;
	}
} seg2d;

int v1[100010];
int v2[100010];

int tree[100010];
void upd(int p, int v){
	while(p<=100000) tree[p]+=v, p+=(p&(-p));
}
int s(int p){
	int ret=0;
	while(p) ret+=tree[p], p&=(p-1);
	return ret;
}
int vi[100010];
ll countInversion(){
	for(int i=0; i<n; ++i)
		vi[v2[i]]=v1[i]+1;
	ll ret=0;
	for(int i=0; i<n; ++i){
		ret += s(n)-s(vi[i]);
		upd(vi[i], 1);
	}
	return ret;
}

int buf[100010];

int main()
{
	freopen("friendcross.in", "r", stdin);
	freopen("friendcross.out", "w", stdout);
    int k;
    read(n, k);
    for(int i=0; i<n; ++i) read(buf[i]);
    for(int i=0; i<n; ++i) v1[buf[i]-1]=i;
    
	for(int i=0; i<n; ++i) read(buf[i]);
    for(int i=0; i<n; ++i) v2[buf[i]-1]=i;
    ll invs = countInversion();
    
    for(int i=0; i<n; ++i) seg2d.preap(v1[i], v2[i]);
    seg2d.init();
    
    for(int i=0; i<n; ++i){
		invs -= seg2d.rs(0, v1[i], v2[i], n-1);
		invs -= seg2d.rs(v1[i], n-1, 0, v2[i]);
		seg2d.ap(v1[i], v2[i], 1);
		if(i-k>=0)
			seg2d.ap(v1[i-k], v2[i-k], -1);
    }
    printf("%lld\n", invs);
    return 0;
}
