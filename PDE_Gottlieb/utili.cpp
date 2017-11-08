#include "utili.h"

extern double dx;

//-----------------------------------------------------------------------------
double segno( double a) {                // calcolo il segno di un double 
#ifdef _WIN32
       return _copysign( 1, a );
#else
       return copysign( 1, a );
#endif
}       
//-----------------------------------------------------------------------------
double minimo( double a, double b) {  // calcolo il minimo fra due double 

       return( a < b ? a:b );
}       
//-----------------------------------------------------------------------------
double minmod( int a, int b, double c) {   // calcolo la funzione minmod 

       return ((a+b)/2)*c;
}       
//-----------------------------------------------------------------------------
double un( double a, double b,int g) {     // calcolo la funzione un 
       if ( g==0 ) return a + 0.5 * b;
       else        return a - 0.5 * b;
}       
//-----------------------------------------------------------------------------
double Godunov( double u1m, double u1p ) {
       // calcolo funzione h e cioè i due flussi fp ed fm 
       double fp, vassp,vassm;       

       if (u1m<=u1p) { 
           if (u1p>=0) {
               if (u1m>=0) fp=u1m*u1m/2;
               else        fp=0;
           }
           else            fp=u1p*u1p/2;
       } else { 
           if (u1m<0) fp=u1p*u1p/2;
           else {
               if (u1p>=0) fp=u1m*u1m/2;
               else {
                   if (u1p>=0) vassp = u1p; else vassp = -u1p; 
                   if (u1m>=0) vassm = u1m; else vassm = -u1m;
                   if (vassp>=vassm) fp=vassp*vassp/2; else fp=vassm*vassm/2;
               }
           }                     
       }
       return fp;
}       
//-----------------------------------------------------------------------------
double uu_x(int i,double u[]){
   double fp, fm;
   double minmod1p, minmod1m, minmod2p, minmod2m;
       
       
     minmod1p = ( segno(u[i+2]- u[i+1] ), segno(u[i+1]- u[i] ),
                  minimo( fabs(u[i+2]- u[i+1] ), fabs(u[i+1]- u[i] ) ) );
     minmod1m = ( segno(u[i+1]- u[i] ), segno(u[i]- u[i-1] ), 
                  minimo(fabs(u[i+1]- u[i] ), fabs(u[i]- u[i-1] ) ) );
     minmod2p =   minmod1m;
     minmod2m = ( segno(u[i]- u[i-1] ), segno(u[i-1]- u[i-2] ), 
                  minimo(fabs(u[i]- u[i-1] ), fabs(u[i-1]- u[i-2] ) ) );
       
     fp= Godunov(un(u[i], minmod1m,0 ), un(u[i+1], minmod1p,1 ) );  
     fm= Godunov(un(u[i-1], minmod2m,0 ), un(u[i], minmod2p,1 ) );  
             
     return (fp-fm)/dx ;
}       
//-----------------------------------------------------------------------------
void sleep( clock_t wait )
{
   clock_t goal;
   goal = wait + clock();
   while( goal > clock() );
}
