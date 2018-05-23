#include <cstdio>

int main()
{
    int a,b,c;
    int cur=1, cc=0;
    int n;
    scanf("%d",&n);
    for(;n--;){
        scanf("%d%d%d",&a,&b,&c);
        cur=(cur*1ll*b/a);
        if(c) cc=1-cc;
    }
    printf("%d %d\n",cc,cur);
    return 0;
}
