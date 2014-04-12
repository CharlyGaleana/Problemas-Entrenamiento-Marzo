#include <iostream>
#include <stdio.h>
 
using namespace std;
 
int n;
char op, c;
int k;
int i, j;
 
struct printer{
    int tam;
    char letter;
    int hijos[22];
};
printer pila[1000002];
int fin;
 
int pos;
int Bin[22];
 
void generaBin(int num){
    if(num==0)
        return;
    Bin[pos++]=num%2;
    generaBin(num/2);
}
 
void GetLetter(int k){
    int num=pila[fin].tam-k, act;
    pos=0;
    generaBin(num);
    act=fin;
    for(i=0; i<pos; i++){
        if(Bin[i])
            act=pila[act].hijos[i];
    }
    printf("%c\n",pila[act].letter);
}
 
void UndoCommands(int k){
    fin++;
    pila[fin]=pila[fin-k-1];
}
 
void TypeLetter(char c){
    fin++;
    int posi=1, act=fin-1;
    pila[fin].tam=pila[fin-1].tam+1;
    pila[fin].letter=c;
    pila[fin].hijos[0]=fin-1;
    while(act!=0){
        pila[fin].hijos[posi]=pila[act].hijos[posi-1];
        act=pila[act].hijos[posi-1];
        posi++;
    }
}
 
int main()
{
    scanf("%d",&n);
    for(int i=1; i<=n; i++){
        scanf(" %c",&op);
        if(op=='T'){
            scanf(" %c",&c);
            TypeLetter(c);
        } else {
            scanf("%d",&k);
            if(op=='U')
                UndoCommands(k);
            else {
                k++;
                GetLetter(k);
            }
        }
    }
    return 0;
}
