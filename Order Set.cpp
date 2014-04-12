#include <iostream>
#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#define L 19
 
using namespace std;
 
struct elemento{
    int key;
    int h;
    int next[22];
    int len[22];
};
elemento skip[300002];
int pos=1;
int n;
char comando;
int valor;
int elementos;
 
void inicializaSkip(){
    for(int i=0; i<L; i++)
        skip[1].len[i]=1;
    skip[0].key = 1<<30;
    skip[0].h=L;
    skip[1].h=L;
    skip[1].key= -1000000001;
}
 
int nuevaAltura(){
    int nh=1, x;
    for(x=rand(); nh<L && x%2; x/=2)
        nh++;
    return nh;
}
 
void insertaElemento(int k){
    pos++;
    skip[pos].key=k;
    skip[pos].h=nuevaAltura();
}
 
int busca(int k){
    int act=1;
    for(int i=L-1; i>=0; i--){
        while(k>skip[skip[act].next[i]].key)
            act=skip[act].next[i];
    }
    act=skip[act].next[0];
    if(skip[act].key==k)
        return act;
    return 0;
}
 
bool Existe(int k){
    return (busca(k));
}
 
void k_esimo(int k){
    int act=1;
    if(elementos<k){
        printf("invalid\n");
        return;
    }
    for(int i=L-1; i>=0 && k>0; i--){
        while(act && k>=skip[act].len[i]){
            k-=skip[act].len[i];
            act=skip[act].next[i];
        }
    }
    printf("%d\n",skip[act].key);
}
 
int cuenta(int k){
    int act=1, ret=0;
    for(int i=L-1; i>=0; i--){
        while(k > skip[skip[act].next[i]].key){
            ret+=skip[act].len[i];
            act=skip[act].next[i];
        }
    }
    return ret;
}
 
void mete(int k){
    int act=1;
    int prev[L]={0};
    int saltos[L]={0};
    for(int i=L-1; i>=0; i--){
        while(k > skip[skip[act].next[i]].key){
            saltos[i]+=skip[act].len[i];
            act=skip[act].next[i];
        }
        prev[i]=act;
    }
    if(skip[skip[prev[0]].next[0]].key==k)
        return;
    elementos++;
    insertaElemento(k);
    for(int i=0; i<L; i++){
        if(i<skip[pos].h){
            int oldlen=skip[prev[i]].len[i];
            skip[prev[i]].len[i]= i==0 ? 1 : saltos[i-1]+skip[prev[i-1]].len[i-1];
            skip[pos].len[i]=oldlen-skip[prev[i]].len[i]+1;
            skip[pos].next[i]=skip[prev[i]].next[i];
            skip[prev[i]].next[i]=pos;
        } else {
            skip[prev[i]].len[i]++;
        }
    }
}
 
void borrar(int k){
    int act=1;
    if(!Existe(k))
        return;
    elementos--;
    for(int i=L; i>=0; i--){
        while(k > skip[skip[act].next[i]].key)
            act=skip[act].next[i];
        if(skip[skip[act].next[i]].key==k){
            skip[act].len[i]+=skip[skip[act].next[i]].len[i];
            skip[act].next[i]=skip[skip[act].next[i]].next[i];
        }
        skip[act].len[i]--;
    }
}
 
int main()
{
    scanf("%d",&n);
    inicializaSkip();
    for(int i=1; i<=n; i++){
        scanf(" %c%d",&comando,&valor);
        if(comando=='I')
            mete(valor);
        if(comando=='D')
            borrar(valor);
        if(comando=='K')
            k_esimo(valor);
        if(comando=='C')
            printf("%d\n",cuenta(valor));
    }
    return 0;
}
