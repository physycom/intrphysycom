#include "Frame_1.h"
#include <FL/gl.h>
#include <GL/glu.h>
#include <cmath>
#include <cstdio>
#include <cstring>

#define LIGHT

extern void draw_scene();
extern void stampa(const char*);

//-----------------------------------------------------------------------------------------------
void Frame_1::init(void) {
  gl_font(FL_HELVETICA_BOLD, 16);
}
//-----------------------------------------------------------------------------------------------


void Frame_1::draw() {
  if (!valid()) {
#if defined(LIGHT)

    GLfloat amb_light[] = { (GLfloat)0.1, (GLfloat)0.1, (GLfloat)0.1, (GLfloat)1.0 };
    GLfloat diffuse[] = { (GLfloat)0.6, (GLfloat)0.6, (GLfloat)0.6, (GLfloat)1 };
    GLfloat specular[] = { (GLfloat)0.7, (GLfloat)0.7, (GLfloat)0.3, (GLfloat)1 };
    glLightModelfv(GL_LIGHT_MODEL_AMBIENT, amb_light);
    glLightfv(GL_LIGHT0, GL_DIFFUSE, diffuse);
    glLightfv(GL_LIGHT0, GL_SPECULAR, specular);
    glEnable(GL_LIGHT0);
    glEnable(GL_COLOR_MATERIAL);
    glShadeModel(GL_SMOOTH);
    glLightModeli(GL_LIGHT_MODEL_TWO_SIDE, GL_FALSE);
    glDepthFunc(GL_LEQUAL);
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_LIGHTING);
    glEnable(GL_LIGHT0);
    glClearColor(0.0, 0.0, 0.0, 1.0);

#endif // LIGHT            
    glClearColor(0.0, 0.0, 0.0, 1);                        // Turn the background color black
    glViewport(0, 0, w(), h());                               // Make our viewport the whole window
    glMatrixMode(GL_PROJECTION);                           // Select The Projection Matrix
    glLoadIdentity();                                      // Reset The Projection Matrix
    gluPerspective(45.0f, w() / h(), 1, 150.0f);
    glMatrixMode(GL_MODELVIEW);                            // Select The Modelview Matrix
    glLoadIdentity();                                      // Reset The Modelview Matrix
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);    // Clear The Screen And The Depth Buffer
    glLoadIdentity();                                      // Reset The View
    gluLookAt(0, 0, 10, 0, 0, 0, 0, 1, 0);        // Position - View  - Up Vector
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_CULL_FACE);

    init();
    valid(1);
  }

  //glClear(GL_DEPTH_BUFFER_BIT); 
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

  glPushMatrix();
  glRotated(ruotaZ, 0, 0, 1); glRotated(ruotaX, 1, 0, 0); glRotated(ruotaY, 0, 1, 0);
  glScalef(zoom, zoom, zoom);
  draw_scene();
  glPopMatrix();
}
//-----------------------------------------------------------------------------------------------
int Frame_1::handle(int evento)
{
  int ix, iy;
  static char  messaggio[50] = { 0 };
  switch (evento)
  {
  case FL_MOVE:
    ix = Fl::event_x();
    iy = Fl::event_y();
    sprintf(messaggio, "  ix=%d iy=%d\n", ix, iy); stampa(messaggio);
  default:
    break;
  }
  redraw();
  return 1;
}
//-----------------------------------------------------------------------------------------------
