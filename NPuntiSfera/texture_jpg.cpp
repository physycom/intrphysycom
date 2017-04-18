#include <FL/gl.h>
#ifdef __APPLE__
#include <OpenGL/glu.h>
#else
#include <GL/glu.h>
#endif
#include <FL/Fl_JPEG_Image.H>

#define NOME_FILE "../dati/mappa.jpg"
using namespace std;

void CreateTexture(unsigned int textureArray[],char *strFileName,int textureID)
{
  Fl_Image *immagine;
  immagine = new Fl_JPEG_Image(NOME_FILE);
  gluBuild2DMipmaps(GL_TEXTURE_2D, 3, immagine->w(), immagine->h(), GL_RGB, GL_UNSIGNED_BYTE, (void*) immagine->data()[0] );
  glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_LINEAR);
  glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_LINEAR_MIPMAP_NEAREST);
}

