#include <cstdio>
char s[1010];
int main()
{
	scanf("%[^\n]", s);
	int j = 0;
	for(int i=0; s[i]; ++i) if (j<4 && s[i]=="UCPC"[j]) ++j;
	if (j==4) printf("I love UCPC\n");
	else printf("I hate UCPC\n");
}
