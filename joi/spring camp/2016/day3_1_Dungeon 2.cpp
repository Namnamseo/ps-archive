#include "dungeon2.h"

#include <bits/stdc++.h>
using namespace std;

vector<int> edge[210];
int par[210];
int edgeind[210][210];
bool back[210][210];
int nv;

void dfs(int x){
    int en = edge[x].size();
    for(int i=0; i<en; ++i){
        if(edge[x][i]) continue;
        Move(i+1, 2);
        if(Color() == 2){
            back[x][i] = 1;
            Move(LastRoad(), 2);
        } else if(Color() == 1){
            ++nv;
            
            edge[x][i]=nv;
            edge[nv].resize(NumberOfRoads());
            edge[nv][LastRoad()-1]=x;
            
            edgeind[x][nv]=i;
            edgeind[nv][x]=LastRoad()-1;
            
            par[nv]=x;
            int my_v = nv;
            dfs(my_v);
            Move(edgeind[my_v][x]+1, 3);
        } else if(Color() == 3){
            Move(LastRoad(), 3);
        }
    }
}

int divisor;

void applyColor(int x){
    for(int y : edge[x]){
        if(par[y] == x){
            Move(edgeind[x][y]+1, x/divisor%3 + 1);
            applyColor(y);
            Move(edgeind[y][x]+1, y/divisor%3 + 1);
        }
    }
    
    for(int i=0; i<int(edge[x].size()); ++i) if(back[x][i]){
        Move(i+1, x/divisor%3 + 1);
        edge[x][i] += divisor * (Color()-1);
        int c=Color();
        Move(LastRoad(), c);
    }
}

int dist[210][210];
int insp[210];

const int inf = 1e9;

void Inspect(int R)
{
    nv = 1;
    par[1] = -1;
    edge[1].resize(NumberOfRoads());
    dfs(1);
    divisor=1; applyColor(1);
    divisor=3; applyColor(1);
    divisor=9; applyColor(1);
    divisor=27; applyColor(1);
    divisor=81; applyColor(1);
    for(int i=1; i<=nv; ++i) for(int j=1; j<=nv; ++j){
        if(i!=j) dist[i][j]=inf;
    }
    for(int i=1; i<=nv; ++i) for(int x:edge[i]) dist[i][x]=dist[x][i]=1;
    for(int j=1; j<=nv; ++j)
        for(int i=1; i<=nv; ++i)
            for(int k=1; k<=nv; ++k)
                dist[i][k]=min(dist[i][k], dist[i][j]+dist[j][k]);
    for(int i=1; i<=nv; ++i) for(int j=i+1; j<=nv; ++j){
        assert(dist[i][j]!=inf);
        ++insp[dist[i][j]];
    }
    for(int i=1; i<=R; ++i) Answer(i, insp[i]);
}
