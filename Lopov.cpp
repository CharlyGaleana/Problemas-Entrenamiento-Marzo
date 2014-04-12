#include <stdio.h>
#include <iostream>
#include <algorithm>
#include <queue>
 
using namespace std;
 
priority_queue<long long int> disponibles;
 
int n, k;
int C[300002];
 
struct joya{
	long long int M;
	long long int V;
};
joya A[300002];
 
bool f(joya a, joya b){
	return a.M<b.M;
}
 
int main(){
	scanf("%d%d",&n,&k);
	for(int i=1; i<=n; i++){
		scanf("%lld%lld",&A[i].M,&A[i].V);
	}
	sort(A+1, A+n+1, f);
	for(int i=1; i<=k; i++){
		scanf("%d",&C[i]);
	}
	sort(C+1, C+k+1);
	int indice=1;
	long long int ans=0;
	for(int i=1; i<=k; i++){
		while(C[i]>=A[indice].M && indice<=n){
			disponibles.push(A[indice].V);
			indice++;
		}
		if(!disponibles.empty()){
			ans+=disponibles.top();
			disponibles.pop();
		}
	}
	printf("%lld\n",ans);
	return 0;
}
