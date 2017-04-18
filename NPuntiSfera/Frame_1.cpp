#include "Frame_1.h"
#include "def.h"

extern void draw_scene();

void Frame_1::init(){

    GLUquadricObj *palla;
    palla = gluNewQuadric();
    gluQuadricDrawStyle(palla, GLU_FILL); 
    gluQuadricNormals(palla, GLU_FLAT);

    glNewList(SFERA, GL_COMPILE);
        glColor3f(1.0f, 1.0f, 0.0f);
        gluSphere(palla, 0.05, 10, 20);
    glEndList();    
}
void Frame_1::draw() {
  if (!valid()) {
    #if defined(LIGHT)
      glEnable(GL_LIGHT0);                                // Turn on a light with defaults set
      glEnable(GL_LIGHTING);                              // Turn on lighting
      glEnable(GL_COLOR_MATERIAL);                        // Allow color                
    #endif // LIGHT            
    glClearColor(0.0, 0.0, 0.0, 1);                        // Turn the background color black
    glViewport(0,0,w(),h());                               // Make our viewport the whole window
    glMatrixMode(GL_PROJECTION);                           // Select The Projection Matrix
    glLoadIdentity();                                      // Reset The Projection Matrix
    gluPerspective(45.0f,w()/h(), 1 ,150.0f);
    glMatrixMode(GL_MODELVIEW);                            // Select The Modelview Matrix
    glLoadIdentity();                                      // Reset The Modelview Matrix
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);    // Clear The Screen And The Depth Buffer
    glLoadIdentity();                                      // Reset The View
    gluLookAt( 0, 0, 10,     0, 0, 0,     0, 1, 0);         // Position - View  - Up Vector
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_CULL_FACE);
    init();    
    valid(1);
  }

  //glClear(GL_DEPTH_BUFFER_BIT); 
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
  
  glPushMatrix();
    glRotated(ruotaZ,0,0,1); glRotated(ruotaX,1,0,0); glRotated(ruotaY,0,1,0);
    glScalef(zoom,zoom,zoom);
    draw_scene();
  glPopMatrix();
  
}
