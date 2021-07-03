#include <cstdio>
#include <algorithm>
#include <map>

using namespace std;

typedef pair<int,int> pp;
map<int,pp> mm;

int max(int a,int b) { return a>b?a:b; }

int ans=1;

int lh, rh;

pp ask(int x){
	if(mm.find(x)!=mm.end()) return mm[x];
	int a=x*2,b=x*2+1;
	printf("%d\n",x); fflush(stdout);
	scanf("%d%d",&a,&b);
	return mm[x]=pp(a,b);
}

void ask(int x,int& a,int& b){ pp tmp=ask(x); a=tmp.first; b=tmp.second; }

int fleft(int x){
	int a,b,cur=x;
	int lefthei=0;
	while(cur){
		ask(cur,a,b);
		if(a) ++lefthei,cur=a;
		else break;
	}
	return lefthei;
}

int fright(int x){
	int a,b,cur=x;
	int righthei=0;
	while(cur){
		ask(cur,a,b);
		if(b) ++righthei,cur=b;
		else break;
	}
	return righthei;
}

int sfrst[400];
int sscnd[400];

int biggestChild(int x,int depth){
	int a,b;
	ask(x,a,b);
	if(a==0) return 1;
	int smallcnt=biggestChild(a,depth+1);
	int i,cur=b;
	for(i=depth+1;i<lh;++i){
		ask(cur,a,b);
		if(sfrst[i]) cur=b; else cur=a;
	}
	if(cur==0){
		int temp;
		for(i=depth;i<lh;++i) temp=sfrst[i],sfrst[i]=sscnd[i],sscnd[i]=temp;
		sfrst[depth]=1; sscnd[depth]=1;
		return smallcnt*2-1;
	} else {
		sfrst[depth]=1; sscnd[depth]=1;
		return smallcnt*2;
	}
}

int main()
{
	lh=fleft(1); rh=fright(1);
	int i,j;
	if(lh!=rh) printf("Answer %d\n",(1<<lh)-1+biggestChild(1,0));
	return 0;
}
