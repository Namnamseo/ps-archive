#include <bits/stdc++.h>
using namespace std;

char s[250010];
int main(){
	scanf("%s", s);
	string a(s);
	reverse(s, s+strlen(s));
	if(a == string(s)) puts("YES");
	else puts("NO");
	return 0;
}
