#include <iostream>
#include <stdio.h>
#include <math.h>
#define pi M_PI
#define ang asin((pc)/(Ma*Mb))
 
using namespace std;
 
float a, b, x, y;
float px, py;
float Ma, Mb;
 
float ppunto(){
    return (a*x) + (b*y);
}
 
float pcruz(){
    return (a*y) - (b*x);
}
 
float grados(float radian){
    return (180.0 * radian) / pi;
}
 
float angulo(){
    float pp=ppunto(), pc=pcruz();
    float radian;
    if(pc>=0){
        if(pp>=0)
            radian= ang;
        else
            radian= pi-ang;
    } else {
        if(pp>=0)
            radian= 2*pi + ang;
        else
            radian= pi-ang;
    }
    return grados(radian);
}
 
int main()
{
    scanf("%f%f%f%f%f%f",&a,&b,&px,&py,&x,&y);
    a-=px;
    b-=py;
    x-=px;
    y-=py;
    Ma=sqrt( (a*a)+(b*b) );
    Mb=sqrt( (x*x)+(y*y) );
    printf("%f\n",angulo());
    return 0;
}
