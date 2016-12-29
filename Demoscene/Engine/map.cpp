#include "map.h"



/*
//load
GLuint tmp_TName = 0;
char path[80];
fscanf(mtlFile, "%79s", path);
FREE_IMAGE_FORMAT formato = FreeImage_GetFileType(path, 0);
FIBITMAP* imagen = FreeImage_Load(formato, path);

FIBITMAP* temp = imagen;
imagen = FreeImage_ConvertTo32Bits(imagen);
FreeImage_Unload(temp);

int w = FreeImage_GetWidth(imagen);
int h = FreeImage_GetHeight(imagen);
cout << "The size of the image is: " << path << " es " << w << "*" << h << endl;
GLubyte* textura = new GLubyte[4 * w*h];
char* pixeles = (char*)FreeImage_GetBits(imagen);


for (int j = 0; j<w*h; j++){
textura[j * 4 + 0] = pixeles[j * 4 + 2];
textura[j * 4 + 1] = pixeles[j * 4 + 1];
textura[j * 4 + 2] = pixeles[j * 4 + 0];
textura[j * 4 + 3] = pixeles[j * 4 + 3];
}

glGenTextures(1, &tmp_TName);
glBindTexture(GL_TEXTURE_2D, tmp_TName);
glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, w, h, 0, GL_RGBA, GL_UNSIGNED_BYTE, (GLvoid*)textura);
glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);

GLenum huboError = glGetError();
if (huboError){

cout << "There was an error loading the texture" << endl;
}

*/