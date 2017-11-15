#include "draw.h"

extern double x[N_PUNTI], y[N_PUNTI], z[N_PUNTI];
extern bool trovato;
extern Nodo nodo[N_PUNTI];

void normale9f(float x1, float y1, float z1, float x2, float y2, float z2,
               float x3, float y3, float z3);
void draw_tetra();
void DisegnaPunti();
void DrawTriangle(int k0, int k1, int k2);
void DisegnaTriangoli();

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
//---------------------------------------------------------------------------------------
void DisegnaPunti() {
  for (int k = 0; k < N_PUNTI; k++) {
    glPushMatrix();
    glTranslated(x[k], y[k], z[k]);
    glCallList(SFERA);
    glPopMatrix();
  }
}
//---------------------------------------------------------------------------------------
void DrawTriangle(int k0, int k1, int k2) {

  normale9f((float)x[k0], (float)y[k0], (float)z[k0], (float)x[k1], (float)y[k1], (float)z[k1], (float)x[k2], (float)y[k2], (float)z[k2]);
  glBegin(GL_TRIANGLES);
  glVertex3f((float)x[k0], (float)y[k0], (float)z[k0]);
  glVertex3f((float)x[k1], (float)y[k1], (float)z[k1]);
  glVertex3f((float)x[k2], (float)y[k2], (float)z[k2]);
  glEnd();
}
//---------------------------------------------------------------------------------------
void DisegnaTriangoli() {
  int k, k0, k1, k2, k3, k4, k5, k6;
  for (k = 0; k < N_PUNTI; k++) {
    k0 = nodo[k].vicino[0].k;
    k1 = nodo[k].vicino[1].k;
    k2 = nodo[k].vicino[2].k;
    k3 = nodo[k].vicino[3].k;
    k4 = nodo[k].vicino[4].k;
    k5 = nodo[k].vicino[5].k;
    k6 = nodo[k].vicino[6].k;
    glColor3f(0.2f, 1.0f, 0.2f);
    glPushMatrix();
    DrawTriangle(k0, k1, k2);
    DrawTriangle(k0, k1, k3);
    DrawTriangle(k0, k1, k4);
    DrawTriangle(k0, k1, k5);
    DrawTriangle(k0, k1, k6);
    DrawTriangle(k0, k2, k3);
    DrawTriangle(k0, k2, k4);
    DrawTriangle(k0, k2, k5);
    DrawTriangle(k0, k2, k6);
    DrawTriangle(k0, k3, k4);
    DrawTriangle(k0, k3, k5);
    DrawTriangle(k0, k3, k6);
    DrawTriangle(k0, k4, k5);
    DrawTriangle(k0, k4, k6);
    DrawTriangle(k0, k5, k6);
    glPopMatrix();
  }
}
//---------------------------------------------------------------------------------------

void draw_scene() {
  if (trovato)
    DisegnaTriangoli();
  else
    DisegnaPunti();
}
