#include <bits/stdc++.h>
using namespace std;

int n, m;
bool nok[201][201];

int main(){
	scanf("%d%d", &n, &m);
	for(int i=1, a, b; i<=m; ++i){
		scanf("%d%d", &a, &b);
		nok[a][b]=nok[b][a]=1;
	}
	
	int ans = 0;
	for(int i=1; i<n; ++i){
		for(int j=i+1; j<=n; ++j){
			if(nok[i][j]) continue;
			for(int k=j+1; k<=n; ++k) if(!nok[i][k] && !nok[j][k]) ++ans;
		}
	}

	printf("%d\n", ans);

	return 0;
}
