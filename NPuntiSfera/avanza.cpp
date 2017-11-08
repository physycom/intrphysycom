#include "avanza.h"

using namespace std;


extern FILE *fp1;
extern void stampa(const char* messaggio);

double t=0,f_error,StartError;
double teta_x=0,teta_y=0,teta_z=0;
double x[N_PUNTI],y[N_PUNTI],z[N_PUNTI];
double xdot[N_PUNTI],ydot[N_PUNTI],zdot[N_PUNTI],xddot[N_PUNTI],yddot[N_PUNTI],zddot[N_PUNTI];
double dd[N_PUNTI][N_PUNTI], d_vic[N_PUNTI];
bool   calcia=false,trovato=false;
int    n_vic[N_PUNTI];
Nodo   nodo[N_PUNTI];
int    iter;

//---------------------------------------------------------------------------------------
double f(double r){ return r*r*r;}
//---------------------------------------------------------------------------------------
void Forza(void){
     int k,kk;
     double r,ax,ay,az,ar,fk,f_max;
     
     for( k=0; k<N_PUNTI; k++ ){
          xddot[k]=0;yddot[k]=0;zddot[k]=0;
     }
     for( k=0; k<N_PUNTI-1; k++ ) for( kk=k+1; kk<N_PUNTI; kk++ ){
          r= sqrt( (x[k]-x[kk])*(x[k]-x[kk])+(y[k]-y[kk])*(y[k]-y[kk])+(z[k]-z[kk])*(z[k]-z[kk]) );
          if( r < RMIN ) r= RMIN;        
          ax= (x[k]-x[kk])/f(r); ay= (y[k]-y[kk])/f(r); az= (z[k]-z[kk])/f(r);
          xddot[ k]+= ax; yddot[ k]+= ay; zddot[ k]+= az;    
          xddot[kk]-= ax; yddot[kk]-= ay; zddot[kk]-= az;    
     }
     for( k=0; k<N_PUNTI; k++ ){ xddot[k]/= N_PUNTI; yddot[k]/= N_PUNTI; zddot[k]/= N_PUNTI; }
     
     for( k=0; k<N_PUNTI; k++ ){                          // elimino le componenti radiali
          ar= xddot[k]*x[k]+yddot[k]*y[k]+zddot[k]*z[k];
          xddot[k]-= ar*x[k]; yddot[k]-= ar*y[k]; zddot[k]-= ar*z[k];
     }

     f_max = -100;
     for( k=0; k<N_PUNTI; k++ ){
          fk= fabs(xddot[k])+fabs(yddot[k])+fabs(zddot[k]);
          if( fk>f_max ) f_max=fk;
     }
     f_error=f_max;
      
     for( k=0; k<N_PUNTI; k++ ){                          // aggiungo una forza di attrito
        xddot[k] += -BETA*xdot[k];
        yddot[k] += -BETA*ydot[k];
        zddot[k] += -BETA*zdot[k];
     }
}
//---------------------------------------------------------------------------------------
double R_UNI()  // random uniforme
{
    static double dseed= 123459234.5678;
    dseed = fmod(16807.0*dseed, 2147483647.0);
    return(dseed/2147483711.0);
}
//---------------------------------------------------------------------------------------
void Distanza(void){
     for( int k=0; k<N_PUNTI; k++ ) for( int kk=0; kk<N_PUNTI; kk++ ){
        dd[k][kk]= sqrt( (x[k]-x[kk])*(x[k]-x[kk])+(y[k]-y[kk])*(y[k]-y[kk])+(z[k]-z[kk])*(z[k]-z[kk]) );
     }
}
//---------------------------------------------------------------------------------------
void Stringhe_Distanze(void) {
     int k,kk,j,jj,id1,id2;
     double r,dmin;
     Punto work[N_PUNTI],temp;
     Nodo n_temp;
     bool prossimo;

     Distanza();
     for( k=0; k<N_PUNTI; k++ ){
          for( j=0; j<N_PUNTI; j++ ){ work[j].k=j; work[j].d= dd[k][j]; }          
          for( j=0; j<DIECI+1; j++ ){ 
               for( jj=j+1; jj<N_PUNTI; jj++ ){
                    if( work[jj].d < work[j].d ) {
                        temp= work[j]; work[j]=work[jj]; work[jj]=temp;                        
                    }
               }
          }
          for( j=0; j<DIECI; j++ ){ nodo[k].vicino[j]= work[j]; }
          nodo[k].n_punti=1;
     }

          
     for( k=0; k<N_PUNTI-1; k++ ) for( kk=k+1; kk<N_PUNTI; kk++ ){
          j=0; prossimo= true;

          while( j<DIECI && prossimo ) {
               id1= int( MILLE*nodo[k].vicino[j].d ); id2= int( MILLE*nodo[kk].vicino[j].d );
               if ( id2 == id1 ) j++;
               else {
                    if( id2 < id1 ) { n_temp= nodo[k]; nodo[k]= nodo[kk]; nodo[kk]= n_temp; }
                    prossimo= false;
               }
          }
     }

     char s0[70]={0},s1[70]={0};
     int k0,k1,k_tot;
     fprintf(fp1,"\n N_PUNTI= %5d  Iter= %8d F_ERROR= %14.12lf \n",N_PUNTI,iter,f_error );     
     k0=0;
     while ( k0<N_PUNTI-1 ) {
          k_tot=1; k1=k0+1; prossimo= true; 
          sprintf( s0,"%7.4lf%7.4lf%7.4lf%7.4lf%7.4lf%7.4lf%7.4lf%7.4lf%7.4lf%7.4lf",
                  nodo[k0].vicino[0].d,nodo[k0].vicino[1].d,nodo[k0].vicino[2].d,
                  nodo[k0].vicino[3].d,nodo[k0].vicino[4].d,nodo[k0].vicino[5].d,
                  nodo[k0].vicino[6].d,nodo[k0].vicino[7].d,nodo[k0].vicino[8].d,nodo[k0].vicino[9].d );
          while ( prossimo && k1 < N_PUNTI ) {
              sprintf( s1,"%7.4lf%7.4lf%7.4lf%7.4lf%7.4lf%7.4lf%7.4lf%7.4lf%7.4lf%7.4lf",
                  nodo[k1].vicino[0].d,nodo[k1].vicino[1].d,nodo[k1].vicino[2].d,
                  nodo[k1].vicino[3].d,nodo[k1].vicino[4].d,nodo[k1].vicino[5].d,
                  nodo[k1].vicino[6].d,nodo[k1].vicino[7].d,nodo[k1].vicino[8].d,nodo[k1].vicino[9].d );
              if ( strcmp(s1,s0) == 0 ){ k_tot++; k0++; k1=k0+1; }            
              else { prossimo = false; k0=k1; }
          }    
          fprintf(fp1," %4d %s \n",k_tot,s0);
     }
}
//---------------------------------------------------------------------------------------
void Next(void){
     double r,vr;
     static double f_error_old=10000.0;
     int k;
     if(trovato) return;
     iter++;
     for( k=0; k<N_PUNTI; k++ ){
          x[k] = x[k] + xdot[k]*DELTA_T/2;
          y[k] = y[k] + ydot[k]*DELTA_T/2;
          z[k] = z[k] + zdot[k]*DELTA_T/2;
     }
     Forza();
     if( f_error < 1.0E-10 || iter>ITERMAX ){ 
         trovato=true;
         Stringhe_Distanze(); 
     }

     for( k=0; k<N_PUNTI; k++ ){
          xdot[k] = xdot[k] + xddot[k]*DELTA_T;
          ydot[k] = ydot[k] + yddot[k]*DELTA_T;
          zdot[k] = zdot[k] + zddot[k]*DELTA_T;
     }
     for( k=0; k<N_PUNTI; k++ ){
          x[k] = x[k] + xdot[k]*DELTA_T/2;
          y[k] = y[k] + ydot[k]*DELTA_T/2;
          z[k] = z[k] + zdot[k]*DELTA_T/2;
     }
     if (iter%KICK_STEP == 0 ) {
         if( f_error < f_error_old/2 ) f_error_old= f_error;
         else { 
              f_error_old=10000.0;
              for( k=0; k<N_PUNTI; k++ ){
                 x[k] += KICK*( (1-2*R_UNI())*4/sqrt(N_PUNTI));
                 y[k] += KICK*( (1-2*R_UNI())*4/sqrt(N_PUNTI));
                 z[k] += KICK*( (1-2*R_UNI())*4/sqrt(N_PUNTI));
                 xdot[k] = ydot[k] = zdot[k] = 0;
              }
              stampa("KICK \n");
         }
     }
     // elimino le componenti radiali
     for( k=0; k<N_PUNTI; k++ ){
          r= sqrt(x[k]*x[k]+y[k]*y[k]+z[k]*z[k]);
          x[k] /=r; y[k] /=r; z[k] /=r;
          vr= xdot[k]*x[k]+ydot[k]*y[k]+zdot[k]*z[k];
          xdot[k]-= vr*x[k]; ydot[k]-= vr*y[k];zdot[k]-= vr*z[k];          
     }
}
//---------------------------------------------------------------------------------------
void StartAvanza(void){
     double r;
     
     iter=0; calcia=false; trovato=false;     
     for( int k=0; k<N_PUNTI; k++ ){
       x[k]= 1-2*R_UNI(); y[k]= 1-2*R_UNI(); z[k]= 1-2*R_UNI();
       r= sqrt(x[k]*x[k]+y[k]*y[k]+z[k]*z[k]);
       x[k] /= r; y[k] /= r; z[k] /= r;
       xdot[k]=ydot[k]=zdot[k]=0;        
     }
}
//---------------------------------------------------------------------------------------
