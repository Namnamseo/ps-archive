#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef pair<int,int> pp;
void read(int& x){ scanf("%d",&x); }
template<typename T,typename... Args>
void read(T& a,Args&... b){ read(a); read(b...); }
#define all(x) (x).begin(),(x).end()
#define pb push_back

#define x first
#define y second

vector<pp> kpt;
ll inf = 1LL << 60;
int kn, qn;

pp operator-(pp a, pp b){
	return pp{a.first-b.first, a.second-b.second};
}

ll cross(pp a, pp b){
	return b.y*1LL*a.x - b.x*1LL*a.y;
}

ll cross(pp a, pp b, pp c){ return cross(b-a, c-a); }

void in(){
    int k;
    read(k, qn); kpt.resize(k);
    for(auto& tmp:kpt){
		int a,b; read(a,b); tmp={a, b};
    }
}

void soka(){
    sort(all(kpt), [&](const pp& a, const pp& b){
		ll tmp=cross(a, b);
		if(tmp != 0) return tmp > 0;
		return a.x < b.x;
	});
    kpt.erase(unique(all(kpt), [&](const pp& a, const pp& b){
		return cross(a, b) == 0LL;
	}), kpt.end());
	kn = kpt.size();
}

struct hside {
	vector<pp> pts;
	int n;
	ll min_jub(pp grad){
		int l=0, r=n-1;
		while(l+3 < r){
			int p1=(l*2+r)/3;
			int p2=(l+2*r)/3;
			ll v1=(-grad.y)*1LL*pts[p1].x + grad.x*1LL*pts[p1].y;
			ll v2=(-grad.y)*1LL*pts[p2].x + grad.x*1LL*pts[p2].y;
			if(v1 > v2) l=p1; else r=p2;
		}
		ll ret=inf;
		for(int i=l; i<=r; ++i){
			auto& tmp=pts[i];
			ret=min(ret, (-grad.y)*1LL*tmp.x + grad.x*1LL*tmp.y);
		}
		return ret;
	}
};

struct hull {
	vector<pp> pt;
	void add_pt(pp& x){ pt.pb(x); }
	hside uh, dh;
	void build(){
		sort(all(pt));
		vector<pp>& uv=uh.pts; int& un=uh.n;
		vector<pp>& dv=dh.pts; int& dn=dh.n;
		un=0;
		for(pp& tmp:pt){
			while(un >= 2 && cross(uv[un-2], uv[un-1], tmp)>=0) uv.pop_back(), --un;
			uv.pb(tmp); ++un;
		}
		reverse(all(pt));
		dn=0;
		for(pp& tmp:pt){
			while(dn >= 2 && cross(dv[dn-2], dv[dn-1], tmp)>=0) dv.pop_back(), --dn;
			dv.pb(tmp); ++dn;
		}
		pt.clear();
	}
	ll min_jub(pp grad){
		return dh.min_jub(grad);
	}
};

struct hnode {
	hull h;
	hnode *lp, *rp;
	int l, r;
	hnode(int a, int b){
		l=a; r=b;
		for(int i=l; i<=r; ++i) h.add_pt(kpt[i]);
		h.build();
		if(l != r){
			int mid=(l+r)/2;
			lp=new hnode(l, mid);
			rp=new hnode(mid+1, r);
		}
	}
	
	ll min_jub(int ql, int qr, pp grad){
		if(ql <= l && r <= qr) return h.min_jub(grad);
		else if(r<ql || qr<l) return inf;
		return min(lp->min_jub(ql, qr, grad), rp->min_jub(ql, qr, grad));
	}
} *root;

auto ccw = [](pp a, pp b){ return cross(a, b) > 0; };

int main() {
	in();
	soka();
	root = new hnode(0, kn-1);
	for(;qn--;){
		pp a, b; read(a.x, a.y); read(b.x, b.y);
		if(ccw(b, a)) swap(a, b);
		int pl = upper_bound(all(kpt), a, ccw) - kpt.begin();
		int pr = lower_bound(all(kpt), b, ccw) - kpt.begin();
		if(pl == pr){
			puts("N"); continue;
		}
		pp grad = a-b;
		ll cur = (-grad.y)*1LL*b.x + (grad.x)*1LL*b.y;
		if(root->min_jub(pl, pr-1, grad) > cur) puts("N");
		else puts("Y");
	}
    return 0;
}

