#include <iostream>
#include <stdio.h>
#include <algorithm>
#include <math.h>
#include <cmath>
#define pi M_PI
 
using namespace std;
 
struct point{
	double x;
	double y;
};
point V[1002];
bool f(point a, point b){
	if(a.x!=b.x)
		return a.x<b.x;
	return a.y<b.y;
}
int pila[1002];
int pila1[1002];
int fin, fin1;
int t;
 
int n;
double l;
double pcruz(int i, int j, int k){
	return ((V[i].x-V[k].x) * (V[j].y-V[k].y)) - ((V[i].y-V[k].y) * (V[j].x-V[k].x));
}
 
double dist(int i, int j){
	return sqrt((V[i].x-V[j].x)*(V[i].x-V[j].x)+(V[i].y-V[j].y)*(V[i].y-V[j].y));
}
 
int main(){
	scanf("%d",&t);
	while(t){
		scanf("%d%lf",&n,&l);
		for(int i=1; i<=n; i++){
			scanf("%lf%lf",&V[i].x,&V[i].y);
		}
		sort(V+1, V+n+1, f);
		pila[++fin]=1;
		for(int i=2; i<=n; i++){
			pila[++fin]=i;
			while(pcruz (pila[fin], pila[fin-2], pila[fin-1])>0 && fin>2){
				pila[fin-1]=pila[fin];
				fin--;
			}
		}
		pila1[++fin1]=1;
		for(int i=2; i<=n; i++){
			pila1[++fin1]=i;
			while(pcruz (pila1[fin1], pila1[fin1-2], pila1[fin1-1])<0 && fin1>2) {
				pila1[fin1-1]=pila1[fin1];
				fin1--;
			}
		}
		double P=0;
		int i, j;
		for(int p=1; p<fin; p++){
			i=pila[p];
			j=pila[p+1];
			P+=dist(i,j);
		}
		for(int p=1; p<fin1; p++){
			i=pila1[p];
			j=pila1[p+1];
			P+=dist(i,j);
		}
		P+=(pi*2.0*l);
		cout<<round(P)<<"\n";
		fin=0;
		fin1=0;
		t--;
		if(t)
            cout<<"\n";
	}
	return 0;
}
