#include <bits/stdc++.h>
using namespace std;
#define sz(v) ((int)((v).size()))
#define all(v) (v).begin(), (v).end()
#define pb push_back
#define coord_comp(v) sort(all(v)), v.erase(unique(all(v)), v.end())
#define v_index(v, x) (lower_bound(all(v),x)-(v).begin())
typedef pair<int,int> pp;
typedef long long ll;
void read(int& x){ scanf("%d",&x); }
void read(ll& x){ scanf("%lld",&x); }
template<typename T1,typename T2>
void read(pair<T1,T2>& p){ read(p.first); read(p.second); }
template<typename T,typename... Args>
void read(T&a,Args&...b){ read(a); read(b...); }

#define double long double

typedef pair<double, double> line;

double cross(line a,line b){
	return (a.second-b.second) / (b.first-a.first);
}

line l[200010];
int top;

bool parallel(line& a,line& b){
	return abs(a.first - b.first) < 1e-14;
}

void addLine(double grad,double yint){
	line c(grad, yint);
	while(top>=1){
		if(parallel(l[top-1], c)){
			if(l[top-1].second < yint) return;
			--top;
			continue;
		}
		if(l[top-1].first > grad){
			--top;
			continue;
		}
		if(top == 1) break;
		double a=cross(l[top-2], l[top-1]);
		double b=cross(l[top-1], c);
		if(b<a) break;
		--top;
	}
	l[top++]=c;
}

double fx(line a,double x){
	return a.first*x+a.second;
}

double findY(double x){
	if(top<=2){
		double ret=1e300;
		for(int i=0; i<top; ++i){
			ret=min(ret, fx(l[i], x));
		}
		return ret;
	}
	int lf=0, r=top-2, mid;
	if(x >= cross(l[lf], l[lf+1])){
		return fx(l[lf],x);
	}
	if(cross(l[r], l[r+1])>=x){
		return fx(l[r+1], x);
	}
	while(lf+1 < r){
		mid=(lf+r)/2;
		if(cross(l[mid], l[mid+1]) >= x) lf=mid;
		else r=mid;
	}
	return min(fx(l[lf],x), fx(l[r],x));
}

double square(double x){ return x*x; }

int main(){
	int n;
	read(n);

	for(int i=1; i<=n; ++i){
		int x, r;
		read(x, r);
		double myr = min((double)r, square(findY(x)));
		addLine(sqrt(1.0 / myr)/2.0, -x*sqrt(1.0 / myr)/2.0);
		printf("%.5Lf\n" ,myr);
	}
	
	return 0;
}

