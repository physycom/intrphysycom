#include <math.h>

#define N  401
#define PI 3.14159265359

int nmax= N;
double t,dt,dx;
double x[N],u[N],d[N],u_[N],d_[N];
double udot[N],ddot[N];

//-----------------------------------------------------------------------------
void Start_SingleWave(void){                                            
    t=0; dx = 10.0/(N-1); dt= 0.001*dx;       
    //t=0; dx = 10.0/(N-1); dt= .99999*dx;   //S2 stabile
    //t=0; dx = 10.0/(N-1); dt= 0.2*dx;      //RK2
    //t=0; dx = 10.0/(N-1); dt= 0.1*dx;      //RK2 limite in
    //t=0; dx = 10.0/(N-1); dt= 1.00001*dx;  //S2 instabile
    //t=0; dx = 10.0/(N-1); dt=0.01*dx;  //S2 instabile                  LX= 10
    
    for( int n=1; n<N-1; n++ ){
         double xx= -5+ n*dx; 
         x[n]= xx;
         if ( xx > -1 && xx < 1 ) {
              d[n]= ( 1+cos(PI*xx) )/2;
              u[n]= 0;
         }
         else { d[n]=u[n]= 0.0; }
    }
    x[0]= x[1]-dx; x[N-1]= x[N-2]+dx;
    u[0]= u[N-2]; u[N-1]= u[1];
    d[0]= d[N-2]; d[N-1]= d[1];
}
//-----------------------------------------------------------------------------
void Start_WavePacket(void){   
    t=0; dx = 10.0/(N-1); dt= 0.2*dx;       //S2 stabile
    //t=0; dx = 10.0/(N-1); dt= .99999*dx;      //S2 stabile
    //t=0; dx = 10.0/(N-1); dt= 0.2*dx;      //RK2
    //t=0; dx = 10.0/(N-1); dt= 0.1*dx;      //RK2 limite in
    //t=0; dx = 10.0/(N-1); dt= 1.00001*dx;  //S2 instabile
    
    for( int n=1; n<N-1; n++ ){
         double xx= -5+ n*dx; 
         x[n]= xx;
        // u[n]= 0.0;
         if ( xx > -1 && xx < 1 ) {
              d[n]= sin(8*PI*xx)*( 1+cos(PI*xx) )/2;
              u[n]= sin(8*PI*xx)*( 1+cos(PI*xx) )/2;
         }
         else { d[n]=u[n]= 0.0; }
    }
    x[0]= x[1]-dx; x[N-1]= x[N-2]+dx;
    u[0]= u[N-2]; u[N-1]= u[1];
    d[0]= d[N-2]; d[N-1]= d[1];
}

//-----------------------------------------------------------------------------
void S2(void) 
{
    
    for( int n=1; n<N-1; n++ )    ddot[n] = - (u[n+1]-u[n  ])/dx;
	for( int n=1; n<N-1; n++ )    d[n]= d[n] +ddot[n]*dt/2;         d[0]= d[N-2]; d[N-1]= d[1];
    for( int n=1; n<N-1; n++ )    udot[n] = - (d[n  ]-d[n-1])/dx;
   	for( int n=1; n<N-1; n++ )    u[n]= u[n] +udot[n]*dt;           u[0]= u[N-2]; u[N-1]= u[1];       
    for( int n=1; n<N-1; n++ )    ddot[n] = - (u[n+1]-u[n  ])/dx;
	for( int n=1; n<N-1; n++ )    d[n]= d[n] +ddot[n]*dt/2;
    d[0]= d[N-2]; d[N-1]= d[1];

	t=t+dt;
} 
//-----------------------------------------------------------------------------
void Force(double u[], double d[], double udot[], double ddot[], double t)
{
    for( int n=1; n<N-1; n++ ){
         udot[n] = - (d[n  ]-d[n-1])/dx;
         ddot[n] = - (u[n+1]-u[n  ])/dx;
    }
}  
//-----------------------------------------------------------------------------
void RK2(void) 
{
	
	Force( u,d,udot,ddot,t );	
	for( int n=1; n<N-1; n++ ) {
       u_[n]= u[n] +udot[n]*dt/2;     d_[n]= d[n] +ddot[n]*dt/2;
    }
    u_[0]= u_[N-2]; u_[N-1]= u_[1];   d_[0]= d_[N-2]; d_[N-1]= d_[1];

	Force(u_,d_,udot,ddot,t+dt/2);
	for( int n=1; n<N-1; n++ ) {
       u[n]= u[n] +udot[n]*dt;        d[n]= d[n] +ddot[n]*dt;
    }
    u[0]= u[N-2]; u[N-1]= u[1];       d[0]= d[N-2]; d[N-1]= d[1];

	t=t+dt;
} 
//-----------------------------------------------------------------------------
void SS(void) 
{

	for( int n=1; n<N-1; n++ ) u[n]= u[n] -(d[n  ]-d[n-1])*(dt/dx); u[0]= u[N-2]; u[N-1]= u[1];
	for( int n=1; n<N-1; n++ ) d[n]= d[n] -(u[n+1]-u[n  ])*(dt/dx); d[0]= d[N-2]; d[N-1]= d[1];

    t=t+dt;
}
//-----------------------------------------------------------------------------
void EqOnde(void){
    static int iter= 0;
    //if(iter++==0) Start_WavePacket();
    if(iter++==0) Start_SingleWave();
    if(iter*dt <= 100 ) SS();  // S2() o RK2 o SS()
}
//-----------------------------------------------------------------------------





