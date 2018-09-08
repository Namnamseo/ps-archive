#include <bits/stdc++.h>
using namespace std;
typedef pair<int,int> pp;

vector<pp> links;

int n;

struct simulator {
	int deg [1000010];
	int oppo[1000010];
	bool crit;
	int R;

	void init(int rem){
		R=rem;
		for(int i=0; i<n; ++i) deg[i]=0, oppo[i]=i;
		crit=true;
		for(auto& q:links){
			update(q.first, q.second);
		}
	}

	void update(int a,int b){
		if(!crit) return;
		if(a!=R && b!=R){
			++deg[a], ++deg[b];
			int p=oppo[a], q=oppo[b];
			if(b==p){
				crit=false;
				return;
			}
			oppo[p]=q; oppo[q]=p;
			if(deg[a]>=3 || deg[b]>=3){
				crit=false;
			}
		}
	}
};

int par[1000010];
int sz [1000010];
int cyc_cnt;
int cyc_size;

int R(int x){
	return (par[x]==x)?x:(par[x]=R(par[x]));
}

void join(int a,int b){
	a=R(a); b=R(b);
	if(a == b){
		++cyc_cnt;
		cyc_size += sz[a];
	} else {
		sz[b] += sz[a];
		par[a] = b;
	}
}

void Init(int n_) {
	n=n_;
	for(int i=0; i<n; ++i) par[i]=i, sz[i]=1;
}

int first_deg[1000010];
bool isSim;

simulator ss[4];

void Link(int A, int B) {
	if(!isSim){
		++first_deg[A]; ++first_deg[B];
		links.push_back({A, B});
		join(A,B);

		int thr = -1;
		if(first_deg[A] == 3) thr = A;
		if(first_deg[B] == 3) thr = B;

		if(thr != -1){
			vector<int> inj;
			for(pp& l:links){
				int a,b; tie(a,b)=l;
				if(a==thr) inj.push_back(b);
				if(b==thr) inj.push_back(a);
			}
			ss[3].init(thr);
			for(int i=0; i<3; ++i) ss[i].init(inj[i]);
			isSim = true;
		}
	} else {
		for(int i=0; i<4; ++i)
			ss[i].update(A, B);
	}
}

int CountCritical() {
	if(!isSim){
		if(cyc_cnt >= 2)
			return 0;
		else return cyc_cnt ? cyc_size : n;
	}
	int ans=0;
	for(int i=0; i<4; ++i) if(ss[i].crit) ++ans;
	return ans;
}