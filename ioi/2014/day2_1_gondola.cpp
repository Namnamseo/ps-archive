#include "gondola.h"
#include <bits/stdc++.h>
using namespace std;

int valid(int n, int a[])
{
	set<int> jb;
	set<int> of;
	for(int i=0; i<n; ++i){
		if(jb.find(a[i]) != jb.end()) return 0;
		jb.insert(a[i]);
		if(1<=a[i] && a[i]<=n){
			int t=(a[i]-i+n)%n;
			of.insert(t);
		}
	}
	return of.size() <= 1u;
}

//----------------------
#include <algorithm>
#include <cstdio>

int replacement(int n, int gond[], int rep[])
{
	int arr[100010];
	int Mx = 0, Mxp;
	set<int> of;
	for(int i=0; i<n; ++i){
		arr[i] = gond[i];
		if(1<=arr[i] && arr[i]<=n){
			int t=(arr[i]-1-i+2*n)%n;
			of.insert(t);
		}
	}
	
	if(of.size() == 1u){
		int t=*of.begin();
		rotate(arr, arr+n-t, arr+n);
	}
	for(int i=0; i<n; ++i){
		if(Mx < arr[i])
			Mx = arr[i], Mxp=i;
	}
	int mp[250010];
	for(int i=n+1; i<=Mx; ++i)
		mp[i] = -1;
	for(int i=0; i<n; ++i){
		if(arr[i] > n)
			mp[arr[i]] = i;
		arr[i] = i+1;
	}

	for(int i=n+1; i<=Mx; ++i){
		if(mp[i] == -1){
			rep[i-n-1] = arr[Mxp];
			arr[Mxp] = i;
		} else {
			rep[i-n-1] = arr[mp[i]];
		}
	}
	return Mx-n;
}

//----------------------
#define ll long long
#define M (1000000009)
static ll poW(ll a,ll b){
	if(b==0) return 1;
	ll ret=poW(a,b/2);
	ret = ret * ret % M;
	if(b&1)
		ret = ret * a % M;
	return ret;
}

int countReplacement(int n, int gond[])
{
	if(!valid(n, gond)) return 0;

	ll ans = 1;

	vector<int> v;
	for(int i=0; i<n; ++i) if(gond[i] > n) v.push_back(gond[i]);

	sort(v.begin(), v.end());

	int last = n;
	int usa = v.size();

	for(int p:v){
		ans *= poW(usa, p-last-1);
		ans %= M;
		last=p;
		--usa;
	}

	if(v.size() == n){
		ans *= n; ans %= M;
	}

	return ans;
}