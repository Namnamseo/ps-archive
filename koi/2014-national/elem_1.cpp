#include <cstdio>

int main()
{
    int t;
    scanf("%d",&t);
    if(t%10) puts("-1");
    else printf("%d %d %d\n",t/300,t%300/60,t%60/10);
    return 0;
}
