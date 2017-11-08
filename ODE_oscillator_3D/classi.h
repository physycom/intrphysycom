#ifndef CLASSI_HPP
#define CLASSI_HPP

//----------------------------------------------------------------------------------------
class Stato
{
   public:
	  int n;
	  double *x,*v,*a;
	  Stato(int n);
	  void set(double x,double v);
	  void set(double x,double y,double vx,double vy);
	  void set(double x,double y,double z,double vx,double vy,double vz);
};
//----------------------------------------------------------------------------------------

#endif // CLASSI_HPP
