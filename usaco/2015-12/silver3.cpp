#include <cstdio>

int c[3][100010];

int main()
{
	freopen("bcount.in","r",stdin);
	freopen("bcount.out","w",stdout);
	int n,q;
	scanf("%d%d",&n,&q);
	int i;
	for(i=1;i<=n;++i){
		int a;scanf("%d",&a);
		++c[a-1][i];
	}
	for(int j=0;j<3;++j)
	for(i=1;i<=n;++i){
		c[j][i]+=c[j][i-1];
	}
	for(;q--;){
		int a,b;
		scanf("%d%d",&a,&b);
		for(i=0;i<3;++i) {
			printf("%d",c[i][b]-c[i][a-1]);
			if(i!=2) putchar(' ');
		}
		putchar(10);
	}
	return 0;
}
