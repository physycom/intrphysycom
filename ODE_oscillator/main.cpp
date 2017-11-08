// Moto armonico: autovalori debolmente instabili


#include <iostream>
#include <stdlib.h>
#include <stdio.h>
#include <math.h>

using namespace std;

#define PI    3.1415927

//-----------------------------------------------------------
struct Stato {
	  double x,v,a;
	  void set(double x,double v) { this->x= x; this->v= v; }
};
//-----------------------------------------------------------

Stato s;
double t,delta;

//-----------------------------------------------------------
void force( Stato &s){
    s.a= -s.x;        
}
//-----------------------------------------------------------
double energy( Stato &s){
    double sum=0;
    sum+=  s.x*s.x;  // 2 energia potenziale
    sum+=  s.v*s.v;  // 2 energia cinetica           
    return sum/2;        
}
//-----------------------------------------------------------
void next_rk2(){
    Stato sw;
    force(s);
    sw.x= s.x +s.v*delta/2;
    sw.v= s.v +s.a*delta/2;		
	t= t +delta/2;
    force(sw);
    s.x= s.x +sw.v*delta;
    s.v= s.v +sw.a*delta;
    t= t +delta/2;
}
//-----------------------------------------------------------
void next_s2(){
     
    s.x= s.x +s.v*delta/2;
    t= t +delta/2; 
	force(s);
    s.v= s.v +s.a*delta;
    s.x= s.x +s.v*delta/2;
    t= t +delta/2;
}
//-----------------------------------------------------------
void next_rk4(){
     
    Stato sw1,sw2,sw3;
 
    force(s);
        sw1.x= s.x +s.v*delta/2;
        sw1.v= s.v +s.a*delta/2;
    t= t+ delta/2; force(sw1);
        sw2.x= s.x +sw1.v*delta/2;
        sw2.v= s.v +sw1.a*delta/2;
    force(sw2);
        sw3.x= s.x +sw2.v*delta;
        sw3.v= s.v +sw2.a*delta; 
    t= t+ delta/2; force(sw3); 
        s.x= s.x +(s.v+2*sw1.v+2*sw2.v+sw3.v)*delta/6;
        s.v= s.v +(s.a+2*sw1.a+2*sw2.a+sw3.a)*delta/6;
}
//-----------------------------------------------------------
int main(int argc, char *argv[])
{
   
   int n_rotazioni=10000000;
   int n_punti_x_rotazione=200; 
   int kmax= n_rotazioni*n_punti_x_rotazione;
   delta= 2*PI/n_punti_x_rotazione;
      
   printf("\n      n_rotazioni= %d  n_punti_x_rotazione= %d\n\n",n_rotazioni,n_punti_x_rotazione);  
   printf("          2E= 1.000000000 x= 1.000000 v= 0.000000  esatto \n");  
   
   s.set(1.0,0.0); t=0.0;
   for (int k=0; k<kmax; k++) next_s2();
   printf(" t=%6.2lf 2E=%12.9lf x=%9.6lf v=%9.6lf      s2\n",t,2*energy(s),s.x,s.v);

   //s.set(1.0,0.0); t=0.0;
   //for (int k=0; k<kmax; k++) next_rk2();
   //printf(" t=%6.2lf 2E=%12.9lf x=%9.6lf v=%9.6lf     rk2\n",t,2*energy(s),s.x,s.v);

   s.set(1.0,0.0); t=0.0;
   for (int k=0; k<kmax; k++) next_rk4();
   printf(" t=%6.2lf 2E=%12.9lf x=%9.6lf v=%9.6lf     rk4\n",t,2*energy(s),s.x,s.v);
  
   printf("\n  ");  
   system("PAUSE");	
   return 0;
}



