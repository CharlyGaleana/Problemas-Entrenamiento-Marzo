#include <iostream>
#include <stdio.h>
 
using namespace std;
 
int ST[300002];
int A[100002];
int L[100002], R[100002];
int pila[100002];
int t, n, fin;
 
void creaST(int nodo, int ini, int fin){
    if(ini==fin){
        ST[nodo]=ini;
        return;
    }
    int mitad=(ini+fin)/2, l=nodo*2, r=nodo*2+1;
    creaST(l, ini    , mitad);
    creaST(r, mitad+1, fin  );
    int rl=ST[l], rr=ST[r];
    if(A[rl]<A[rr])
        ST[nodo]=rl;
    else
        ST[nodo]=rr;
}
 
int query(int nodo, int b, int e, int i, int j){
    if(b>j || e<i)
        return -1;
    if(b>=i && e<=j)
        return ST[nodo];
    int mitad=(b+e)/2, p1, p2;
    p1=query(nodo*2  , b      , mitad, i, j);
    p2=query(nodo*2+1, mitad+1, e    , i, j);
    if(p1==-1)
        return p2;
    if(p2==-1)
        return p1;
    if(A[p1]<A[p2])
        return p1;
    return p2;
}
 
bool cumpleR(int i){
    if(!R[i])
        return A[i]>=150000;
    if(R[i]>i+1)
        return A[query(1, 1, n, i+1, R[i]-1)] <= A[i]-150000;
    return false;
}
 
bool cumpleL(int i){
    if(!L[i])
        return A[i]>=150000;
    if(L[i]<i-1)
        return A[query(1, 1, n, L[i]+1, i-1)] <= A[i]-150000;
    return false;
}
 
void llenaR(){
    fin=0;
    for(int i=1; i<=n; i++)
        R[i]=0;
    for(int i=1; i<=n; i++){
        while(fin>0 && A[pila[fin]]<A[i]){
            R[pila[fin]]=i;
            fin--;
        }
        pila[++fin]=i;
    }
}
 
void llenaL(){
    fin=0;
    for(int i=1; i<=n; i++)
        L[i]=0;
    for(int i=n; i>0; i--){
        while(fin>0 && A[pila[fin]]<A[i]){
            L[pila[fin]]=i;
            fin--;
        }
        pila[++fin]=i;
    }
}
 
int main()
{
    while(scanf("%d",&n) != EOF){
        for(int i=1; i<=n; i++){
            scanf("%d",&A[i]);
        }
        llenaR();
        llenaL();
        creaST(1, 1, n);
        int cuantos=0;
        for(int i=1; i<=n; i++){
            if(cumpleL(i) && cumpleR(i)){
                if(cuantos)
                    printf(" ");
                printf("%d",i);
                cuantos++;
            }
        }
        printf("\n");
    }
    return 0;
}
