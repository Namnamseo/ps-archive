#include <bits/stdc++.h>
using namespace std;
#define sz(v) ((int)((v).size()))
#define all(v) (v).begin(), (v).end()
#define pb push_back
#define coord_comp(v) sort(all(v)), v.erase(unique(all(v)), v.end())
#define v_index(v, x) (lower_bound(all(v),x)-(v).begin())
typedef pair<int,int> pp;
typedef long long ll;
void read(int& x){ scanf("%d",&x); }
void read(ll& x){ scanf("%lld",&x); }
template<typename T1,typename T2>
void read(pair<T1,T2>& p){ read(p.first); read(p.second); }
template<typename T,typename... Args>
void read(T&a,Args&...b){ read(a); read(b...); }

int n;

const int MAX_N = 100001;

vector<pp> edge[MAX_N];
int prepare[MAX_N];
int vel[MAX_N];

typedef pair<ll,ll> pll;

struct asdf{
	vector<ll> grad, yint;
	int top;
	asdf(){ top = 0; }

	void push(ll g,ll y){
		grad.push_back(g);
		yint.push_back(y);
		++top;
	}

	void addLine(ll g,ll y){
		if(top == 0){
			push(g, y);
			return;
		}
		while(top >= 2){
			ll a=grad[top-2], b=yint[top-2];
			ll c=grad[top-1], d=yint[top-1];
			if((d-b)*(c-g) < (y-d)*(a-c)) break;
			--top;
			grad.pop_back();
			yint.pop_back();
		}
		push(g, y);
	}

	ll f(int i,int x){
		return grad[i]*x + yint[i];
	}

	ll ask(int x){
		if(top <= 3){
			ll ret=0;
			for(int i=0; i<top; ++i) ret=min(ret, f(i, x));
			return ret;
		}
		if(x*(grad[0]-grad[1]) <= yint[1]-yint[0])
			return f(0, x);
		int l=0, r=top-2;
		while(l+1 < r){
			int mid=(l+r)/2;
			if(yint[mid+1]-yint[mid] <= x*(grad[mid]-grad[mid+1]))
				l=mid;
			else
				r=mid;
		}
		return min({f(l, x), f(r, x), f(r+1, x)});
	}
};

ll dp[MAX_N];
ll depth[MAX_N];
int par[MAX_N];

int tin[MAX_N];
int tout[MAX_N];
int nt;

const int M=131072;
asdf seg[M*2];

void pre_dfs(int x){
	tin[x] = ++nt;
	for(pp& yy:edge[x]){
		int y,d; tie(y,d) = yy;
		if(par[x] == y) continue;
		par[y]=x;
		pre_dfs(y);
	}
	tout[x] = nt;
}

ll get(int pos,int x){
	pos += M;
	ll ret=0;
	while(pos){
		ret = min(ret, seg[pos].ask(x));
		pos /= 2;
	}
	return ret;
}

void rangeUpd(int l,int r,ll gra,ll yin){
	l+=M; r+=M;
	while(l<=r){
		if(l%2 == 1) seg[l++].addLine(gra, yin);
		if(r%2 == 0) seg[r--].addLine(gra, yin);
		l/=2; r/=2;
	}
}

void dfs(int x){
	dp[x] = prepare[x] + vel[x]*1LL*depth[x] + get(tin[x], vel[x]);
	rangeUpd(tin[x], tout[x], -depth[x], dp[x]);
	for(pp& yy:edge[x]){
		int y,d;
		tie(y,d) = yy;
		if(par[x] == y) continue;
		par[y]=x;
		depth[y]=depth[x]+d;
		dfs(y);
	}
}

int main(){
	scanf("%d",&n);
	for(int i=1; i<n; ++i){
		int a,b, x;
		read(a,b,x);
		edge[a].pb({b, x});
		edge[b].pb({a, x});
	}
	for(int i=2; i<=n; ++i){
		scanf("%d%d", prepare+i, vel+i);
	}
	pre_dfs(1);
	dfs(1);
	for(int i=2; i<=n; ++i)
		printf("%lld ",dp[i]);
	return 0;
}

