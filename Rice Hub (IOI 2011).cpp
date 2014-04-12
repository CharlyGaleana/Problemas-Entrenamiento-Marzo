#include <iostream>
#include <stdio.h>
 
using namespace std;
 
int n, L;
long long int B;
int x[100002];
long long int sum[100002];
 
int busca(int ini, int fin, int p){
    int mitad;
    while(ini!=fin){
        mitad=(ini+fin)/2+1;
        if(p>=x[mitad])
            ini=mitad;
        else
            fin=mitad-1;
    }
    return ini;
}
 
long long int costo(int p, int a, int b){
    int x=busca(a, b, p);
    return (long long int)(x-a+1)*(long long int)(p)-(sum[x]-sum[a-1])+(sum[b]-sum[x])-(long long int)(b-x)*(long long int)(p);
}
 
int minimo(int ini, int fin, int b, int e){
    int mitad;
    while(ini!=fin){
        mitad=(ini+fin)/2;
        if(costo(mitad, b, e)<=costo(mitad+1, b, e))
            fin=mitad;
        else
            ini=mitad+1;
    }
    return ini;
}
 
bool puede(int i, int h){
    return costo(minimo(x[i], x[i+h-1], i, i+h-1), i, i+h-1) <= B;
}
 
int main()
{
    scanf("%d%d%lld",&n,&L,&B);
    for(int i=1; i<=n; i++){
        scanf("%d",&x[i]);
    }
    int cuantos=0;
    for(int i=1; i<=n; i++){
        sum[i]=sum[i-1]+(long long int)(x[i]);
    }
    for(int i=1; i<=n; i++){
        if(i+cuantos<=n){
            while(puede(i, cuantos+1)){
                cuantos++;
                if(i+cuantos>n)
                    break;
            }
        }
    }
    printf("%d\n",cuantos);
    return 0;
}
