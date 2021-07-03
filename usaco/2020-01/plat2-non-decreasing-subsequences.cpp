#include <bits/stdc++.h>
#include <sys/mman.h>
#include <sys/stat.h>
#include <unistd.h>
using namespace std;
typedef long long ll;
typedef pair<int,int> pp;
typedef pair<ll,ll> pll;
void cppio(){ ios_base::sync_with_stdio(0); cin.tie(0); }
template<typename T,typename U>
istream& operator>>(istream& i, pair<T,U>& p) { i >> p.first >> p.second; return i; }
#define all(x) (x).begin(),(x).end()
#define pb push_back
#define eb emplace_back
#define x first
#define y second
#define rep(i,n) for(int i = 0; i < (n); ++i)
#define rrep(i,n) for(int i = 1; i <= (n); ++i)
#define sz(x) (int)(x).size()
#define XY(t) t.x, t.y

int n, k;

const int mod = int(1e9) + 7;

inline void z(int& x) { if (x >= mod) x -= mod; }
inline void zz(int& x) { if (x < 0) x += mod; }

struct fun {
	fun *lp, *rp;
	int n, mid;
	int (*dl)[20];
	int (*dr)[20];
	void build(int *v, int n_) {
		n = n_;
		mid = n/2;

		dl = new int[mid][20];
		dr = new int[n-mid][20];

		static int tmp[20][20];

		memset(tmp, 0, sizeof(tmp));
		for(int i=mid-1; 0<=i; --i) {
			int x = v[i];
			if (i+1 < mid) copy(dl[i+1], dl[i+1]+20, dl[i]);
			for(int j=x; j<20; ++j) {
				zz(dl[i][j] -= tmp[j][x]);
				for(int k=x; k<=j; ++k) {
					z(tmp[j][x] += tmp[j][k]);
				}
				z(dl[i][j] += tmp[j][x]);
			}
			if (++tmp[x][x] == mod)
				tmp[x][x] = 0;
			if (++dl[i][x] == mod)
				dl[i][x] = 0;
		}

		memset(tmp, 0, sizeof(tmp));
		for(int i=mid, ii=0; i<n; ++i, ++ii) {
			int x = v[i];
			if (ii) copy(dr[ii-1], dr[ii-1]+20, dr[ii]);
			for(int j=0; j<=x; ++j) {
				z(dr[ii][j] += mod-tmp[j][x]);
				for(int k=x; j<=k; --k) {
					z(tmp[j][x] += tmp[j][k]);
				}
				z(dr[ii][j] += tmp[j][x]);
			}
			if (++tmp[x][x] == mod)
				tmp[x][x] = 0;
			if (++dr[ii][x] == mod)
				dr[ii][x] = 0;
		}

		if (n > 1) {
			lp = new fun(); lp->build(v, mid);
			rp = new fun(); rp->build(v+mid, n-mid);
		}
	}

	int calc(int l, int r) {
		if (r == mid-1) {
			int ans = 1;
			auto &v = dl[l];
			rep(i, 20) z(ans += v[i]);
			return ans;
		} else if (l == mid) {
			int ans = 1;
			auto &v = dr[r-mid];
			rep(i, 20) z(ans += v[i]);
			return ans;
		} else if (r < mid) return lp->calc(l, r);
		else if (mid < l) return rp->calc(l-mid, r-mid);
		int ans = 1;
		auto &vl = dl[l];
		auto &vr = dr[r-mid];
		int ls = 0;
		rep(i, 20) {
			z(ls += vl[i]);
			z(ans += ls * 1ll * vr[i] % mod);
			z(ans += vl[i]);
			z(ans += vr[i]);
		}
		return ans;
	}
} root;

char *bin;
char bout[1<<22]; int no;

inline int ri() {
	int r=0;
	while (*bin < '0' || *bin > '9') ++bin;
	while (*bin >= '0' && *bin <= '9') {
		r = r*10 + (*bin-'0'); ++bin;
	}
	return r;
}

inline void wi(int x) {
	if (!x) {
		bout[no++]='0'; bout[no++]='\n'; return;
	}
	int t = x, l = 0, ll;
	while (t) t/=10, ++l;
	t = x;
	ll = l;
	while (t) bout[no+--l]='0'+t%10, t/=10;
	bout[no+=ll]='\n'; ++no;
}

int main()
{
	fstat(0,(struct stat*)bout); bin=(char*)mmap(0,((struct stat*)bout)->st_size,PROT_READ,MAP_FILE|MAP_PRIVATE,0,0);
	int n=ri(), k=ri();
	int *v = new int[n];
	rep(i, n) v[i] = ri()-1;
	root.build(v, n);
	int q = ri();
	for(;q--;) {
		int l = ri(), r = ri();
		wi(root.calc(l-1, r-1));
	}
	write(1, bout, no);
	return 0;
}
