#include "classi.h"
Stato::Stato(int m){
    this->n= m;             
    x= new double[n];    
    v= new double[n];        
    a= new double[n];        
}
//-------------------------------------------------------------------------------------------------------------
void Stato::set(double x,double v)
{
	this->x[0]= x;
	this->v[0]= v;
}
//-------------------------------------------------------------------------------------------------------------
void Stato::set(double x,double y,double vx,double vy)
{
	this->x[0]=  x;
	this->x[1]=  y;
	this->v[0]= vx;
	this->v[1]= vy;
}
//-------------------------------------------------------------------------------------------------------------
void Stato::set(double x,double y,double z,double vx,double vy,double vz)
{
	this->x[0]=  x;
	this->x[1]=  y;
	this->x[2]=  z;
	this->v[0]= vx;
	this->v[1]= vy;
	this->v[2]= vz;
}
//-------------------------------------------------------------------------------------------------------------
