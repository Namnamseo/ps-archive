#include <cstdio>
#include <algorithm>

int n,m;

int mt  [262144];
int lazy[262144];

int max(int a,int b){ return a>b?a:b; }
int min(int a,int b){ return a<b?a:b; }

void update(int pos,int ml,int mr,int l,int r){
	if(pos<131072){
		mt  [pos*2  ]+=lazy[pos];
		lazy[pos*2  ]+=lazy[pos];
		mt  [pos*2+1]+=lazy[pos];
		lazy[pos*2+1]+=lazy[pos];
		lazy[pos]=0;
	}
	if(l<=ml && mr<=r){
		++mt[pos]; ++lazy[pos];
	} else if(mr<l || r<ml) return;
	else {
		int m=(ml+mr)/2;
		update(pos*2  ,ml ,m ,l,r);
		update(pos*2+1,m+1,mr,l,r);
		mt[pos]=max(mt[pos*2],mt[pos*2+1]);
	}
}

inline void update(int l,int r){ if(l<=r) update(1,0,131071,l,r); }

int findLeftIsang(int val){
	int pos=1;
	if(mt[pos]<val) return n;
	while(pos<131072){
		mt  [pos*2  ]+=lazy[pos];
		lazy[pos*2  ]+=lazy[pos];
		mt  [pos*2+1]+=lazy[pos];
		lazy[pos*2+1]+=lazy[pos];
		lazy[pos]=0;
		pos*=2;
		if(mt[pos]<val) ++pos;
	}
	return pos-131072;
}
void back_propagate(int index){
	if(index>1){
		back_propagate(index/2);
	}
	if(index<131072){
		mt  [index*2  ]+=lazy[index];
		mt  [index*2+1]+=lazy[index];
		lazy[index*2  ]+=lazy[index];
		lazy[index*2+1]+=lazy[index];
		lazy[index]=0;
	}
}

int to_upd_left[10];
int to_upd_right[10];
int to_upd_ind;

inline void queue(int l,int r){ to_upd_left[to_upd_ind]=l, to_upd_right[to_upd_ind]=r, ++to_upd_ind; }
inline void flush() { for(;to_upd_ind--;) update(to_upd_left[to_upd_ind],to_upd_right[to_upd_ind]); ++to_upd_ind; }

int main(){
	scanf("%d%d",&n,&m);
	int i;
	for(i=0;i<n;++i) scanf("%d",mt+131072+i);
	std::sort(mt+131072,mt+131072+n);
	for(i=131071;i>=1;--i) mt[i]=max(mt[i*2],mt[i*2+1]);
	char com;
	int a,b;
	int k;
	int p,q,r,s, minval, maxval;
	for(;m--;){
		getchar();
		scanf("%c%d%d",&com,&a,&b);
		if(com=='F'){
			if(mt[1]<b) continue;
			p = findLeftIsang(b);
			q = findLeftIsang(mt[131072+p]+1);
			if(q-p >= a) queue(q-a,q-1);
			else {
				queue(p,q-1);
				a-=q-p;
				if(q+a-1>n-1) queue(q,n-1);
				else {
					back_propagate(q+a-1+131072);
					maxval = mt[q+a-1+131072];
					r = findLeftIsang(maxval);
					s = findLeftIsang(maxval+1);
					k=a-(r-q);
					queue(s-k,s-1);
					queue(q,q+a-k-1);
				}
			}
			flush();
		} else if(com=='C'){
			b=findLeftIsang(b+1);
			a=findLeftIsang(a);
			printf("%d\n",b-a);
		}
	}
	return 0;
}
