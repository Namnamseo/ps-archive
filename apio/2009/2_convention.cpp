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

const int inf = 2e9;

vector<int> xs;

int S[200010];
int E[200010];

int n;

pp d[200010];

int par[20][200010];

auto segcmp = [&](const pp& a,const pp& b){
	if(a.first != b.first) return a.first < b.first;
	return d[a.second].first < d[b.second].first;
};

const int M = 524288;
pp tree[M*2];

void upd(int pos,pp val){
	pos += M;
	while(pos){
		tree[pos] = max(tree[pos], val, segcmp);
		pos /= 2;
	}
}

pp range(int l,int r){
	l += M; r += M;
	pp ret(0, 0);
	while(l<=r){
		if(l%2 == 1) ret = max(ret, tree[l++], segcmp);
		if(r%2 == 0) ret = max(ret, tree[r--], segcmp);
		l /= 2;
		r /= 2;
	}
	return ret;
}

void in(){
	read(n);
	for(int i=1; i<=n; ++i) read(S[i], E[i]);
}

void compr(){
	xs.reserve(2*n);
	for(int i=1; i<=n; ++i){
		xs.pb(S[i]);
		xs.pb(E[i]);
	}
	coord_comp(xs);
	for(int i=1; i<=n; ++i){
		S[i] = v_index(xs, S[i])+1;
		E[i] = v_index(xs, E[i])+1;
	}
}

auto seccmp = [](const pp& a, const pp& b){
	return a.second < b.second;
};

void precalc(){
	for(int i=1; i<=n; ++i) d[i] = {S[i], E[i]};
	sort(d+1, d+n+1, seccmp);
	for(int i=1; i<=n; ++i){
		auto tt = range(0, d[i].first-1);
		par[0][i] = tt.second;
		if(0) printf("(%d,%d) picks (%d,%d)\n", d[i].first, d[i].second,
				d[tt.second].first, d[tt.second].second);
		for(int j=1; j<=18; ++j)
			par[j][i] = par[j-1][par[j-1][i]];
		upd(d[i].second, pp(tt.first + 1, i));
	}
}

int Gugan(int L,int R){
	auto tt = range(L, R);
	if(tt.first == 0) return 0;
	int x = tt.second;
	if(d[x].first < L) return 0;
	int ans = 1;
	for(int i=18; 0<=i; --i){
		if(par[i][x] && L <= d[par[i][x]].first){
			ans += (1<<i);
			x = par[i][x];
		}
	}
	//printf("Gugan %d~%d : %d\n", L, R, ans);
	return ans;
}

struct gug {
	int l, r, cnt;
	bool operator<(const gug& oth) const {
		return make_tuple(l, -r, cnt) < make_tuple(oth.l, -oth.r, oth.cnt);
	}
};

set<gug> gugan;

int main(){
	in(); compr(); precalc();

	gugan.insert({0, sz(xs), Gugan(0, sz(xs))});
	vector<int> ans;
	for(int i=1; i<=n; ++i){
		if(sz(gugan) == 0) break;
		auto it = --gugan.upper_bound({S[i], E[i], inf});
		int bL = it->l, bR = it->r;
		if(!(bL <= S[i] && E[i] <= bR)){
			continue;
		}
		int lv = Gugan(bL, S[i]-1);
		int rv = Gugan(E[i]+1, bR);
		if(lv+rv+1 != it->cnt) continue;
		ans.pb(i);
		gugan.erase(it);
		if(bL < S[i]-1){
			gugan.insert({bL, S[i]-1, lv});
		}
		if(E[i]+1 < bR){
			gugan.insert({E[i]+1, bR, rv});
		}
	}
	printf("%d\n", sz(ans));
	for(int x: ans) printf("%d ",x);
	return 0;
}

