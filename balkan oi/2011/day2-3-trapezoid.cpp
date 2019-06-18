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

struct trap {
	int a,b,c,d;
} t[100001];

inline pp combine(pp a,pp b){
	if(a.first < b.first) return b;
	else if(a.first > b.first) return a;
	else return {a.first, (a.second + b.second)%30013};
}

inline void put(pp& a,pp b){
	a=combine(a,b);
}

priority_queue<pp> pq;

vector<int> ux, dx;

const int M=262144;
pp tree[M*2];

void upd(int pos,pp val){
	pos+=M;
	put(tree[pos], val);
	pos /= 2;
	while(pos)
		tree[pos]=combine(tree[pos*2], tree[pos*2+1]),
		pos/=2;
}

pp range(int l,int r){
	l += M; r += M;
	pp ret(0,0);
	while(l<=r){
		if(l%2 == 1) put(ret, tree[l++]);
		if(r%2 == 0) put(ret, tree[r--]);
		l/=2; r/=2;
	}
	return ret;
}

pp dp[100010];

int main(){
	read(n);
	for(int i=1; i<=n; ++i){
		trap& a=t[i];
		read(a.a, a.b, a.c, a.d);
		ux.pb(a.a);
		ux.pb(a.b);
		dx.pb(a.c);
		dx.pb(a.d);
	}
	coord_comp(ux);
	coord_comp(dx);
	for(int i=1; i<=n; ++i){
		trap& a=t[i];
		a.a = v_index(ux, a.a);
		a.b = v_index(ux, a.b);
		a.c = v_index(dx, a.c);
		a.d = v_index(dx, a.d);
	}

	sort(t+1, t+n+1, [](const trap& a, const trap& b){
		return a.b < b.b;
	});

	pp ans(0,0);
	for(int i=n; 1<=i; --i){
		while(pq.size()){
			if(pq.top().first <= t[i].b) break;
			int x = pq.top().second;
			upd(t[x].c, dp[x]);
			pq.pop();
		}
		dp[i] = range(t[i].d+1, 262143);
		dp[i].first += 1;
		put(dp[i], pp(1,1));
		put(ans, dp[i]);
		pq.push({t[i].a, i});
	}

	printf("%d %d\n", ans.first, ans.second);
	return 0;
}

