#include <cstdio>
int c(int a,int b){
    if(b==0 || b==a) return 1;
    else return c(a-1,b-1)+c(a-1,b);
}
int main()
{
    int n,m,k;
    scanf("%d%d%d",&n,&m,&k);
    --k;
    if(k>=0) printf("%d\n",c(k/m+k%m,k/m)*c(n+m-2-k/m-k%m,n-1-k/m));
    else printf("%d\n",c(n+m-2,m-1));
    return 0;
}
