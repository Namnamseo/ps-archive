#include <vector>
#include <algorithm>
#include <map>
#include <set>

using namespace std;

typedef pair<int,int> pp;

pp data[100010];

int ntonode[100010];
int nodesize[100010];
int treesize[100010];
bool visit[100010];
vector<int> edge[100010];

const int MODD=1000000000;

long long finalans;

int NNN;

void buildTree(int pos){
	visit[pos]=true;
	int i;
	int there;
	int n = edge[pos].size();
	for(i=0;i<n;i++){
		there = edge[pos][i];
		if(!visit[there]){
			buildTree(there);
			finalans = (finalans + 1LL*treesize[there]*(1LL*NNN-treesize[there]))%MODD;
			treesize[pos]+=treesize[edge[pos][i]];
		}
	}
	treesize[pos] += nodesize[pos];
}

int cutByX(int n,int *x,int *y) {
	finalans=0;
	set<pp> edgeset;
	int i;

	for(i=0;i<=100000;i++) {
		visit[i]=false;
		treesize[i]=nodesize[i]=ntonode[i]=0;
		edge[i].clear();
	}

	int nodeind=0;

	map<pp,int> mymap;
	map<pp,int>::iterator it;

	for(i=0;i<n;i++){
		mymap.insert(make_pair(make_pair(i[x],i[y]),0));
		data[i].first=x[i];
		data[i].second=y[i];
	}
	i=0;
	for(it=mymap.begin() ;it!=mymap.end(); it++){
		it->second = i;
		i++;
	}
	sort(data,data+n);

	for(i=0;i<n;i++){

		if(i==0 || data[i-1].first != data[i].first || 
		   data[i-1].second+1 != data[i].second ) {
			nodeind++;
		}

		ntonode[i]=nodeind;
		nodesize[nodeind]++;

		it = mymap.find(make_pair(data[i].first-1, data[i].second));

		if(it != mymap.end()){
			edgeset.insert(make_pair(ntonode[it->second],nodeind));
		}
	}

	set<pp>::iterator it2;

	int a,b;

	for(it2=edgeset.begin(); it2!=edgeset.end(); it2++){
		a=it2->first; b=it2->second;
		edge[a].push_back(b);
		edge[b].push_back(a);
	}

	buildTree(1);

	return finalans;
}

int DistanceSum(int n, int *x, int *y) {
	int i;
	NNN=n;
	int minx=2147483647;
	int miny=2147483647;
	for(i=0;i<n;i++){
		minx = min(minx, x[i]);
		miny = min(miny, y[i]);
	}
	for(i=0;i<n;i++){
		x[i]-=minx;
		y[i]-=miny;
	}
	return (cutByX(n,x,y)+cutByX(n,y,x))%MODD;
}