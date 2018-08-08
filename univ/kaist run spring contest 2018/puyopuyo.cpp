#include <bits/stdc++.h>

int n, m, k;
int a[21][21];

typedef tuple<int,int,int,int> t4;

vector<t4> ans;

int main(){
	cin >> n >> m >> k;
	for(int i=1; i<=n; ++i){
		for(int j=1; j<=m; ++j){
			cin >> a[i][j];
		}
	}
	for(int j=1; j<=m; ++j){
		vector<int> t;
		for(int i=n; 1<=i; --i){
			if(!a[i][j]) break;
			t.push_back(a[i][j]);
		}
		int s = t.size();
		if(s & 1){
			int c1 = t[0];
			int c2 = (c1 == k ? 1 : k);
			ans.emplace_back(1, j, c2, c1);
			ans.emplace_back(1, j, c2, c2);
			ans.emplace_back(1, j, c2, c2);
			for(int i=0; i+1<s; ++i) t[i]=t[i+1];
			t.resize(s-1);
		}
		for(int i=0; i<s; i+=2){

		}
	}
	return 0;
}
