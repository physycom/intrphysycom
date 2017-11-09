#include "draw.h"

void normale9f(float x1, float y1, float z1, float x2, float y2, float z2,
               float x3, float y3, float z3);
void draw_palla();
void draw_tetra();
void draw_cube();

//-------------------------------------------------------------------------------------------------
void normale9f(float x1, float y1, float z1, float x2, float y2, float z2,
               float x3, float y3, float z3) {
  float xx1, yy1, zz1, xx2, yy2, zz2, nx, ny, nz, nn;
  xx1 = x2 - x1;
  yy1 = y2 - y1;
  zz1 = z2 - z1;
  xx2 = x3 - x1;
  yy2 = y3 - y1;
  zz2 = z3 - z1;
  nx = yy1 * zz2 - yy2 * zz1;
  ny = zz1 * xx2 - zz2 * xx1;
  nz = xx1 * yy2 - xx2 * yy1;
  nn = sqrt(nx * nx + ny * ny + nz * nz);
  nx /= nn;
  ny /= nn;
  nz /= nn;
  glNormal3f(nx, ny, nz);
}
//-------------------------------------------------------------------------------------------------
void draw_palla() {
  GLUquadricObj *palla;
  palla = gluNewQuadric();
  glDisable(GL_TEXTURE_2D);
  GLfloat cubeMater[] = {(GLfloat)0.2, (GLfloat)0.2, (GLfloat)1.0,
                         (GLfloat)1.0};
  glMaterialfv(GL_FRONT, GL_AMBIENT_AND_DIFFUSE, cubeMater);
  gluQuadricDrawStyle(palla, GLU_FILL);
  gluQuadricNormals(palla, GLU_FLAT);
  gluSphere(palla, 1.0, 50, 100);
  glEnable(GL_TEXTURE_2D);
  // dopo zooming con glscale occorre renormalizzare le normali altrimenti
  // l'illuminazione cambia
}
//-------------------------------------------------------------------------------------------------
void draw_tetra() {
  const float H1 = 0.288675f, H2 = 0.577350f;

  glColor3f((GLfloat)1.0, (GLfloat)0.8, (GLfloat)0.2);
  glBegin(GL_TRIANGLES);
  normale9f(-0.5, -H1, -H1, 0.5, -H1, -H1, 0.0, H2, -H1);
  glVertex3f(-0.5, -H1, -H1);
  glVertex3f(0.5, -H1, -H1);
  glVertex3f(0.0, H2, -H1);
  normale9f(-0.5, -H1, -H1, 0.0, H2, -H1, 0.0, 0.0, H2);
  glVertex3f(-0.5, -H1, -H1);
  glVertex3f(0.0, H2, -H1);
  glVertex3f(0.0, 0.0, H2);
  normale9f(-0.5, -H1, -H1, 0.0, 0.0, H2, 0.5, -H1, -H1);
  glVertex3f(-0.5, -H1, -H1);
  glVertex3f(0.0, 0.0, H2);
  glVertex3f(0.5, -H1, -H1);
  normale9f(0.0, 0.0, H2, 0.0, H2, -H1, 0.5, -H1, -H1);
  glVertex3f(0.0, 0.0, H2);
  glVertex3f(0.0, H2, -H1);
  glVertex3f(0.5, -H1, -H1);
  glEnd();
  glColor3f(1.0, 1.0, 1.0);
}
//-------------------------------------------------------------------------------------------------
void draw_cube() {
  glColor3f((GLfloat)0.2, (GLfloat)1.0, (GLfloat)0.2);
  glBegin(GL_QUADS);
  glNormal3f(0, 0, -1);
  glVertex3f(-1.0f, 1.0f, -1.0f);
  glVertex3f(1.0f, 1.0f, -1.0f);
  glVertex3f(1.0f, -1.0f, -1.0f);
  glVertex3f(-1.0f, -1.0f, -1.0f);
  glNormal3f(0, 0, 1);
  glVertex3f(-1.0f, 1.0f, 1.0f);
  glVertex3f(-1.0f, -1.0f, 1.0f);
  glVertex3f(1.0f, -1.0f, 1.0f);
  glVertex3f(1.0f, 1.0f, 1.0f);
  glNormal3f(0, -1, 0);
  glVertex3f(1.0f, -1.0f, -1.0f);
  glVertex3f(1.0f, -1.0f, 1.0f);
  glVertex3f(-1.0f, -1.0f, 1.0f);
  glVertex3f(-1.0f, -1.0f, -1.0f);
  glNormal3f(0, 1, 0);
  glVertex3f(-1.0f, 1.0f, 1.0f);
  glVertex3f(1.0f, 1.0f, 1.0f);
  glVertex3f(1.0f, 1.0f, -1.0f);
  glVertex3f(-1.0f, 1.0f, -1.0f);
  glNormal3f(-1, 0, 0);
  glVertex3f(-1.0f, -1.0f, 1.0f);
  glVertex3f(-1.0f, 1.0f, 1.0f);
  glVertex3f(-1.0f, 1.0f, -1.0f);
  glVertex3f(-1.0f, -1.0f, -1.0f);
  glNormal3f(1, 0, 0);
  glVertex3f(1.0f, -1.0f, 1.0f);
  glVertex3f(1.0f, -1.0f, -1.0f);
  glVertex3f(1.0f, 1.0f, -1.0f);
  glVertex3f(1.0f, 1.0f, 1.0f);
  glEnd();
  glColor3f(1.0, 1.0, 1.0);
}
// ********************************************************************************************************
void draw_scene() {

  // draw_tetra();
  // draw_palla();
  // draw_cube();

  glColor3f((GLfloat)0.1, (GLfloat)1.0, (GLfloat)0.1); // redish
  glFrontFace(GL_CW);
  // glutSolidTeapot(0.5);		                  	// draw the
  // teapot
  // glutSolidTorus(1,2,30,30);			            // draw the torus
  // glutSolidCylinder(1,2,30,20);			          // draw the
  // cylinder
}
