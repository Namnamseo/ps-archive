#include "game.h"
#include <cstdio>

typedef long long ll;

ll gcd2(ll a,ll b){ return b?gcd2(b,a%b):a; }
struct node {
	node *lp, *rp;
	ll val;
	int l,r;
	int sing_pos;
	
	node(int a,int b){
		l=a; r=b;
		lp=rp=0;
		val=0;
		sing_pos = -1;
	}

	void insert_val(int pos,ll v){
		if(l==r){
			val=v;
			return;
		}
		int mid=(l+r)/2;
		if(pos<=mid){
			if(!lp) lp=new node(l, mid);
			lp->update(pos, v);
		} else {
			if(!rp) rp=new node(mid+1, r);
			rp->update(pos, v);
		}
		val = 0;
		if(lp) val=gcd2(val, lp->val);
		if(rp) val=gcd2(val, rp->val);
	}

	void update(int pos,ll uv){
		if(lp==0 && rp==0){
			if(sing_pos == -1 || sing_pos == pos){
				sing_pos = pos;
				val = uv;
				return;
			} else {
				insert_val(sing_pos, val);
				insert_val(pos, uv);
			}
		} else insert_val(pos,uv);
	}
	
	ll range(int a,int b){
		if(r<a || b<l) return 0;
		if(lp==0 && rp==0 && sing_pos!=-1 && a<=sing_pos && sing_pos<=b) return val;
		if(a<=l && r<=b){
			return val;
		}
		ll ret=0;
		if(lp) ret=gcd2(ret, lp->range(a,b));
		if(rp) ret=gcd2(ret, rp->range(a,b));
		return ret;
	}
};

int n,m;

struct node2 {
	node *p;
	int l,r;
	node2 *lp, *rp;
	node2(int a,int b){
		l=a; r=b;
		p=new node(0, m-1);
		lp=0; rp=0;
	}

	void update2(int x,int y,ll val){
		if(x<l || r<x) return;
		if(l==r){
			p->update(y,val);
			return;
		}
		int mid=(l+r)/2;
		ll yv=0;
		if(x<=mid){
			if(!lp) lp=new node2(l, mid);
			lp->update2(x,y,val);
		} else {
			if(!rp) rp=new node2(mid+1, r);
			rp->update2(x,y,val);
		}
		yv=gcd2(lp?(lp->p->range(y,y)):0, rp?(rp->p->range(y,y)):0);
		p->update(y, yv);
	}

	ll range(int a,int b,int x,int y){
		if(a<=l && r<=b){
			return p->range(x,y);
		}
		if(r<a || b<l) return 0;
		ll ret=0;
		if(lp) ret=gcd2(ret, lp->range(a,b,x,y));
		if(rp) ret=gcd2(ret, rp->range(a,b,x,y));
		return ret;
	}
} *root=0;

void init(int R, int C) {
	n=R; m=C;
	root=new node2(0, n-1);
}

void update(int P, int Q, long long K) {
	root->update2(P, Q, K);
}

long long calculate(int P, int Q, int U, int V) {
	return root->range(P, U, Q, V);
}
