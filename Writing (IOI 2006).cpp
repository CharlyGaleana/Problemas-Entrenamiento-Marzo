#include <iostream>
#include <stdio.h>
 
using namespace std;
 
int n, m;
char W[5002];
char S[5000002];
int C[502];
int cubeta[502];
 
void cubetazo(char a, int c, int v){
    int letra=(a-'A');
    if(letra>25){
        letra=(a-'a');
        letra+=26;
    }
    if(c)
        cubeta[letra]+=v;
    else
        C[letra]+=v;
}
 
bool compara(){
    for(int i=0; i<=51; i++){
        if(C[i]!=cubeta[i])
            return false;
    }
    return true;
}
 
int barrido(){
    int ini=1, fin;
    int ret=0;
    for(int i=1; i<=n; i++)
        cubetazo(W[i], 0, 1);
    for(int i=1; i<=n; i++)
        cubetazo(S[i], 1, 1);
    fin=n+1;
    if(compara())
        ret++;
    while(fin<=m){
        cubetazo(S[ini], 1, -1);
        ini++;
        cubetazo(S[fin], 1, 1);
        fin++;
        if(compara())
            ret++;
    }
    return ret;
}
 
int main()
{
    scanf("%d%d",&n,&m);
    for(int i=1; i<=n; i++)
        scanf(" %c",&W[i]);
    for(int j=1; j<=m; j++)
        scanf(" %c",&S[j]);
    cout<<barrido()<<"\n";
    return 0;
}
