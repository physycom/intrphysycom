#include <math.h>
#include <nr.h>

#define BPI  6.2831853
#define NDAT       128

using namespace std;

void realft(VecDoub_IO &, const int);

VecDoub_IO u(NDAT);

double x[NDAT],ud[NDAT],dx,dt,t;
int nmax=NDAT;
//----------------------------------------------------------------------------
void filtro() {
    double alfa= 2.0/u.size();
    realft(u, 1); realft(u,-1);
    for(int i=0; i<u.size(); i++)  u[i]*= alfa;
}
//----------------------------------------------------------------------------
void der(VecDoub_IO &f,VecDoub_IO &f1,VecDoub_IO &f3) {
    double alfa= BPI/(f.size()*dx);
    for(int i=0; i<f.size(); i++) f1[i]= 2.0*f[i]/f.size();

    realft(f1, 1);

    for(int i=0; i<f.size()/2; i++) {
        double save= -f1[2*i  ]*(i*alfa);
        f1[2*i  ]=    f1[2*i+1]*(i*alfa);
        f1[2*i+1]=    save;
        f3[2*i  ]=    -f1[2*i  ]*(i*alfa)*(i*alfa);
        f3[2*i+1]=    -f1[2*i+1]*(i*alfa)*(i*alfa);
    }
    realft(f1,-1);
    realft(f3,-1);
}
//----------------------------------------------------------------------------
void fdot(VecDoub_IO &u,VecDoub_IO &ut){
    static VecDoub_IO ux(NDAT),uxxx(NDAT);
    der(u,ux,uxxx);
    for(int i=0; i<u.size(); i++) ut[i]= -6*u[i]*ux[i]-uxxx[i];   // KDV
}
//----------------------------------------------------------------------------
void fdot(VecDoub_IO &u,VecDoub_IO &ut,VecDoub_IO &utt){
    static VecDoub_IO ux(NDAT),uxxx(NDAT);
    static VecDoub_IO utx(NDAT),utxxx(NDAT);
    der(u,ux,uxxx);
    for(int i=0; i<u.size(); i++) ut[i]=  -6*u[i]*ux[i]-uxxx[i];
    der(ut,utx,utxxx);
    for(int i=0; i<u.size(); i++) utt[i]= -6*ut[i]*ux[i] -6*u[i]*utx[i] -utxxx[i];
}
//----------------------------------------------------------------------------
void test_der(){
    VecDoub_IO data(NDAT),d1(NDAT),d3(NDAT),d1c(NDAT),d3c(NDAT);
    double dx=1.0;
    double k0= BPI/(data.size()*dx);
    for(int i=0; i<NDAT; i++) { data[i]= 7.0                        +3.0*cos(27*k0*i*dx)                     +6*sin(7*k0*i*dx); }
    for(int i=0; i<NDAT; i++) { d1[i]=                      -3.0*(27*k0)*sin(27*k0*i*dx)              +6*(7*k0)*cos(7*k0*i*dx); }
    for(int i=0; i<NDAT; i++) { d3[i]=       3.0*(27*k0)*(27*k0)*(27*k0)*sin(27*k0*i*dx)-6*(7*k0)*(7*k0)*(7*k0)*cos(7*k0*i*dx); }

    der(data,d1c,d3c);

    for(int i=0; i<data.size()/2; i++) fprintf(stdout,"%8d %10.3lf %10.3lf\n",i,d1[i],d1c[i]);
    system("Pause");
    for(int i=0; i<data.size()/2; i++) fprintf(stdout,"%8d %10.3lf %10.3lf\n",i,d3[i],d3c[i]);
}
//----------------------------------------------------------------------------
void TAY(void){
    static VecDoub_IO uw(NDAT),ut(NDAT),utt(NDAT);
    fdot(u,ut,utt);
    for(int i=0; i<u.size(); i++) u[i]= u[i]+ ut[i]*dt+0.5*utt[i]*dt*dt;
}
//----------------------------------------------------------------------------
void RK2(void){
    static VecDoub_IO uw(NDAT),udot(NDAT);

    fdot(u,udot);
    for(int i=0; i<u.size(); i++) uw[i]= u[i]+ udot[i]*dt/2;
    fdot(uw,udot);
    for(int i=0; i<u.size(); i++) u[i]= u[i]+ udot[i]*dt;
}
//-----------------------------------------------------------
void RK4(){

    static VecDoub_IO u1(NDAT),u2(NDAT),u3(NDAT);
    static VecDoub_IO d1(NDAT),d2(NDAT),d3(NDAT),d4(NDAT);

    fdot(u,d1);
    for(int i=0; i<u.size(); i++) u1[i]= u[i]+ d1[i]*dt/2;
    fdot(u1,d2);
    for(int i=0; i<u.size(); i++) u2[i]= u[i]+ d2[i]*dt/2;
    fdot(u2,d3);
    for(int i=0; i<u.size(); i++) u3[i]= u[i]+ d3[i]*dt;
    fdot(u3,d4);
    for(int i=0; i<u.size(); i++) u[i]= u[i]+ (d1[i]+2*d2[i]+2*d3[i]+d4[i])*dt/6;
    t+=dt;
}
//----------------------------------------------------------
void Leap(){
    static bool primavolta=true,uno=true;
    static VecDoub_IO u1(NDAT),d1(NDAT); int i;
    if(primavolta){
        primavolta=false; for(int i=0; i<u.size(); i++) u1[i]= u[i];
        RK4(); return;
    }
    static double *a,*a1;
    if(uno){ a=&u[0]; a1=&u1[0]; fdot(u,d1);}
    else   { a=&u1[0]; a1=&u[0]; fdot(u1,d1);}
    uno= !uno;
    for(int i=0; i<u.size(); i++) a1[i]= a1[i]+ d1[i]*dt;
}
//----------------------------------------------------------
void ZK(){ // Zabusky e Kruskal
    static bool primavolta=true,uno=true;
    static VecDoub_IO u1(NDAT),w(NDAT); int i;
    if(primavolta){
        primavolta=false; for(int i=0; i<u.size(); i++) u1[i]= u[i];
        RK4(); return;
    }
    static double *a,*a1;
    if(uno){ a=&u[0];  a1=&u1[0];}
    else   { a=&u1[0]; a1=&u[0];}
    uno= !uno;

    i=0; a1[i]= a1[i] -2*dt*(a[i+1]+a[i]+a[NDAT-1])*(a[i+1]-a[NDAT-1])/dx
                      -dt*(a[i+2]-2*a[i+1]+2*a[NDAT-1]-a[NDAT-2])/(dx*dx*dx);
    i=1; a1[i]= a1[i] -2*dt*(a[i+1]+a[i]+a[i-1])*(a[i+1]-a[i-1])/dx
                      -dt*(a[i+2]-2*a[i+1]+2*a[i-1]-a[NDAT-1])/(dx*dx*dx);
    for(int i=2; i<u.size()-2; i++){
         a1[i]= a1[i] -2*dt*(a[i+1]+a[i]+a[i-1])*(a[i+1]-a[i-1])/dx
                      -dt*(a[i+2]-2*a[i+1]+2*a[i-1]-a[i-2])/(dx*dx*dx);
    }
    i=NDAT-2; a1[i]= a1[i] -2*dt*(a[i+1]+a[i]+a[i-1])*(a[i+1]-a[i-1])/dx
                           -dt*(a[0]-2*a[i+1]+2*a[i-1]-a[i-2])/(dx*dx*dx);
    i=NDAT-1; a1[i]= a1[i] -2*dt*(a[0]+a[i]+a[i-1])*(a[0]-a[i-1])/dx
                           -dt*(a[1]-2*a[0]+2*a[i-1]-a[i-2])/(dx*dx*dx);

}
//----------------------------------------------------------------------------
double secH( double x){ double temp= exp(x); return 2.0/(temp+1/temp); }
//----------------------------------------------------------------------------
void KDV(void) {
    static int iter=0; static double sum_1=0,sum_2=0,ampli=6.0;   // 2 6 8 12

    static bool primavolta=true;
    if(primavolta){
       primavolta=false;
       dx=10.0/NDAT; int i0= u.size()/2; t=0.0;
         dt= 0.0001;   //ZK 0.0001
       //dt= 0.00002;       //Leap
       //dt= 0.000002;      //RK4
       //dt= 0.000002;      //RK2
       //dt= 0.000002;      //TAY
       for(int i=0; i<u.size(); i++) { x[i]= (i-i0)*dx; u[i]= ampli*secH( (i-i0)*dx )+ (0.0*rand())/RAND_MAX; }
       filtro();
       for(int i=0; i<u.size(); i++ ) ud[i]=2*u[i]/ampli;
       for(int i=0; i<u.size(); i++ ) { sum_1 += ud[i]; sum_2 += ud[i]*ud[i];}

    }else for(int n=0; n<100; n++) ZK();  //ZK();  TAY();    RK2();   RK4();

    for(int i=0; i<u.size(); i++ ) ud[i]=2*u[i]/ampli;

    if(iter++%100==0 ) {
       double sum1=0,sum2=0;
       for(int i=0; i<u.size(); i++ ) { sum1 += ud[i]; sum2 += ud[i]*ud[i];}
       fprintf(stdout,"%10d %16.12lf %16.12lf\n",iter,(sum1-sum_1)/sum_1,(sum2-sum_2)/sum_2); fflush(stdout); //system("Pause");
    }
}
//----------------------------------------------------------------------------

