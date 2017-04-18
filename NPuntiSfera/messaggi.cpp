#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <iostream>

#include "form.h"

extern void Stringhe_Distanze(void);

extern FILE *fp1;
extern Fl_Multiline_Output *linee;
extern double f_error;
extern bool trovato;
extern double x[N_PUNTI],y[N_PUNTI],z[N_PUNTI];

//------------------------------------------------------------------------------------------------------ 
void leggi(void){     
  FILE *fp2;
  int nmax;
  fp2 = fopen (FILE_INPUT, "r");
  fscanf(fp2," %d ",&nmax);
  if(nmax != N_PUNTI) exit(2);
  for (int k=0; k<N_PUNTI; k++) fscanf(fp2," %lf %lf %lf ",&x[k],&y[k],&z[k]);
  trovato=true;
  Stringhe_Distanze();
}
//------------------------------------------------------------------------------------------------------ 
void stampa(const char* messaggio){
  const int M=50;
  static char linea2[M]={0},linea3[M]={0},linea4[M]={0};
  char linea[4*M]={0};

  strcpy( linea,linea2); strcpy( linea2,linea3); strcpy( linea3,linea4); strcpy( linea4, messaggio);
  strcat( linea, linea2 ); strcat( linea, linea3 ); strcat( linea, linea4 );
  linee->value(linea); 
}
//------------------------------------------------------------------------------------------------------ 
void stampa(int M){
  static char  messaggio[50]={0};
  sprintf(messaggio, " N_PUNTI= %d ",M); linee->value(messaggio);
}
//------------------------------------------------------------------------------------------------------ 
void stampa(void){
  static bool stampati=false;
  static char  messaggio[50]={0};
  if(trovato){
      if(!stampati) {
          stampati=true;                     
          fprintf(fp1,"\n\n");
          for (int k=0; k<N_PUNTI; k++) fprintf(fp1," %12.8lf %12.8lf %12.8lf \n",x[k],y[k],z[k]);          
      }        
  }
  else {             
     sprintf(messaggio, " error=%14.12lf \n",f_error); stampa(messaggio);
  }
}
//------------------------------------------------------------------------------------------------------ 
