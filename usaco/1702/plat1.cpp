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

int rev[100010];

struct SEG {
	const static int M=131072;
	int tree[M<<1];
	void init(){ memset(tree, 0, sizeof(tree)); }
	void upd(int p, int v){
		p+=M; while(p) tree[p]+=v, p>>=1;
	}
	int s(int l, int r){
		int e=0;
		l+=M; r+=M;
		while(l<=r){
			if(l&1) e+=tree[l++];
			if(l&1) e+=tree[l++];
			l>>=1; r>>=1;
		}
		return e;
	}
} seg;

ll countInversion(vector<int> v){
	ll ret=0;
	seg.init();
	for(int x:v){
		ret += seg.s(x+1, n);
		seg.upd(x, 1);
	}
	return ret;
}

ll Do(vector<int> v_off, vector<int> v){
	for(int i=0; i<n; ++i) rev[v_off[i]]=i;
	for(int& x:v) x=rev[x];
	ll invs = countInversion(v);
	ll ans = invs;
	
	for(int i=0; i<n; ++i){
		if(v[i]>0) invs -= v[i];
		if(v[i]+1<n) invs += n-1-v[i];
		ans=min(ans, invs);
	}
	return ans;
}

ll DoEither(vector<int> v1, vector<int> v2){
	return min(Do(v1, v2), Do(v2, v1));
}

int main()
{
	freopen("mincross.in", "r", stdin);
	freopen("mincross.out", "w", stdout);
    read(n);
    vector<int> v1(n), v2(n);
    for(int& x:v1) read(x), --x;
    for(int& x:v2) read(x), --x;
    printf("%lld\n", DoEither(v1, v2));
    return 0;
}
