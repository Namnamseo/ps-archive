#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef pair<int,int> pp;
typedef pair<ll,ll> pll;
void read(int& x){ scanf("%d",&x); }
void read(ll& x){ scanf("%lld",&x); }
void read(pp& x){ scanf("%d%d",&x.first, &x.second); }
void read(pll& x){ scanf("%lld%lld",&x.first, &x.second); }
template<typename T,typename... Args>
void read(T& a,Args&... b){ read(a); read(b...); }
#define all(x) (x).begin(),(x).end()
#define pb push_back
#define eb emplace_back
#define x first
#define y second
#define rep(i,n) for(int i = 0; i < (n); ++i)
#define rrep(i,n) for(int i = 1; i <= (n); ++i)
#define sz(x) (int)(x).size()

char s[100010];
int n;
ll k;

pp p[100010];
int pn;

int dx, dy;

bool exist(int x, int y){
	pp t{x, y};
	int k=lower_bound(p, p+pn, t)-p;
	return 0 <= k && k < pn && p[k] == t;
}

typedef tuple<ll,int,int> t3;

map<t3, int> group;
int gn;
ll gl[100010];
int gx[100010], gy[100010];
set<pp> gug[100010];

int Mod(int n, int r){
	r = max(1, abs(r));
	return (n%r+r)%r;
}

pp get_grp(ll x, ll y, bool make=true){
	ll lv = dx*1ll*y - dy*1ll*x;
	int mx = Mod(x, dx), my = Mod(y, dy);
	auto tpl = make_tuple(lv, mx, my);
	auto it = group.find(tpl);
	if(it != group.end()){
		return {it->second, dx ? (x-mx)/abs(dx) : (y-my)/abs(dy)};
	}
	if(!make) return {-1, -1};
	group[tpl] = ++gn;
	gl[gn] = lv; gx[gn] = x; gy[gn] = y;

	return {gn, dx ? (x-mx)/abs(dx) : (y-my)/abs(dy)};
}

void gi(set<pp>& s, int l, int r){
	auto it = s.insert(pp{l, r}).first;
	if(it != s.begin()) --it;
	auto mrg = [&](){
		while(true){
			auto it2 = it;
			++it2;
			if(it2 == s.end()) break;
			if(it->y+1 < it2->x) break;
			pp tmp{it->x, it2->y};
			s.erase(it); s.erase(it2);
			it = s.insert(tmp).first;
		}
	};
	mrg();
	++it;
	if(it != s.end()) mrg();
}

ll Count(set<pp>& s){
	ll ret = 0;
	for(auto& tmp:s) ret += tmp.y - tmp.x + 1;
	return ret;
}

int main()
{
	read(n, k); scanf("%s", s+1);
	rrep(i, n){
		if(s[i]=='N') ++dy;
		else if(s[i]=='E') ++dx;
		else if(s[i]=='S') --dy;
		else if(s[i]=='W') --dx;
		p[i]={dx, dy};
	}
	sort(p, p+n+1);
	pn = unique(p, p+n+1)-p;

	if(dx==0 && dy==0){
		int ans = 0;
		rep(i, pn){
			int x, y; tie(x, y) = p[i];
			if(exist(x+1, y) && exist(x, y+1) && exist(x+1, y+1)) ++ans;
		}
		printf("%d\n", ans);
		return 0;
	}

	rep(i, pn){
		int x, y; tie(x, y) = p[i];
		int grp, df; tie(grp, df) = get_grp(x, y);
		gi(gug[grp], df, df+k-1);
	}

	printf("%d\n", gn);
	ll ans = 0;
	rrep(i, gn){
		set<pp> G = gug[i];
		int x=gx[i], y=gy[i];
		int myir = get_grp(x, y).second;
		printf("Group [%2d] of x %d y %d, line value %lld: ", i, x, y, gl[i]);
		for(auto& tmp:G) printf("[%d, %d], ", tmp.x, tmp.y);
		putchar(10);
		auto add = [&](int qx, int qy){
			int X = (x+qx), Y = (y+qy);
			int tg, ir;
			tie(tg, ir) = get_grp(X, Y, false);
			ir -= myir;
			printf("    adj. %d %d tg=%d, ir=%d: ", X-x, Y-y, tg, ir);
			if(tg != -1) for(auto& tmp:gug[tg]) printf("[%d, %d], ", tmp.x-ir, tmp.y-ir);
			putchar(10);
			if(tg == -1){
				G.clear();
				return;
			}
			set<pp> tmp;

			auto &S1 = G, &S2 = gug[tg];
			auto i1 = G.begin(), i2 = gug[tg].begin();
			while(i1 != S1.end() && i2 != S2.end()){
				int zl=max(i1->x, i2->x-ir);
				int zr=min(i1->y, i2->y-ir);
				if(zl <= zr) tmp.emplace(zl, zr);
				if(i1->y < i2->y-ir) ++i1;
				else ++i2;
			}

			swap(G, tmp);
			printf("        -> merge: ");
			for(auto& tmp:G) printf("[%d, %d], ", tmp.x, tmp.y); putchar(10);
		};
		add(1, 0);
		add(0, 1);
		add(1, 1);
		printf("  count: %lld\n", Count(G));
		putchar(10);
		ans += Count(G);
	}

	printf("%lld\n", ans);
	return 0;
}
