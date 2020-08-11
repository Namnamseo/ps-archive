#include <bits/stdc++.h>
using namespace std;

int pr[1010], pn;

int main(){
	pr[pn++]=2;
	pr[pn++]=3;
	pr[pn++]=5;
	
	for(int i=7; i<1000; i+=2){
		int j;
		for(j=0; j<pn; ++j) if(i%pr[j]==0) break;
		if(j==pn) pr[pn++]=i;
	}

	int t;
	cin>>t;
	
	for(;t--;){
		int a;
		cin>>a;
		bool e=false;
		for(int i=0; i<pn && !e; ++i) for(int j=i; j<pn && !e; ++j) for(int k=j; k<pn; ++k){
			int p=pr[i];
			int q=pr[j];
			int r=pr[k];
			if(p+q+r == a){
				printf("%d %d %d\n", p, q, r);
				e=true;
				break;
			}
		}
		if(!e) puts("0");
	}
	return 0;
}

