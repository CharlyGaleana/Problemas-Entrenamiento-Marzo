#include <iostream>
#include <stdio.h>
#include <queue>
 
using namespace std;
 
struct estado{
    int x;
    long long int t;
};
 
bool operator<(estado a, estado b){
    return a.t>b.t;
}
 
priority_queue<estado> monti;
 
long long int lim=500000000;
int n, m, pos;
int nodo[20002];
bool HP[20002];
long long int costo[20002];
int siguiente[20002];
int primero[502];
 
void agregaArista(int a, int b, bool h, long long int c){
    nodo[++pos]=b;
    HP[pos]=h;
    costo[pos]=c;
    siguiente[pos]=primero[a];
    primero[a]=pos;
}
 
void vaciaMonti(){
    while(!monti.empty()){
        monti.pop();
    }
}
 
int color;
int vis[502];
 
long long int dijkstra(int a, int b, long long int v){
    estado ini, act, hijo;
    color++;
    vaciaMonti();
    ini.x=a;
    ini.t=0;
    monti.push(ini);
    while(!monti.empty()){
        act=monti.top();
        while(vis[act.x]==color && !monti.empty()){
            monti.pop();
            act=monti.top();
        }
        if(vis[act.x]!=color){
            vis[act.x]=color;
            if(act.x==b)
                return act.t;
            int posi=primero[act.x];
            while(posi){
                hijo.x=nodo[posi];
                if(HP[posi])
                    hijo.t=v;
                else
                    hijo.t=costo[posi];
                hijo.t+=act.t;
                monti.push(hijo);
                posi=siguiente[posi];
            }
        }
    }
    return -1;
}
 
long long int binaria(int a, int b){
    long long int ini=1, fin=lim, mitad;
    while(ini!=fin){
        mitad=(ini+fin)/2;
        if(dijkstra(a, b, mitad)==dijkstra(a, b, mitad+1))
            fin=mitad;
        else
            ini=mitad+1;
    }
    return ini;
}
 
int a, b, q;
long long int c;
 
int main()
{
    scanf("%d%d",&n,&m);
    for(int i=1; i<=m; i++){
        bool h=0;
        if(scanf("%d%d%lld",&a,&b,&c)!=3){
            h=1;
            scanf(" %*c");
        }
        agregaArista(a, b, h, c);
    }
    scanf("%d",&q);
    for(int i=1; i<=q; i++){
        scanf("%d%d",&a,&b);
        long long int aux=dijkstra(a, b, lim+1);
        if(aux > lim){
            printf("inf");
        } else {
            if(aux==-1){
                printf("0");
            } else {
                cout<<binaria(a, b);
            }
        }
        printf("\n");
    }
    return 0;
}
