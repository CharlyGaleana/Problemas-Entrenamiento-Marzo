#include <iostream>
#include <stdio.h>
 
using namespace std;
 
int n;
int operacion;
int x1, y1, x2, y2;
int v;
int bit[1030][1030];
 
void actualiza(int x, int y, int v){
    for(; x<=n; x+=(x&-x)){
        for(int j=y; j<=n; j+=(j&-j)){
            bit[x][j]+=v;
        }
    }
}
 
int query(int x, int y){
    int ret=0;
    for(; x; x-=(x&-x)){
        for(int j=y; j; j-=(j&-j)){
            ret+=bit[x][j];
        }
    }
    return ret;
}
 
int consulta(int x1, int y1, int x2, int y2){
    int ret=query(x2, y2);
    ret-=query(x2  , y1-1);
    ret-=query(x1-1, y2  );
    ret+=query(x1-1, y1-1);
    return ret;
}
 
int main()
{
    scanf("%d%d",&operacion,&n);
    scanf("%d",&operacion);
    while(operacion!=3){
        if(operacion==1){
            scanf("%d%d%d",&x1,&y1,&v);
            x1++; y1++;
            actualiza(x1, y1, v);
        } else {
            scanf("%d%d%d%d",&x1,&y1,&x2,&y2);
            x1++; y1++; x2++; y2++;
            printf("%d\n",consulta(x1, y1, x2, y2));
        }
        scanf("%d",&operacion);
    }
    return 0;
}
