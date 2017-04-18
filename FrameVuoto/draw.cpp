#include <FL/gl.h>
#include <math.h>

#include "draw.h"

#define CARTESIO  1
#define QUADRATO  2
#define LINEA     3


// ********************************************************************************************************
void draw_init(void){
    float L=0.5;
    glNewList(QUADRATO, GL_COMPILE);
       glBegin(GL_QUADS);
          glColor3f(1.0, 0.0, 0.0);
          glVertex3f( L, L,0.0); 
		  glVertex3f(-L, L,0.0); 
		  glVertex3f(-L,-L,0.0);
		  glVertex3f( L,-L,0.0); 
          glColor3f(1.0, 1.0, 1.0);
       glEnd();
    glEndList(); 
       
    L=1;   
    glNewList(LINEA, GL_COMPILE);
       glBegin(GL_LINES);
          glColor3f(1.0, 1.0, 0.0);
          glVertex3f( -L, 0.0,0.0); glVertex3f( L,0.0,0.0);  
          glColor3f(1.0, 1.0, 1.0);
       glEnd();
    glEndList();    


    glNewList(CARTESIO, GL_COMPILE);
       glColor3f(1.0f, 1.0f, 1.0f);
       glBegin(GL_LINES);
           glVertex3f(-5.0f, 0.0f, 0.0f);
           glVertex3f(+5.0f, 0.0f, 0.0f);
       glEnd();
       glBegin(GL_LINES);
           glVertex3f(0.0f, -5.0f, 0.0f);
           glVertex3f(0.0f, +5.0f, 0.0f);
       glEnd();
    glEndList();
       
}
// ********************************************************************************************************
void draw_scene(void){
   static double t= 0.0;
   double dt=0.001,r=2.0,x,y;
   
   t+=dt;
   x= r*cos(t); y= r*sin(t);

   //glClear(GL_DEPTH_BUFFER_BIT); 
   glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
   glCallList(CARTESIO);
   
   glPushMatrix();  
      glTranslated(x,y,0);
      glRotated(t*180/3.1415927,0,0,1);
      glCallList(QUADRATO);
   glPopMatrix();

   glPushMatrix();  
      glRotated(t*180/3.1415927,0,0,1);
      glCallList(LINEA);
   glPopMatrix();
}
// ********************************************************************************************************


