#include "draw.h"

#define DOMINIO   1
#define QUADRO    7

extern double x[],u[],d[],dx;
extern int nmax;
extern void EqOnde(void);

// ********************************************************************************************************
void draw_init(void){
    float L=0.02;
    glNewList(QUADRO, GL_COMPILE);
       glBegin(GL_QUADS);
          glVertex3f( L, L,0.0); glVertex3f(-L, L,0.0); glVertex3f(-L,-L,0.0);glVertex3f( L,-L,0.0); 
       glEnd();
    glEndList();    
       
    glNewList(DOMINIO, GL_COMPILE);
       glColor3f(1.0f, 1.0f, 1.0f);
       glBegin(GL_LINES);
           glVertex3f(-5.0f,  0.0f, 0.0f);
           glVertex3f(+5.0f,  0.0f, 0.0f);
       glEnd();
       glBegin(GL_LINES);
           glVertex3f(-5.0f, -1.0f, 0.0f);
           glVertex3f(-5.0f, +1.0f, 0.0f);
       glEnd();
       glBegin(GL_LINES);
           glVertex3f( 5.0f, -1.0f, 0.0f);
           glVertex3f( 5.0f, +1.0f, 0.0f);
       glEnd();
    glEndList();
       
}
// ********************************************************************************************************
void draw_scene(void){
     int n;

   glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
   EqOnde();
   glPushMatrix();
   glScalef(1.0,2.0,1.0);
   glCallList(DOMINIO);

   glColor3f(1.0, 0.0, 0.0);
   for( n=1; n<nmax-1; n++ ){ 
      glPushMatrix();
         glTranslated(x[n],u[n],0);
         glCallList(QUADRO);
      glPopMatrix();
   }
   glColor3f(0.0, 1.0, 0.0);
   for( n=1; n<nmax-1; n++ ){ 
      glPushMatrix();
         glTranslated(x[n]+dx/2,d[n],0);
         glCallList(QUADRO);
      glPopMatrix();
   }
   glPopMatrix();
}
// ********************************************************************************************************

