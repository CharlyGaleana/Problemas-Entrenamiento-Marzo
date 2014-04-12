#include <iostream>
#include <stdio.h>
#include <math.h>

using namespace std;

bool cambia;
int n, L, m;
int ind, pos;
int cubetas;
int H;
int lim;
int i, j;
int E[151002];
struct cubeta{
    int p;
    int e[800];
};
cubeta B[400];
int J[151002], last[151002];
int x[151002];
int b[151002], e[151002];

void reconstruyeCubeta(int i, int k){
    int j;
    x[B[i].e[B[i].p]]=x[B[i].e[B[i].p-1]]+L+1;
    J[B[i].e[B[i].p]]=0;
    last[B[i].e[B[i].p]]=B[i].e[B[i].p];
    int t=B[i].p;
    for(j=k; j>=0; j--){
        while(x[B[i].e[t-1]]>x[B[i].e[j]]+L)
            t--;
        J[B[i].e[j]]=J[B[i].e[t]]+1;
        last[B[i].e[j]]=last[B[i].e[t]];
        if(last[B[i].e[j]]==B[i].e[B[i].p])
            last[B[i].e[j]]=B[i].e[j];
    }
}

void reordena(){
    int donde=0, pos=0, i, j;
    for(i=0; i<cubetas; i++)
        for(j=0; j<B[i].p; j++)
            E[pos++]=B[i].e[j];
    for(i=0; i<cubetas; i++)
        B[i].p=0;
    for(i=0; i<n; i++){
        if(B[donde].p<H){
            B[donde].e[B[donde].p++]=E[i];
        } else {
            donde++;
            B[donde].e[B[donde].p++]=E[i];
        }
        b[E[i]]=donde;
        e[E[i]]=B[donde].p-1;
    }
    cubetas=donde+1;
    for(i=0; i<cubetas; i++){
        B[i].e[B[i].p]=n+i+1;
        reconstruyeCubeta(i, B[i].p-1);
    }
}

void quita(int i, int j){
    B[i].p--;
    if(B[i].p==0)
        cambia=true;
    for(; j<B[i].p; j++){
        B[i].e[j]=B[i].e[j+1];
        e[B[i].e[j]]=j;
    }
    B[i].e[B[i].p]=n+i+1;
    reconstruyeCubeta(i, j-1);
}

void pon(int i, int j, int ind){
    int k;
    B[i].p++;
    if(B[i].p>=lim)
        cambia=true;
    for(k=B[i].p; k>=j+1; k--){
        B[i].e[k]=B[i].e[k-1];
        e[B[i].e[k]]=k;
    }
    B[i].e[j]=ind;
    B[i].e[B[i].p]=n+i+1;
    reconstruyeCubeta(i, j);
}

int encuentraPos(int i, int pos){
    int ini=0, fin=B[i].p-1, mitad;
    while(ini!=fin){
        mitad=(ini+fin)/2+1;
        if(x[B[i].e[mitad]]<pos)
            ini=mitad;
        else
            fin=mitad-1;
    }
    return ini+1;
}

void update(int ind, int pos){
    int i, nuevab=cubetas-1, nuevae;
    x[ind]=pos;
    quita(b[ind], e[ind]);
    for(i=0; i<cubetas; i++){
        if(B[i].p){
            if(x[B[i].e[B[i].p-1]]>=pos){
                nuevab=i;
                break;
            }
        }
    }
    if(x[B[nuevab].e[0]]>=pos || B[nuevab].p==0)
        nuevae=0;
    else
        nuevae=encuentraPos(nuevab, pos);
    pon(nuevab, nuevae, ind);
    b[ind]=nuevab;
    e[ind]=nuevae;
}

int primeraMayor(int i, int pos){
    int ini=0, fin=B[i].p-1, mitad;
    while(ini!=fin){
        mitad=(ini+fin)/2;
        if(x[B[i].e[mitad]]>pos)
            fin=mitad;
        else
            ini=mitad+1;
    }
    return B[i].e[ini];
}

int query(){
    int ret=0, pos=-1, act, i;
    for(i=0; i<cubetas; i++){
        if(B[i].p){
            if(x[B[i].e[B[i].p-1]]>pos){
                act=primeraMayor(i, pos);
                ret+=J[act];
                pos=x[last[act]]+L;
            }
        }
    }
    return ret;
}

int main()
{
    scanf("%d%d%d",&n,&L,&m);
    for(i=0; i<n; i++){
        scanf("%d",&x[i]);
        E[i]=i;
    }
    H=sqrt(n);
    lim=H+(H/2)+(H/2/2);
    reordena();
    for(i=1; i<=m; i++){
        scanf("%d%d",&ind,&pos);
        update(ind, pos);
        printf("%d\n",query());
        if(cambia)
            reordena();
        cambia=false;
    }
    return 0;
}
