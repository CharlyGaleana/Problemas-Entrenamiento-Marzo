#include <iostream>
#include <stdio.h>
#include <queue>
#include <algorithm>
 
using namespace std;
 
int n;
double w;
 
int S[500002];
int Q[500002];
int A[500002];
 
struct trabajador{
    double U;
    int id;
};
trabajador T[500002];
double mayor;
int cual;
double costo;
double suma, elementos;
double fin;
 
priority_queue<int> monti;
bool f(trabajador a, trabajador b){
    return a.U<b.U;
}
bool f1(int a, int b){
    return Q[a]<Q[b];
}
 
int main()
{
    scanf("%d%lf",&n,&w);
    for(int i=1; i<=n; i++){
        scanf("%d%d",&S[i],&Q[i]);
        T[i].U= ( double(S[i]) / double(Q[i]));
        T[i].id=i;
    }
    sort(T+1, T+n+1, f);
    double aux;
    for(int i=1; i<=n; i++){
        monti.push(Q[T[i].id]);
        elementos+=1.0;
        suma+=double(Q[T[i].id]);
        while(suma*T[i].U>w && !monti.empty()){
            elementos-=1.0;
            aux=double(monti.top());
            suma-=aux;
            monti.pop();
        }
        double P=suma*T[i].U;
        if(elementos>mayor){
            mayor=elementos;
            cual=i;
            costo=P;
        } else {
            if(elementos==mayor){
                if(P<costo){
                    cual=i;
                    costo=P;
                }
            }
        }
    }
    elementos=0;
    suma=0;
    while(!monti.empty()){
        monti.pop();
    }
    cout<<mayor<<"\n";
    for(int i=1; i<=cual; i++){
        A[i]=T[i].id;
        if(i==cual){
            fin=T[i].U;
        }
    }
    sort(A+1, A+cual+1, f1);
    int i=1;
    while(suma*fin<w && i<=cual){
        if(i>1)
            printf("%d\n",A[i-1]);
        suma+=double(Q[A[i]]);
        i++;
    }
    if(suma*fin<=w)
        printf("%d\n",A[cual]);
    return 0;
}
