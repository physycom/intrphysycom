#include <math.h>
#include "dati.h"
#include "utili.h"


double x[N],u[N],t,dt,dx;
int nmax=N,iter=0;

//-----------------------------------------------------------------------------
void Start(void){
        t=0; dx = 10.0/(N-1); dt= 0.99*dx;                // perche dissipa?
    //  t=0; dx = 10.0/(N-1); dt= 1.3*dx;  //GOT
    //  t=0; dx = 10.0/(N-1); dt= 0.1*dx;  //Simple
    
    for( int n=0; n<N; n++ ){ 
         x[n]= -5+ n*dx;
         
         if ( x[n] > -1 &&   x[n] < 1 ) u[n]= 1;
         else u[n]= 0.0;
    }
}
//-----------------------------------------------------------------------------
void GOT(void){
      double L[N],v[N];
      for (int i = 2; i<(N-2); i++) { L[i]=-uu_x(i,u); v[i]= u[i] +L[i]*dt; }
      v[0]=v[N-4]; v[1]=v[N-3]; v[N-2]= v[2]; v[N-1]= v[3]; 

      for (int i = 2; i<(N-2); i++) { L[i]=-uu_x(i,v);; u[i]= (u[i] +v[i] +L[i]*dt)/2; }
      u[0]=u[N-4]; u[1]=u[N-3]; u[N-2]= u[2]; u[N-1]= u[3]; 

	  t=t+dt;
}
//-----------------------------------------------------------------------------
void simple2(void){
      double L[N],v[N];
      for (int i = 2; i<(N-2); i++) { 
          L[i]=-(2.0/3.0)*( u[i+1]*u[i+1]*u[i+1] - u[i-1]*u[i-1]*u[i-1] )/dx; 
          v[i]= sqrt( u[i]*u[i] +L[i]*dt ) ;
      }
      v[0]= v[N-2]; v[N-1]= v[1];

      for (int i = 2; i<(N-2); i++) { 
          L[i]=-(2.0/3.0)*( v[i+1]*v[i+1]*v[i+1] - v[i-1]*v[i-1]*v[i-1] )/dx;
          u[i]= sqrt(u[i]*u[i] +v[i]*v[i] +L[i]*dt)/2;
      }   
      u[0]= u[N-2]; u[N-1]= u[1];
	  t=t+dt;
     
}
//-----------------------------------------------------------------------------
void simple(void){
      double L[N],v[N];
      for (int i = 2; i<(N-2); i++) { L[i]=-(u[i+1]+u[i-1])*(u[i+1]-u[i-1])/(4*dx); v[i]= u[i] +L[i]*dt; }
      v[0]= v[N-2]; v[N-1]= v[1];

      for (int i = 2; i<(N-2); i++) { L[i]=-(v[i+1]+v[i-1])*(v[i+1]-v[i-1])/(4*dx); u[i]= (u[i] +v[i] +L[i]*dt)/2; }   
      u[0]= u[N-2]; u[N-1]= u[1];

	  t=t+dt;
     
}
//-----------------------------------------------------------------------------
void EqOnde(void){
    
    if(iter++==0) Start();
    else   GOT();
    //else   simple();                   //GOT();
    sleep(200);
}
//-----------------------------------------------------------------------------





