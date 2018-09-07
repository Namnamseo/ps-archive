#include <bits/stdc++.h>
using namespace std;

int n, h, w;
int z;

const int M = 1048576;
int tree[M<<1];
int lazy[M<<1];
int cmn[M<<1];

int iv[int(1e6)+10];

inline void pd(int p){
	if(!lazy[p]) return;
	for(int c=p*2; c<=p*2+1; ++c){
		tree[c] += lazy[p];
		lazy[c] += lazy[p];
	}
	lazy[p]=0;
}

inline void gather(int p){
	if(tree[p*2] == tree[p*2+1]){
		tree[p] = tree[p*2];
		cmn[p] = cmn[p*2]+cmn[p*2+1];
	} else if(tree[p*2] > tree[p*2+1]){
		tree[p] = tree[p*2+1];
		cmn[p] = cmn[p*2+1];
	} else {
		tree[p] = tree[p*2];
		cmn[p] = cmn[p*2];
	}
}

void init(int p=1, int l=1, int r=n){
	if(l==r){
		tree[p]=iv[l];
		cmn[p]=1;
		return;
	}
	int mid=(l+r)/2;
	init(p*2, l, mid);
	init(p*2+1, mid+1, r);
	gather(p);
}

void upd(int l, int r, int v, int mp=1, int ml=1, int mr=n){
	if(r<ml || mr<l) return;
	if(ml!=mr) pd(mp);
	if(l<=ml && mr<=r){
		tree[mp] += v;
		lazy[mp] += v;
		return;
	}
	int mid=(ml+mr)/2;
	upd(l,r,v, mp*2, ml, mid);
	upd(l,r,v, mp*2+1, mid+1, mr);
	gather(mp);
}

inline void addr(int x, int y){
	if(x>=y) return;
	upd(x, y-1, 1);
}

inline void delr(int x, int y){
	if(x>=y) return;
	upd(x, y-1, -1);
}

int Arr[3*int(1e6)+10];

int arr[4];
inline void add(int x, int y){
	arr[0]=Arr[x*z+y]; if(!arr[0]) arr[0]=1e9;
	arr[1]=Arr[x*z+y+1]; if(!arr[1]) arr[1]=1e9;
	arr[2]=Arr[(x+1)*z+y]; if(!arr[2]) arr[2]=1e9;
	arr[3]=Arr[(x+1)*z+y+1]; if(!arr[3]) arr[3]=1e9;
	sort(arr, arr+4);
	addr(arr[0], arr[1]);
	addr(arr[2], arr[3]);
}

inline void del(int x, int y){
	arr[0]=Arr[x*z+y]; if(!arr[0]) arr[0]=1e9;
	arr[1]=Arr[x*z+y+1]; if(!arr[1]) arr[1]=1e9;
	arr[2]=Arr[(x+1)*z+y]; if(!arr[2]) arr[2]=1e9;
	arr[3]=Arr[(x+1)*z+y+1]; if(!arr[3]) arr[3]=1e9;
	sort(arr, arr+4);
	delr(arr[0], arr[1]);
	delr(arr[2], arr[3]);
}

int mx[int(1e6)+1];
int my[int(1e6)+1];

inline void addr2(int x, int y){
	if(x>=y) return;
	y = min(y, n+1);
	iv[x]+=1;
	iv[y]-=1;
}

inline void add2(int x, int y){
	arr[0]=Arr[x*z+y]; if(!arr[0]) arr[0]=1e9;
	arr[1]=Arr[x*z+y+1]; if(!arr[1]) arr[1]=1e9;
	arr[2]=Arr[(x+1)*z+y]; if(!arr[2]) arr[2]=1e9;
	arr[3]=Arr[(x+1)*z+y+1]; if(!arr[3]) arr[3]=1e9;
	sort(arr, arr+4);
	addr2(arr[0], arr[1]);
	addr2(arr[2], arr[3]);
}

void give_initial_chart(int H, int W, vector<int> R, vector<int> C) {
	h=H; w=W; n=h*w;
	z=w+2;
	for(int i=1; i<=n; ++i){
		int x=R[i-1]+1, y=C[i-1]+1;
		mx[i]=x; my[i]=y;
		Arr[x*z+y] = i;
	}

	for(int i=0; i<=h; ++i){
		for(int j=0; j<=w; ++j){
			add2(i, j);
		}
	}

	for(int i=1; i<=n; ++i) iv[i]+=iv[i-1];

	init();
}

#define rep(i,n) for(int i=0; i<(n); ++i)

int swap_seats(int A, int B) {
	++A; ++B;
	int ax=mx[A], ay=my[A];
	rep(dx,2) rep(dy,2) del(ax-dx, ay-dy);
	Arr[ax*z+ay]=B;
	rep(dx,2) rep(dy,2) add(ax-dx, ay-dy);

	int bx=mx[B], by=my[B];
	rep(dx,2) rep(dy,2) del(bx-dx, by-dy);
	Arr[bx*z+by]=A;
	rep(dx,2) rep(dy,2) add(bx-dx, by-dy);

	mx[A]=bx; my[A]=by;
	mx[B]=ax; my[B]=ay;
	return (tree[1]==4) ? (cmn[1]) : 0;
}

