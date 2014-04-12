#include <iostream>
#include <stdio.h>
 
using namespace std;
 
int n;
int vis[1002][1002];
long long int x[1002];
long long int y[1002];
long long int pass=1;
int color;
 
bool sonColineales(int a, int b, int c){
    int aux=x[b]-x[a], aux1=x[c]-x[b];
    if(!aux)
        aux=(pass<<40);
    if(!aux1)
        aux1=(pass<<40);
    return (aux1)*(y[b]-y[a])==(aux)*(y[c]-y[b]);
}
 
int main(){
    scanf("%d",&n);
    while(n!=0){
        for(int i=1; i<=n; i++){
            scanf("%lld%lld",&x[i],&y[i]);
        }
        color++;
        int cont=0;
        for(int i=1; i<=n; i++){
            for(int j=i+1; j<=n; j++){
                vis[i][j]=color;
            }
        }
        for(int i=1; i<=n; i++){
            for(int j=i+1; j<=n; j++){
                for(int k=j+1; k<=n; k++){
                    if(sonColineales(i, j, k)){
                        vis[i][j]=0;
                        vis[j][k]=0;
                    }
                }
            }
        }
        for(int i=1; i<=n; i++){
            for(int j=i+1; j<=n; j++){
                if(vis[i][j]==color){
                    cont++;
                }
            }
        }
        printf("%d\n",cont);
        scanf("%d",&n);
    }
}
