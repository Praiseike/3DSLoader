/*
    Here I'm trying to use the 3dsLoader i edited to work with linux in this project
    Test No: 1
    last sign out: 20/05/04 02:16 am

*/

#include <GL/glew.h>
#include <GL/freeglut.h>
#include <GL/gl.h>
#include <GL/glu.h>
#include <iostream>
#include "classes/main.h"
#include "classes/3ds.h"
#include "classes/3ds.cpp" ///  Linker and library setup workaround
#include "classes/TextureObjects.h"
#include "classes/TextureObjects.cpp" /// Same here
#include "classes/events/EventHandler.h"  ///  for keyboard events

#define MAX_TEX 10
#define WIDTH 800
#define HEIGHT 760

using namespace std;

EventHandler * handle; // hanler instance for this program


float lightPosition[] = {0,0,10,1};

float lightAbient[] = {0.1,0.1,0.1,1};
float lightDiffuse[] = {1,1,1,1};

// Copy the values of light ambient and diffuse properties respectively
float *matAmbient = lightAbient;
float *matDiffuse = lightDiffuse;

///******************************* Creating variables from the classes*******************\\\

CLoad3DS loader;
t3DModel model;
CTextures tLoader;

unsigned int gTextures[MAX_TEX];
/// *********************
void loadModel(char * filename);

void initGL()
{
    glEnable(GL_DEPTH_TEST);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glClearColor(1,1,0,1);
    glHint(GL_PERSPECTIVE_CORRECTION_HINT,GL_NICEST);
    glEnable(GL_NORMALIZE);
    handle = new EventHandler; // initialize and allocate memory for the handler;
    handle->setSpeed(20);

    // Enable lights in opengl
    glEnable(GL_LIGHTING);

    glMaterialfv(GL_FRONT,GL_AMBIENT,matAmbient);
    glMaterialfv(GL_FRONT,GL_DIFFUSE,matDiffuse);

    glLightfv(GL_LIGHT0,GL_AMBIENT,lightAbient);
    glLightfv(GL_LIGHT0,GL_DIFFUSE,lightDiffuse);
    glLightfv(GL_LIGHT0,GL_POSITION,lightPosition);

    glEnable(GL_LIGHT0);

}



void loadModel(char *filename)
{
    loader.Import3DS(&model,filename);

    // Checking for textures

    for(int i = 0;i<model.numOfMaterials;i++)
    {
        if(strlen(model.pMaterials[i].strFile)>0)
        {
            tLoader.LoadTexture(model.pMaterials[i].strFile,gTextures[i]);
        }
        model.pMaterials[i].texureId = i;
    }

    cout << "No of objects: "<<model.numOfObjects<<endl;

}

void draw()
{


    glPushMatrix();
    glTranslatef(handle->getXtrans(),0,handle->getZtrans());
    glTranslatef(0,-3,0);
    glRotatef(handle->rotateMod(),0,1,0);

    for(int i = 0;i<model.numOfObjects;i++)
    {

        if(model.pObject.size() <= 0) break;

        t3DObject *pObject = &model.pObject[i];

        if(pObject->bHasTexture)
        {
            glEnable(GL_TEXTURE_2D);
            glColor3ub(255,255,255);
            glBindTexture(GL_TEXTURE_2D,gTextures[pObject->materialID]);

        }
        else
        {
            glDisable(GL_TEXTURE_2D);
            glColor3ub(255,255,255);
        }

        glBegin(handle->getViewMode());
        for(int j = 0;j < pObject->numOfFaces;j++)
        {
            for(int k = 0;k<3;k++)
            {
                // get face index for this vertex
                int index = pObject->pFaces[j].vertIndex[k];

                // Normal for this vertex
                glNormal3f(pObject->pNormals[index].x,pObject->pNormals[index].y,pObject->pNormals[index].z);
                if(pObject->bHasTexture)
                {

                    if(pObject->pTexVerts)
                    {
                        glTexCoord2f(pObject->pTexVerts[index].x,pObject->pTexVerts[index].y);
                    }
                }
                else
                {
                    if(model.pMaterials.size() && pObject->materialID >= 0)
                    {
                        unsigned char *pColor = model.pMaterials[pObject->materialID].color;
                        glColor3ub(pColor[0],pColor[1],pColor[2]);
                    }
                }
                glVertex3f(pObject->pVerts[index].x,pObject->pVerts[index].y,pObject->pVerts[index].z);
            }

        }
        glEnd();

    }
    glPopMatrix();



//    gluLookAt(0,3,4, 0,0,0, 0,1,0); // params(camaraPos | center | upVector);
//    glTranslatef(handle->getXtrans(),0,handle->getZtrans());
//    glRotatef(handle->rotateMod(),0,1,0);
//    glutSolidTeapot(1);
}

void render()
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glClearColor(0,0,0,1);
    glLoadIdentity();
    draw();
    glutSwapBuffers();
}

void idle()
{
    glutPostRedisplay();
}

void reshape(int w,int h)
{
    glViewport(0,0,w,h);
    h = (h==0)?1:h;
    double aspect = float(w)/float(h);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(45.0f,aspect,0.1,1000);
    glMatrixMode(GL_MODELVIEW);
    glutPostRedisplay();

}

void keyboard(unsigned char key,int x,int y)
{
    // get char input
}

void specialKeys(int key,int x,int y)
{
    handle->keyboard(key,x,y);
}


int main(int argc,char ** argv)
{
    if(argc < 2)
    {
        printf("Usage: ./main [filename.3ds]\n");
        exit(1);
    }

    glutInit(&argc,argv);
    glutInitDisplayMode(GLUT_RGB | GLUT_DEPTH | GLUT_DOUBLE);
    glutInitWindowPosition(0,0);
    glutInitWindowSize(WIDTH,HEIGHT);

    glutCreateWindow(argv[1]);

    glutDisplayFunc(render);
    glutIdleFunc(idle);
    glutSpecialFunc(specialKeys);
    glutKeyboardFunc(keyboard);
    glutReshapeFunc(reshape);
    initGL();
    loadModel(argv[1]);
    glutMainLoop();


    return 0;
}
